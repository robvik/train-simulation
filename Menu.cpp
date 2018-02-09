//-------------------------------------------------------------------
// Filename: Menu.cpp
// Description: The menu-class which handles everything related to the menu and its items
// Robin Viktorsson 2017-06-01 12:46
// Version 1.1
//-------------------------------------------------------------------
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <sstream>

//------------------------------------------------------------------------------
// Including header-files
//------------------------------------------------------------------------------
#include "Menu.h"
#include "MenuItem.h"

//------------------------------------------------------------------------------
// Function definition 
// Name: addItem
// Description: Adds an item (choice) to the menu
//------------------------------------------------------------------------------
void Menu::addItem(std::string pMenuText)
{
	MenuItem menuItem;
	menuItem.setMenuText(pMenuText);

	menuItems.push_back(menuItem);
}

//------------------------------------------------------------------------------
// Function definition 
// Name: changeItem
// Description: Allows the user to make changes to an menuitems
//------------------------------------------------------------------------------
void Menu::changeItem(std::string pMenuText, int pElement) {

	menuItems.at(pElement).setMenuText(pMenuText);
}

//------------------------------------------------------------------------------
// Function definition 
// Name: printMenuItems
// Description: Prints all the items (choices) in the menu
//------------------------------------------------------------------------------
void Menu::printMenuItems()
{

	std::cout << std::endl << header << std::endl;

	int number = 1;
	for (auto menuChoice : menuItems) {

		std::cout << number << ". " << menuChoice.getMenuText() << std::endl;
		number++;
	}
}

//------------------------------------------------------------------------------
// Function definition 
// Name: getMenuChoice
// Description: Allows the user to make a menu-choice
// Returns: Integer - The choice of the user
//------------------------------------------------------------------------------
int Menu::getMenuChoice(int max)
{
	int menuChoice;
	while ((std::cout << "Menuchoice: ") && (!(std::cin >> menuChoice) || menuChoice < 1 || menuChoice > max))
	{
		std::cout << "Please choose an valid option. Max number is: " << max << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	return menuChoice;
}