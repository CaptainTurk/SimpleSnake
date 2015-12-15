/***********************
*C++ Console Snake Game*
***********************/

/*
Sophistikated Games

		/ ╲ ︵ ╱\
		l(◉) (◉)l
		\ ︶ V︶ /
		/ ↺↺↺↺\
	   /|↺↺↺↺↺|\
	  / |↺↺↺↺↺| \
	  \ |↺↺↺↺↺| /
		   ^  ^
		   ^  ^
*/
#include <windows.h>	//Windows specific header file contains declarations for all of the functions in the Windows API.
#include <iostream>		//Provides Input Output to or from files.
#include <conio.h>		//Provides console Input Output, inherited from C language.


using namespace std;	//A declarative region that provides a scope to the identifiers. 

bool endGame;					// Declare function endGame
const int width = 20;			//Draws region width
const int height = 20;			//Draws region height

//Declare values
int x, y, foodX, foodY, gameScore;	
int tailX[100], tailY[100];		//set array sizes
int nTail;


//Sets direction properties
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirecton dir;		


void LoadGame()
{
	endGame = false;
	dir = UP;					//initial direction of the snake, no movement
	x = width / 2;				//x equals half of width
	y = height / 2;				//y equals half of height
	
	foodX = rand() % width;		//randomly generates values in the region
	foodY = rand() % height;	//randomly generates values in the region
	
	gameScore = 0;					//Initializes default value of score
}

/***********************************************************
*						Draw Boundaries					   *
***********************************************************/
void setBoundaries()
{
	system("cls");				//Clear screen
	
	//create width border
	for (int i = 0; i < width + 2; i++)	
		cout << "#";
	cout << endl;

	//create height border
	for (int i = 0; i < height; i++)
	{
		//draw width length 
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				cout << "#";

			//head of the snake
			if (i == y && j == x)
				cout << "O";

			//create food (cherry)
			else if (i == foodY && j == foodX)
				cout << "%";

			//create tail 
			else
			{
				bool print = false;

				//Add on tail
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "*";
						print = true;
					}
				}
				//if nothing printed on the screen, display blank
				if (!print)
					cout << " ";
			}

			//Reduce width length
			if (j == width - 1)
				cout << "#";
		}
		cout << endl;
	}

	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;
	cout << endl;
	cout << "Game Score:" << gameScore << endl;
}

/***********************************************************
*						Get Input Keys					   *
***********************************************************/
void Input()
{
	if (_kbhit())			//Get keys
	{
		switch (_getch())	//get user input  cin <<
		{
		case 'a':
			dir = LEFT;		//direction move left
			break;
		case 'd':
			dir = RIGHT;	//direction move right
			break;
		case 'w':
			dir = UP;		//direction move up
			break;
		case 's':
			dir = DOWN;		//direction move down
			break;
		case 'p':
			endGame = true;	//if user input = p end game
			break;
		}
	}
}

/***********************************************************
*						Create Game Logic				   *
***********************************************************/
void gameLogic()
{
	//sets default array values for tail
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;

	//determine array values as the tail gets longer
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	//determine posisiton accordingly with the user input
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}

	//Adjust boundary limits when snake tail gets longer
	if (x >= width) x = 0; else if (x < 0) x = width - 1;
	if (y >= height) y = 0; else if (y < 0) y = height - 1;

	//if crashes end game
	//Add values when the food is eaten by the snake to the tail
	for (int i = 0; i < nTail; i++)
		if (tailX[i] == x && tailY[i] == y)
			endGame = true;

	//Add score by incrementing 5 points if a fruit is eaten
	//Generate random food for the snake in the boundaries
	if (x == foodX && y == foodY)
	{
		gameScore += 5;				
		foodX = rand() % width;
		foodY = rand() % height;
		nTail++;
	}
}

//Prints out info to display if the player wants to end the game
void info()

{
	cout << "Press P to end the game during the game!" << endl;

}

/***********************************************************
*						Main					           *
***********************************************************/
int main()
{

	int options;	//menu options declaration


		//print out below on the screen
		std::cout << "  |||||\n 0 . . 0\n0   ^   0\n0  \\_/  0\n 0     0\n  00000\n   888\n    8\n\n"; // Smiley Face :=)
		cout << "|===========================|" << endl;
		cout << "|                           |" << endl;
		cout << "|          SNAKE            |" << endl;
		cout << "|                           |" << endl;
		cout << "|===========================|" << endl;
		cout << "" << endl;
		cout << "1) Press 1 to start the game!" << endl;
		cout << "2) Press 2 to exit the game!" << endl;
		cout << "Please select an option : ";
		cin >> options;  // taking option value as input and saving in variable "options"

		if (options == 1) //If user selected option 1, deploy Setup()
		{
			LoadGame();
		}
		else if (options == 2) // If user selected option 2, exit game
		{
			return 0;
		}

		else //if user has entered invalid choice (other than 1,2,3)
		{
			//Displaying error message
			cout << "Invalid Option entered" << endl;
		}

		/***********************************************************
		*						Set Loop					       *
		***********************************************************/

		//Puts all the classes together to run the game
		while (!endGame)	//While endGame is not called do below
		{
			setBoundaries(); //call setBoundaries class
			Input();		//call input class
			gameLogic();	//calls gamelogic 
			Sleep(10);		//Suspends the execution of the current thread until the time-out interval elapses in miliseconds
			info();			//calls info class
		}
		
		cout << "GREAT JOB, YOU CRASHED! GAME OVER!!!" << endl; //Print this lane when crashed.
		system("pause");	//Allows the system to pause for an input from the user.
}