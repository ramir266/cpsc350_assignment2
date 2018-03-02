#include "Game.h"
#include <iostream>

using namespace std;

Game::Game(){}

Game::~Game(){}

void Game::runRandomSimulate() //function that runs the random simulate
{
  srand (time(NULL));
  //These variables are for random assignment
  x = width;
  y = height;
  regularity = density;

  currentMap = 1;
  //cout<<"regularity: " <<regularity<<endl;
  //initializing temp array and map2;
  temp = new int *[x];
  map2 = new int *[x];
  for (int i = 0; i < x; ++i)
  {
    map2[i] = new int[y];
    temp[i] = new int[y];
    for (int j = 0; j < y; ++j)
    {
      temp[i][j] = 0;
      map2[i][j] = 0;
    }
  }

  map1 = new int *[x];

  //here is where we will populate the map using regularity
  for (int i = 0; i < x; ++i)
  {
    map1[i] = new int[y];
    for (int j = 0; j < y; ++j)
    {
      if ((double)rand() / (double)RAND_MAX <= regularity)
      {
        map1[i][j] = 1;
      }
      else
      {
        map1[i][j] = 0;
      }
    }
  }

  switch(outputNum) //switch statement gets the output number from main, and uses the case statements to run between different modes
  {
    case 0: //sleep case
      cout<<"Initial Generation: "<<currentMap<<endl;
      cout<<printMapConsole(x,y,map1);
      sleep(2);
      break;
    case 1: //"Enter" case
      cout<<"Initial Generation: "<<currentMap<<endl;
      cout<<printMapConsole(x,y,map1);
      cin.get();
      break;
    case 2: //write to file
      o.open(outputFile.c_str(),ofstream::out | ofstream::trunc);
      o<<"Initial Generation: "<<endl;
      printMapConsole(x, y, map1);
      break;
  }
  /*
  cin.get();
  cout<<"Print map1 Initial Generation is: "<<currentMap<<endl;
  printMapConsole(x,y,map1);
  */

  //This is the main loop where everything runs and outputs every time the user presses enter
  bool stop = false;
  //cin.get();
  while (!stop)
  {
    if (currentMap == 1)
    {
      temp = simulateNext(map1, mode, x, y);
      for (int i = 0; i < x; ++i)
      {
        for (int j = 0; j < y; j++)
        {

          map2[i][j] = temp[i][j];

        }
      }

      currentMap++;

      if (outputNum == 0 || outputNum == 1)
      {
        cout<<"Generation: "<<currentMap<<endl;
        cout<<printMapConsole(x, y, map2);
      }
      else
      {
        o<<"Generation: "<<currentMap<<endl;
        printMapConsole(x, y, map2);
      }

      //cout<<"Current Map"<<endl;
    }

    else if (currentMap >= 2)
    {
      for (int i = 0; i < x; ++i)
      {
        for (int j = 0; j < y; ++j)
        {
          map1[i][j] = map2[i][j];
        }
      }

      temp = simulateNext(map1, mode,x,y);

      for (int i = 0; i < x; ++i)
      {
        for (int j = 0; j < y; ++j)
        {
          map2[i][j] = temp[i][j];
        }
      }
      currentMap++;
      if(outputNum == 0 || outputNum == 1)
      {
        cout<<"Generation: " <<currentMap<<endl;
        printMapConsole(x, y, map2);
      }
      else
      {
        o<<"Generation: "<<currentMap<<endl;
        printMapConsole(x, y, map2);
      }
    }

    stop = CheckingError(map1, map2, currentMap, x, y); //checks whether it is empty or stable

    switch (outputNum)
    {
      case 0:
      {
        sleep(2);
        break;
      }
      case 1:
      {
        string userInput = " ";
        userInput = cin.get();
        if(userInput == "n")
        {
          stop = true;
        }
        break;
      }
      case 2:
      {
        break;
      }
    }
  }
  o.close();
}



