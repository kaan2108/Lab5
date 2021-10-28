/*
    Kaan Yuecel
    C++ Fall 2021
	Due: 10/27/21
	Lab 5 Number Guessing Game 
    Description : Write a number - guessing game in which the computer selects a random	
    number in the range of 0 to 100, and users get a maximum of 20 attempts to guess it.At
    the end of each game, users should be told whether they won or lost, and then be asked
    whether they want to play again.When the user quits, the program should output the
    total number of wins and losses. To make the game more interesting, the program
    should vary the wording of the messages that it outputs for winning, for losing, and for
    asking for another game.Create 10 different messages for each of these cases, and use
    random numbers to choose among them.This application should use at least one Do -
    While loop and at least one Switch statement. Write your C++ code using good style and
    documenting comments.You should use functions in your code as well.Your source
    code file should be called Lab5.cpp. 
*/

#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;


void WelcomeMsg();

//PreC: Program is compiled successfully
//PostC: Welcome message and Instructions

void SuccessMsg();

//PreC: The user has entered the correct guess
//PostC: A correct statement (out of 10) is showing up (User won)

void WrongGuessMsg();

//PreC: Incorrect guess entered as to what the random number is
//PostC: An incorrect statement (out of 10) is showing up (Wrong guess)

void AnotherGameMessage();

//PreC: The user has either won or lost the game.
//PostC: 1 of 10 messages is printed to the screen asking the user for another game.


void ScoreBoard(int totalGames, int wins, int losses);

//PreC: Variables totalGames, wins, and losses are initialized and passed to the function
//PostC: A scoreboard is printed that keeps track of total games played, wins, and losses

void GameOver();

//PreC: The user wants to leave the game (Return value of NewGameMenu must be false)
//PostC: A parting message is printed to the screen.


bool NumCompare();

//PreC: Program is compiled succesfully
//PostC: Determines if user won or lost the game.

bool NewGameMenu();

//PreC: The user has either won or lost the game
//PostC: Program gets boolean value to make a decision to either start a new game or stop the program


int main()
{
	
	int totalGames = 0;
	int wins = 0;
	int losses = 0;


    bool gameLoop = true;
	
	do
	{
		++totalGames; //Increasing number of games played
		ScoreBoard(totalGames, wins, losses); //Prints initial scoreboard.

		WelcomeMsg(); //Showing welcome message and instructions

		if (NumCompare()) //If NumCompare returns true, user has guessed the random number correctly and wins
		{
			++wins;
			SuccessMsg(); //Prints success message
			AnotherGameMessage(); //Prompts user for another game
			if (NewGameMenu()) //If user chooses a new game, NewGameMenu() returns true 
			{
				gameLoop = true; //Loop control set to true
				continue; //A new game is started
			}
			else //NewGameMenu() returns false and user has chosen to end program
			{
				gameLoop = false; //Loop control is set to false
				continue; //Game loop is exited
			}
		}
		else //User has lost the game by exceeding 20 guesses
		{
			++losses; //Loss count incremented
			if (NewGameMenu()) //If user chooses a new game, NewGameMenu() returns true
			{
				gameLoop = true; //Loop control set to true
				continue; //New game is started
			}
			else //NewGameMenu() returns false and user has chosen to end program execution
			{
				gameLoop = false; //Loop control set to false
				continue; //Game loop is exited
			}
		}
	} while (gameLoop);

	GameOver(); //Prints parting message
	ScoreBoard(totalGames, wins, losses); //Prints final score board.

	cout << "\nGoodbye...";


	return 0;
}

void ScoreBoard(int totalGames, int wins, int losses)
{
	cout << "\n\n---------------------------------------------------\n" << endl << endl;
	cout << "These are your stats so far: \n";
	cout << "Number of games played: " << totalGames << endl;
	cout << "Number of wins: " << wins << endl;
	cout << "Number of losses: " << losses << endl;
	cout << "\n\n---------------------------------------------------\n" << endl << endl;
}

void WelcomeMsg()
{
	
	cout << "Ladies and Gentleman, welcome to the NUMBER GUESSING GAME. \n" << endl;
	cout << "The computer has generated a random number between 1 and 100.\n";
	cout << "The user has 20 guesses to get the right number. \n";
	cout << "Here we go, please enter your first guess: ";
}

