#ifndef GAME_H
#define GAME_H

#include "ControllingInput.h"

#include <iostream>
#include <stdlib.h>

using namespace std;

class Game
{
	private:
  		int **map1;
  		int **map2;
  		int **temp;
  		int **mapFile;

		short currentMap;
 	    int outputNum;              //output type selection
  		string outputFile;          //output file name
 		string outString;           //output string for storing output strings
  		ofstream o;                 //declare output stream

		//dimensions of the map
  		int x;
  		int y;
  		int height;
  		int width;
  		int mode;
  		bool pause;

  		double density;
  		double regularity;

  		short checkNeighboring(int **map, int x, int y);

	public:
  		Game();
  		~Game();
  		void runRandomSimulate();
  		void setHeight(int inputHeight);
  		void setWidth(int inputWidth);
  		void setDensity(double inputDensity);
 		void setMode(int inputMode);

  		

  		bool CheckingError(int **map1, int **map2, int currentMap, int x, int y);
  		int **simulateNext(int **map, int mode, int x, int y);
 		bool checkEmpty(int **map, int x, int y);
  		int **CreateArray(int width, int height);
  		void LoadRowArray(string intString, int row);
  		string printMapConsole(int height, int width, int **map);
  		void runMapSimulate(int **map, int mode, int x, int y);
  		int getHeight(string fileName);
  		int getWidth(string fileName);

  		int **readInitialFile(string inputFileName);
  		void setOutputNum(int inNumber);           //set the outputNum
  		void setOutputFile(string inString);       //set output file name

};


#endif