void Game::runMapSimulate(int **map, int mode, int x, int y) //this is for map file not random assignment
{
  //x outer loop is height
  //y inner loop is width
  cin.get();
  currentMap = 1;

  //initializing temp array and map2;
  temp = new int *[x];
  map2 = new int *[x];
  for (int i = 0; i < x; ++i)
  {
    map2[i] = new int[y];
    temp[i] = new int[y];
    for (int j = 0; j < y; ++j)
    {
      temp[i][j] = 0;
      map2[i][j] = 0;
    }
  }

  //stop here and build map1

  //equate input map to map1
  map1 = map;

  //call printMapConsole to make sure that correct x, y are used
  switch (outputNum)
  {
    case 0 ... 1:
    {
      cout<<"Initial Generation: "<<currentMap<<endl;
      cout<<printMapConsole(x, y, map1);
      break;
    }
    case 2:
    {
      o.open(outputFile.c_str(), ofstream::out | ofstream::trunc); //opening up the file stream
      o<<"Initial Generation: "<<endl;
      printMapConsole(x, y, map1);
      break;
    }
  }


  //This is the main loop where everything runs and outputs every time the user presses enter
  bool stop = false;
  if (outputNum ==1)
  {
    cin.get();
  }

  //cout<<"Entered runSimulate!!"<<endl;
  while (!stop)
  {
    if (currentMap == 1)
    {
      //simpulateNext returns temp which is then equated to map2
      temp = simulateNext(map1, mode,x,y);

      map2 = temp;

      //next generation calculated so increment map count
      currentMap++;
      if (outputNum==0 || outputNum==1)
      {
        cout<<"Generation: "<<currentMap<<endl;
        cout<<printMapConsole(x, y, map2);
      }
      else if (outputNum == 2)
      {
        o<<"Generation: "<<currentMap<<endl;
        printMapConsole(x, y, map2);
      }
      //currentMap = 2;
    }
    else if (currentMap >= 2)
    {
      for (int i = 0; i < x; ++i)
      {
        for (int j = 0; j < y; ++j)
        {
          map1[i][j] = map2[i][j];
        }
      }

      temp = simulateNext(map1, mode,x,y);
      for (int i = 0; i < x; ++i)
      {
        for (int j = 0; j < y; ++j)
        {
          map2[i][j] = temp[i][j];
        }
      }
      //cout<<"Print map1 Generation "<<currentMap<<endl;
      //printMapConsole(x, y, map1);
      currentMap++;
      if (outputNum == 0 || outputNum == 1)
      {
        cout<<"Generation: "<<currentMap<<endl;
        cout<<printMapConsole(x, y, map2);
      }
      else //saving it to file
      {
        o<<"Generation: "<<currentMap<<endl;
        printMapConsole(x, y, map2);
      }
      //call printMapConsole to make sure that correct x, y are used
      //printMapConsole(x, y, map2);
     // currentMap = 1;
    }

    stop = CheckingError(map1, map2, currentMap, x, y);
    //cout<<"outputNum: "<<outputNum<<endl;
    switch (outputNum)
    {
      case 0:
        {
          //cout<<"case 0 - sleep for 2"<<endl;
          sleep(2);
          break;
        }
      case 1:
        {
          //cout<<"case 1 - user input"<<endl;
          string userInput = " ";
          userInput = cin.get();
          if (userInput == "n")
          {
            stop = true;
          }
          break;
        }
      case 2:
        {
          //cout<<"case 2 - file output"<<endl;
          break;
        }
    }
  }
  o.close();    // close out the output file
}

