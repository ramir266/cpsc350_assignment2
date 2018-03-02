#include <iostream>
#include "ControllingInput.h"
#include "Game.h"

using namespace std;

int main(int argc, char** argv)
{
	ControllingInput ci;
	Game game;
	int **myMap;
	int height = 0;
	int width = 0;
	double density = 0; //where you are configuring input output for game class

	cout<<"Welcome to the Game of Life. How would you like to play?"<<endl;

	int inputMode = ci.AskOptionInput(3, "Classic Mode (0), Donut Mode (1), Mirror Mode (2): ", "mode");
	game.setMode(inputMode);
	int outputNum = ci.AskOptionInput(3,"With a brief pause (0), Press 'Enter' to view the next result (1), or Print All to File (2): ","Output Type");
	int inputValue = ci.AskOptionInput(2, "Map File (0) or Random Assignment (1) ", "Type" );

	if (outputNum == 0) //brief pause is chosen
	{
		game.setOutputNum(outputNum);
	}

	else if(outputNum == 1) //printing to console is chosen
	{
		game.setOutputNum(outputNum);
	}

	else if (outputNum == 2) //writing everything to file
	{
		game.setOutputNum(outputNum);
		string outFileName;
		cout<<"Enter file name you would like to print to: "<<endl;
		cin>>outFileName;
		game.setOutputFile(outFileName);
	}

	if (inputValue == 0) //map file
	{
		while (height < 3 || width < 3)
		{

			string validFileName = ci.ValidatePath();
			myMap = game.readInitialFile(validFileName);
			//when calling runSimulate use the following input parameters
			//runSimulate(mappointer, mode, height, width)
			height = game.getHeight(validFileName);
			width = game.getWidth(validFileName);
			if (height >= 3 && width >= 3)
			{
				//cout<<"Height is: "<< height<<endl;
				//cout<<"Width is: "<<width<<endl;
				game.runMapSimulate(myMap,inputMode,height,width);
			}
		}
	}

	else if (inputValue == 1) //random assignment
	{
		height = ci.AskRow();//pass in mode for ask methods and x values
		game.setHeight(height);
		width = ci.AskColumn(); //y values
		game.setWidth(width);
		density = ci.AskPercentage(); //density
		game.setDensity(density);
		//cout<<"DenSITY IN RUN SIMULATE IS: "<<density<<endl;
		game.runRandomSimulate();
	}
}