bool NumCompare()
{

	//Random number is generated
	int ranNum; //Stores random number generated by computer.
	srand(unsigned int(time(NULL))); //Seeds random number generator
	ranNum = rand() % 101; //Generates random numbers between 0 and 100. 
	

	int guessesLeft = 19; //This shows the user how many guesses they have left during the game
	int guessCount = 1; //Count control for folowing loop that gives player 20 chances to guess the random number.

	int guess;
	cin >> guess;

	do
	{
		if (!cin) //User enters an invalid data type
		{
			cout << "\n-------------------------------------------------------------------------\n";
			cout << "You entered an invalid data type.\n";
			cout << "Your input should be only integers between 1 inclusive and 100 inclusive.";
			cout << "\n-------------------------------------------------------------------------\n";
			cin.clear(); //This line clears the failure flag on the input stream.
			cin.ignore(1000, '\n'); //This line ignores anything else in the line that caused the input stream to fail. 1000 is arbitrary and skips 1000 chars in the input stream. Also uses new line char as a termination point.

			cout << "Try again: ";
			cin >> guess;
		}
		else if (isdigit(guess) && guess <= 0 || guess > 100) //User enters out of bounds number. isdigit() method is used to check if input is a number AND outside of the range on both sides.
		{
			cout << "\n----------------------------------------\n";
			cout << "That number is not in the range.\n";
			cout << "Your input should be between 1 and 100 \n";
			cout << "------------------------------------------\n\n";
			cout << "Please try again: ";
			cin >> guess;
		}
		else if (guess != ranNum) //User enters incorrect guess.
		{
			++guessCount;
			WrongGuessMsg(); //wrong guess returns a failure message.

			//Following if-else statement prints how many guesses the user has for each game.
			if (guessesLeft > 1)
				cout << "You have " << guessesLeft << " guesses left\n";
			else
				cout << "This is your last guess\n";
			guessesLeft--;

			cout << "Try again: ";
			cin >> guess;
		}
		else //User guesses random number.
		{
			return true; //NumCompare returns a true value to the main function
		}
	} while (guessCount < 20);

	cout << "\n\n---------------------------------------------------\n";
	cout << "I am sorry, but you are out of guesses!\n";
	cout << "The secret number was: " << ranNum;
	cout << "\n-----------------------------------------------------\n";
	AnotherGameMessage(); //Prints a random message prompting the user for another game.
	return false; //Returns false to the main function

}

void WrongGuessMsg()
{
	int failureMessageIndex = 0; //Used to generate random success messages in the switch statement below

	srand(unsigned int(time(NULL))); //Seeds random number generator
	failureMessageIndex = rand() % 10 + 1; //Generates random numbers between 1 and 10
	//Again, remainder of division will always land between 1 and one less than the divisor. So before adding one we have a range of 1-9, after adding one 1-10.

	switch (failureMessageIndex)
	{
	case 1:	cout << "\n\nI am sorry, wrong number\n";
		break;

	case 2:	cout << "\n\nMaybe the next one buddy\n";
		break;

	case 3:	cout << "\n\nNo no no no no\n";
		break;

	case 4:	cout << "\n\nKeep trying\n";
		break;

	case 5:	cout << "\n\nIn Germany we say: Falsche Nummer \n";
		break;

	case 6:	cout << "\n\nUnlucky\n";
		break;

	case 7:	cout << "\n\nHow disappointing\n";
		break;

	case 8:	cout << "\n\nSometimes you need to be wrong before being right\n";
		break;

	case 9:	cout << "\n\nI know you can do it\n";
		break;

	case 10: cout << "\n\nNext one please \n";
		break;

	default:	cout << "Other error";
	}
}