bool Game::CheckingError(int **map1, int **map2, int currentMap, int x, int y) //checks whether grid is empty or not
{
  bool stop = false;
  bool bazinga = false;
  for(int i = 0; i < x; ++i)
  {
    for (int j = 0; j < y; ++j)
    {
      if (map2[i][j] == 1)
      {
        bazinga = true;
        break;
      }
    }
    if (bazinga == true)
    {
      break;
    }
      //stop = true;
  }

  if (bazinga == false)
  {
    if (outputNum == 0 || outputNum ==1)
    {
      cout<<"Grid is empty. Ending Game."<<endl;
    }
    else
    {
      o<<"Grid is empty. Ending Game.";
      o<<endl;
    }
    stop = true;
  }

  bool jenga = false;
  for(int i = 0; i < x; ++i)
  {
    for (int j = 0; j < y; ++j)
    {
      if (map1[i][j] != map2[i][j])
      {
        jenga = true;
        break;
      }
    }
    if (jenga == true)
    {
      break;
    }
      //stop = true;
  }
  if (jenga == false)
  {
    if (outputNum == 0 || outputNum == 1)
    {
      cout<<"Stability achieved... End of Generation"<<endl;
    }
    else
    {
      o<<"Stability achieved... End of Generation";
      o<<endl;
    }
    stop = true;
  }

  if(currentMap == 1000)//this makes it so you cant go longer than 1000 generations
  {
    if(outputNum == 0 || outputNum == 1)
    {
      cout<<"Generation cannot be any longer"<<endl;
    }
    else
    {
      o<<"Generation cannot go on any longer";
      o<<endl;
    }
    stop = true;
  }
  //cout<<"STOP IS: "<<stop<<endl;
  return stop; //CANT RETURN THIS STOP BACK INTO THE WHILE LOOP STOP!!!!
}


