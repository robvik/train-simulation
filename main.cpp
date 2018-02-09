//-------------------------------------------------------------------
// Filename: main.cpp
// Description: The startpoint of the program. This class simply calls the run-function from the UserInterface-class after creating an instance of the class.
// Robin Viktorsson 2017-06-01 13:46
// Version 1.0
//-------------------------------------------------------------------

//-------------------------------------------------------------------
// Including header-files
//-------------------------------------------------------------------
#include "UserInterface.h"

//------------------------------------------------------------------------------
// Function definition 
// Name: main
// Description: The starting-point of the program. Calls the run-function in UserInterface which presents the start-menu for the user.
//------------------------------------------------------------------------------
int main()
{

	UserInterface ui; //Create an instance of UserInterface-class...
	ui.run(); //...and start its run-function

	return 0;
}