void SuccessMsg()
{
	int successMessageIndex = 0; //Used to generate random failure messages in the switch statement below

	srand(unsigned int(time(NULL))); //Seeds random number generator
	successMessageIndex = rand() % 10 + 1; //Generates random numbers between 1 and 10

	switch (successMessageIndex)
	{
	case 1:
		cout << "\n\n!!!!!!!!!\n";
		cout << "YESSIR YOU WON";
		cout << "\n!!!!!!!!!\n\n";
		break;

	case 2:
		cout << "\n\n!!!!!!!!!!\n";
		cout << "PERFECT!";
		cout << "\n!!!!!!!!!!\n\n";
		break;

	case 3:
		cout << "\n\n!!!!!!!!!!!!!!!!!\n";
		cout << "Right number, you won";
		cout << "\n!!!!!!!!!!!!!!!!!\n\n";
		break;

	case 4:
		cout << "\n\n!!!!!\n";
		cout << "Good job";
		cout << "\n!!!!!\n\n";
		break;

	case 5:
		cout << "\n\n!!!!!!!!!\n";
		cout << "Incredible, you won!";
		cout << "\n!!!!!!!!!\n\n";
		break;

	case 6:
		cout << "\n\n!!!!!!!!!!!!!!\n";
		cout << "That's the one";
		cout << "\n!!!!!!!!!!!!!!\n\n";
		break;

	case 7:
		cout << "\n\n!!!!!!!!!!\n";
		cout << "You win";
		cout << "\n!!!!!!!!!!\n\n";
		break;

	case 8:
		cout << "\n\n!!!!!!!\n";
		cout << "WOOOWWW ";
		cout << "\n!!!!!!!\n\n";
		break;

	case 9:
		cout << "\n\n!!!!!!!!!!\n";
		cout << "You did it";
		cout << "\n!!!!!!!!!!\n\n";
		break;

	case 10:
		cout << "\n\n!!!!!!!!!\n";
		cout << "HUGE W";
		cout << "\n!!!!!!!!!\n\n";
		break;

	default:
		cout << "Other error";
	}
}

void AnotherGameMessage()
{
	int MenuPromptIndex = 0; //Used to generate random failure messages in the switch statement below

	srand(unsigned int(time(NULL))); //Seeds random number generator
	MenuPromptIndex = rand() % 10 + 1; //Generates random numbers between 1 and 10

	switch (MenuPromptIndex)
	{
	case 1:
		cout << "\nTry again\n";
		break;

	case 2:
		cout << "\nPress 1 from the menu below if you want to play again\n";
		break;

	case 3:
		cout << "\nSelect an option from the following menu\n";
		break;

	case 4:
		cout << "\nTo exit the program, press 2 \n";
		break;

	case 5:
		cout << "\nYou can play again if you want play by pressing '1'\n";
		break;

	case 6:
		cout << "\nIf you press 1 at the following menu a new number will be generated and you can play again.\n";
		break;

	case 7:
		cout << "\nI hope you enjoyed to play!\n";
		break;

	case 8:
		cout << "\nYou can play again if you want\n";
		break;

	case 9:
		cout << "\nHow about another game?\n";
		break;

	case 10:
		cout << "\nGive it another shot and play again.\n";
		break;

	default:
		cout << "Error";
	}
}

bool NewGameMenu()
{
	char choice; //Stores user's selection in menu
	bool switchLoop = true; //Loop control for do-while statement menu is nested in.
	bool newGame = true; //Stores return value of function - used to determine if new game is initiated or user terminates program. 

	do {
		cout << "\n\n****\n";
		cout << "The MENU\n";
		cout << "****\n";
		cout << "Please make a selection from the menu below:\n";
		cout << "If you want a new game press 1\n";
		cout << "If you want to quit press 2\n";

		cout << "Enter your choice: ";
		cin >> choice;
		cout << "\n\n"; //Space before next game.

		switch (choice) {
		case '1':
			newGame = true; //Return value for New_Game_Menu()
			switchLoop = false; //Breaks out of menu loop to return value
			break;

		case '2':
			newGame = false; //Return value for New_Game_Menu()
			switchLoop = false; //Breaks out of menu loop to return value
			break;

		default:	cout << "Invaild choice - you must enter either 1 or 2\n";
			break;
		}
	} while (switchLoop);

	return newGame; //Returns true or false to expression called from in main.
}

void GameOver() //Prints a parting message to the user.
{
	cout << "You quit the game.\n";
	cout << "Here are your final stats:\n";
}