int **Game::simulateNext(int **map, int mode, int x, int y) //this is where all the modes are
{
  //individually defining the rules for each gamemode
  //x outer loop = HEIGHT
  //y inner loop = WIDTH
  for (int i = 0; i < x; ++i)
  {
    for (int j = 0; j < y; ++j)
    {
      short neighbors = 0;
      switch (mode)
      {
        //individually checking all the neighbors for all cases
        case 0: //classic mode
        {
          //standard case checking (not sides)
          if (i > 0 && i < x - 1 && j > 0 && j < y - 1)
          {
            neighbors += checkNeighboring(map, i, j);
          }
          //left side
          else if (i == 0 && j > 0 && j < y - 1)
          {
            for (int k = 0; k < 2; ++k)
            {
              for(int l = -1; l < 2; ++l)
              {
                neighbors += map[i + k][j + l];
              }
            }
          }
          //right side
          else if (i == x - 1 && j > 0 && j < y - 1)
          {
            //cout<<"6";
            for (int k = -1; k < 1; ++k)
            {
              for(int l = -1; l < 2; ++l)
              {
                neighbors += map[i + k][j + l];
              }
            }
          }
          //top side
          else if (j == 0 && i > 0 && i < x - 1)
          {
            //cout<<"5";
            for (int k = -1; k < 2; ++k)
            {
              for(int l = 0; l < 2; ++l)
              {
                neighbors += map[i + k][j + l];
              }
            }
          }
          //bottom side
          else if (j == y - 1 && i > 0 && i < x - 1)
          {
            //cout<<"4";
            for (int k = -1; k < 2; ++k)
            {
              for(int l = -1; l < 1; ++l)
              {
                neighbors += map[i + k][j + l];
              }
            }
          }
          //top left
          else if (i == 0 && j == 0)
          {
            for (int k = 0; k < 2; ++k)
            {
              for(int l = 0; l < 2; ++l)
              {
                neighbors += map[i + k][j + l];
              }
            }
          }
          //bottom left
          else if (i == 0 && j == y - 1)
          {
            for (int k = 0; k < 2; ++k)
            {
              for(int l = -1; l < 1; ++l)
              {
                neighbors += map[i + k][j + l];
              }
            }
          }
          //bottom right
          else if (i == x - 1 && j == y - 1)
          {
            for (int k = -1; k < 1; ++k)
            {
              for(int l = -1; l < 1; ++l)
              {
                neighbors += map[i + k][j + l];
              }
            }
          }
          //top right
          else if (i == x - 1 && j == 0)
          {
            for (int k = -1; k < 1; ++k)
            {
              for(int l = 0; l < 2; ++l)
              {
                neighbors += map[i + k][j + l];
              }
            }
          }

          //setting temp array with the processed array
          if (map[i][j] == 1)
          {
            --neighbors;
          }

          if (neighbors == 2)
          {
            temp[i][j] = map[i][j];
          }

          else if (neighbors <= 1 || neighbors >= 4)
          {
            temp[i][j] = 0;
          }

          else if (neighbors == 3)
          {
            temp[i][j] = 1;
          }

          break;
        }
        case 1: //Doughnut mode
        {
          //cout<<"THIS WAS DOUGHNUT MODE"<<endl;
          //standard case checking (not sides)
          if (i > 0 && i < x - 1 && j > 0 && j < y - 1)
          {
            neighbors += checkNeighboring(map, i, j);
          }
          //left side
          else if (i == 0 && j > 0 && j < y - 1)
          {
            for (int l = -1; l < 2; ++l)
            {
              neighbors += map[x - 1][j + l];
            }
            for (int k = 0; k < 2; ++k)
            {
              for(int l = -1; l < 2; ++l)
              {
                neighbors += map[i + k][j + l];
              }
            }
          }
          //right side
          else if (i == x - 1 && j > 0 && j < y - 1)
          {
            for (int l = -1; l < 2; ++l)
            {
              neighbors += map[0][j + l];
            }
            for (int k = -1; k < 1; ++k)
            {
              for(int l = -1; l < 2; ++l)
              {
                neighbors += map[i + k][j + l];
              }
            }
          }
          //top side
          else if (j == 0 && i > 0 && i < x - 1)
          {
            for (int k = -1; k < 2; ++k)
            {
              neighbors += map[i + k][y - 1];
              for(int l = 0; l < 2; ++l)
              {
                neighbors += map[i + k][j + l];
              }
            }
          }
          //bottom side
          else if (j == y - 1 && i > 0 && i < x - 1)
          {
            for (int k = -1; k < 2; ++k)
            {
              neighbors += map[i + k][0];
              for(int l = -1; l < 1; ++l)
              {
                neighbors += map[i + k][j + l];
              }
            }
          }
          //top left
          else if (i == 0 && j == 0)
          {
            neighbors += map[x - 1][y - 1] + map[x - 1][0] + map[x - 1][1];
            for (int k = 0; k < 2; ++k)
            {
              neighbors += map[i + k][y - 1];
              for(int l = 0; l < 2; ++l)
              {
                neighbors += map[i + k][j + l];
              }
            }
          }
          //bottom left
          else if (i == 0 && j == y - 1)
          {
            neighbors += map[x - 1][0] + map[x - 1][y - 1] + map[x - 1][y - 2];
            for (int k = 0; k < 2; ++k)
            {
              neighbors += map[i + k][0];
              for(int l = -1; l < 1; ++l)
              {
                neighbors += map[i + k][j + l];
              }
            }
          }
          //bottom right
          else if (i == x - 1 && j == y - 1)
          {
            neighbors += map[0][0] + map[0][y - 1] + map[0][y - 2];
            for (int k = -1; k < 1; ++k)
            {
              neighbors += map[x - 1 + k][0];
              for(int l = -1; l < 1; ++l)
              {
                neighbors += map[i + k][j + l];
              }
            }
          }
          //top right
          else if (i == x - 1 && j == 0)
          {
            neighbors += map[0][y - 1] + map[0][0] + map[0][1];
            for (int k = -1; k < 1; ++k)
            {
              neighbors += map[x - 1 + k][y - 1];
              for(int l = 0; l < 2; ++l)
              {
                neighbors += map[i + k][j + l];
              }
            }
          }

          //setting temp array with the processed array using classic rules
          //decrementing neighbor count to exclude current cell
          if (map[i][j] == 1)
          {
            --neighbors;
          }
          //stability
          if (neighbors == 2)
          {
            temp[i][j] = map[i][j];
          }
          //loneliness
          else if (neighbors <= 1 || neighbors >= 4)
          {
            temp[i][j] = 0;
          }
          //growth
          else if (neighbors == 3)
          {
            temp[i][j] = 1;
          }

          break;
        }
        case 2: //Mirror Mode
        {
          //cout<<"This is Mirror Mode"<<endl;
          //standard case checking (not sides)
          if (i > 0 && i < x - 1 && j > 0 && j < y - 1)
          {
            neighbors += checkNeighboring(map, i, j);
          }
          //left side
          else if (i == 0 && j > 0 && j < y - 1)
          {
            for (int l = -1; l < 2; ++l)
            {
              neighbors += map[0][j + l];
            }
            for (int k = 0; k < 2; ++k)
            {
              for(int l = -1; l < 2; ++l)
              {
                neighbors += map[i + k][j + l];
              }
            }
          }
          //right side
          else if (i == x - 1 && j > 0 && j < y - 1)
          {
            for (int l = -1; l < 2; ++l)
            {
              neighbors += map[x - 1][j + l];
            }
            for (int k = -1; k < 1; ++k)
            {
              for(int l = -1; l < 2; ++l)
              {
                neighbors += map[i + k][j + l];
              }
            }
          }
          //top side
          else if (j == 0 && i > 0 && i < x - 1)
          {
            for (int k = -1; k < 2; ++k)
            {
              neighbors += map[i + k][0];
              for(int l = 0; l < 2; ++l)
              {
                neighbors += map[i + k][j + l];
              }
            }
          }
          //bottom side
          else if (j == y - 1 && i > 0 && i < x - 1)
          {
            for (int k = -1; k < 2; ++k)
            {
              neighbors += map[i + k][y - 1];
              for(int l = -1; l < 1; ++l)
              {
                neighbors += map[i + k][j + l];
              }
            }
          }
          //top left
          else if (i == 0 && j == 0)
          {
            neighbors += map[0][0] + map[0][1];
            for (int k = 0; k < 2; ++k)
            {
              neighbors += map[i + k][0];
              for(int l = 0; l < 2; ++l)
              {
                neighbors += map[i + k][j + l];
              }
            }
          }
          //bottom left
          else if (i == 0 && j == y - 1)
          {
            neighbors += map[0][y - 1] + map[0][y - 2];
            for (int k = 0; k < 2; ++k)
            {
              neighbors += map[i + k][y - 1];
              for(int l = -1; l < 1; ++l)
              {
                neighbors += map[i + k][j + l];
              }
            }
          }
          //bottom right
          else if (i == x - 1 && j == y - 1)
          {
            neighbors += map[x - 1][y - 1] + map[x - 1][y - 2];
            for (int k = -1; k < 1; ++k)
            {
              neighbors += map[x - 1 + k][y - 1];
              for(int l = -1; l < 1; ++l)
              {
                neighbors += map[i + k][j + l];
              }
            }
          }
          //top right
          else if (i == x - 1 && j == 0)
          {
            neighbors += map[x - 1][0] + map[x - 1][1];
            for (int k = -1; k < 1; ++k)
            {
              neighbors += map[x - 1 + k][0];
              for(int l = 0; l < 2; ++l)
              {
                neighbors += map[i + k][j + l];
              }
            }
          }

          //setting temp array with the processed array
          if (map[i][j] == 1)
          {
            --neighbors;
          }

          if (neighbors == 2)
          {
            temp[i][j] = map[i][j];
          }

          else if (neighbors <= 1 || neighbors >= 4)
          {
            temp[i][j] = 0;
          }

          else if (neighbors == 3)
          {
            temp[i][j] = 1;
          }

          break;
        }
      }
    }
  }
  return temp;
}

