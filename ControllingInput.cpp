#include "ControllingInput.h"

using namespace std;

ControllingInput::ControllingInput()
{
	int height = 0;
	int width = 0;
	int mode = 0;
}
ControllingInput::~ControllingInput(){}

int ControllingInput::AskOptionInput(int options, string message, string name) //asking for input and checks whether its valid or not
{
	cout<<message;
	string inputStr;
	int inputNum;
	while (true)
	{
		getline(cin, inputStr);
		if (IsBadInt(inputStr))
		{
			cout<<"Invalid Value. Try again: ";
			continue;
		}
		inputNum = atoi(inputStr.c_str());//converts string value to integer value
		if (!(inputNum >= 0 && inputNum < options))
		{	
			cout<<"Invalid " << name << ". Try again: ";
			continue;
		}
		if (name == "mode") //only checks whether the mode was correct, and grabs that number 
		{
			mode = inputNum;
			//cout<<"Setting mode value to "<<inputNum<<endl;
		}
		cout<<"You chose: "<<inputNum<<endl;
		return inputNum;
	}
}

string ControllingInput::ValidatePath() //checks whether file exists 
{
	string filePath;
	while(true)
	{
		cout<<"Enter name of text file you want to input: "<<endl;
		cin>>filePath;
		struct stat buffer; 
		if (!(stat(filePath.c_str(),&buffer) == 0)) //checks whether the file exists 
		{
			cout<<"IO Error: File does not exist."<<endl;
			continue;
		}
		else
		{
			//cout<<"File is good"<<endl;
			break;
		}
	}
	return filePath;
}

int ControllingInput::AskRow() //height of grid
{	
	string tempStr;
	bool badValue = true;	
	while(badValue)
	{
		cout<<"Enter amount of rows in grid: ";
		 //used to flush the buffer
		getline(cin, tempStr);
		if(IsBadInt(tempStr))
		{
			cout<<"Invalid Input. Try again."<<endl;
			continue;
		}

		height = atoi(tempStr.c_str());

		if (height < 3)
		{
			cout<<"Invalid Input. Need value greater than 3."<<endl;
			continue;
		}	
		if (height > 1000)
		{
			cout<<"Limit rows to less than or equal to 1000 for better performance. :)"<<endl;
			continue;
		}

		else
			badValue = false;
	}
	//cout<< "HEIGHT IS: " << height << endl;
	return height;
}

int ControllingInput::AskColumn() //width of grid
{
	string tempStr;
	bool badValue = true;
	while(badValue)
	{	
		cout<<"Enter amount of columns in grid: ";
		getline(cin, tempStr);
		if(IsBadInt(tempStr))
		{
			cout<<"Invalid Input. Try again."<<endl;
			continue;
		}

		width = atoi(tempStr.c_str());

		if (width < 3)
		{
			cout<<"Invalid Input. Need value bigger than 3."<<endl;
			continue;
		}	
		if (width > 1000)
		{
			cout<<"Limit columns to less than or equal to 1000 for better performance. :)"<<endl;
			continue;
		}
		else
			badValue = false;
	}
	//cout<<"WIDTH IS: " <<width<<endl;
	return width;
}

double ControllingInput::AskPercentage() //ask for number and converts it to a decimal 
{
	string tempStr;
	int tempDensity;
	bool badValue = true;
	int index = 0;
	while(badValue == true)
	{	
		cout<<"Enter a number between 1-100 for density of grid: ";
		getline(cin, tempStr);
		if(IsBadInt(tempStr))
		{
			cout<<"Invalid Input. Try again. \n";
			continue;
		}
		//convert the number
		tempDensity = atoi(tempStr.c_str());
		density = double (tempDensity) / double (100);
		if((density<0) || (density > 1))
		{
			cout<<"Invalid input number, must be > 0 and < 100. Try again \n";
			continue;
		}
		else 
		{
			badValue = false;
		}
	}
	//cout<<"DENSITY IS: " <<density << endl;
	return density;
}

bool ControllingInput::IsBadInt(string input) //checks if it is a bad int
{
	for (int i=0; i<input.size(); ++i)
	{
		if(!isdigit(input[i]))
		{
			return true;
		}
	}
	return false;
}