short Game::checkNeighboring(int **map, int x, int y)
{
  short neighbors = 0;
  for (int i = -1; i < 2; ++i)
  {
    for(int j = -1; j < 2; ++j)
    {
      neighbors += map[x+i][y+j]; // minus one for the center square;
    }
  }
  return neighbors;
}

int **Game::readInitialFile(string inputFileName)//opens the file inputted for the map file mode
{
  ifstream myFile;
  string filePath = inputFileName;
  string line;
  int lineCount = 0;
  myFile.open(inputFileName.c_str());
  bool good = myFile.good();
  if (myFile.is_open())
  {
      getline(myFile,line);
      height = atoi(line.c_str()); //also known as rows

      getline(myFile,line);
      width = atoi(line.c_str()); //also known as columns

      if (height > 1000 || width > 1000)
      {
        cout<<"Limit rows and columns to less than or equal to 1000 for better performance. :)"<<endl;
        mapFile = new int *[0];
        height = 0;
        width = 0;
        good = false;
      }

      else if (height < 3 || width < 3)
      {
        cout << "IO Error: Unable to create map. Map file width and height parameters invalid.\n";
        mapFile = new int *[0];
        height = 0;
        width = 0;
        good = false;
      }
      else
      {
        mapFile = CreateArray(width, height);
      }
    for (int n = 0; n < height && good; ++n)
    {
      //starts from line 3 in the file
      getline(myFile,line);
      for (int m = 0; m < width && line[m] != '\n'; m++)
      {
        if (line[m] != '-' && line[m] != 'X' && line[m] != '\n' && line[m] != ' ')
        {
          cout << "Unable to create map. Incorrect syntax." << endl;
          height = 0;
          width = 0;
          return (new int *[0]);
        }
      }
      if ((n == height - 1 && (line.length() != width + 1 && line.length() != width)) || (n != height - 1 && line.length() != width + 1))
      {
        cout << "IO Error: Unable to create map. Map does not match defined array size.\n";
        mapFile = new int *[0];
        height = 0;
        width = 0;
        break;
      }

      //THATS WHERE THE ERROR IS
      else if ((line.size() != width + 1 && n == height - 1))
      {

      }
      LoadRowArray(line, lineCount);
      lineCount++;
    }
  }
  myFile.close();
  return mapFile;
}
int Game::getHeight(string fileName)
{
  return height;
}

int Game::getWidth(string fileName)
{
  return width;
}

void Game::setOutputNum(int inNumber)
{
  outputNum = inNumber;
  //cout<<"outputNum set to: "<<outputNum<<endl;
}

void Game::setOutputFile(string inString)
{
  outputFile = inString;
  //cout<<"outputFile set to: "<<outputFile<<endl;
}

void Game::setHeight(int inputHeight)
{
  height = inputHeight;
  //cout<<"Random Simulate Height is: "<<height<<endl;
}

void Game::setWidth(int inputWidth)
{
  width = inputWidth;
  //cout<<"Random Simulate Width is: "<<width<<endl;
}

void Game::setDensity(double inputDensity)
{
  density = inputDensity;
  //cout<<"Random Simulate Density is: "<<density<<endl;
}

void Game::setMode(int inputMode)
{
  mode = inputMode;
  //cout<<"Random Simulate Mode is: "<<mode<<endl;
}

string Game::printMapConsole(int height, int width, int **map) //generic print map to console
{
  //cout<<"Start of print"<<endl;
  string outString = "";
  for (int i = 0; i < height; ++i)
  {
    for (int j = 0; j < width; ++j)
    {
      if (map[i][j] == 1)
      {
        outString += "X ";
      }
      else
      {
        outString += "- ";
      }
    }
    if (outputNum == 0 || outputNum == 1)
    {
      cout<<outString<<" : row: "<<i + 1<<endl;
      outString = "";
    }
    else
    {
      o<<outString<<" : row: ";
      o<<i;
      o<<endl;
      outString = "";
    }
  }
  return outString;
}

int **Game::CreateArray(int width, int height) //creates the grid for the map file
{
  //the height needs to be the outer loop
  mapFile = new int *[height];
  for (int i = 0; i < height; ++i)
  {
    //the width needs to be inner loop
    mapFile[i] = new int[width];
    for (int j = 0; j < width; ++j)
    {
      mapFile[i][j] = 0;
    }
  }
  return mapFile;
}

void Game::LoadRowArray(string inString, int lineCount) //loads the array created from the map file
{
  for(int i = 0; i < inString.length();++i)
  {
    if(inString[i] == '-')
    {
      mapFile[lineCount][i] = 0;
    }
    else
    {
      mapFile[lineCount][i] = 1;
    }
  }
  //cout<<"LOADED ARRAY!"<<"Row : "<<lineCount<<endl;
}