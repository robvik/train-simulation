//------------------------------
// Header filename: Menu.h
// Robin Viktorsson 2017-06-01 08:57
// Description: The header-file for the menu-class. Contains all variables, vectors, constructor, and function definitions necessary for this class.
// Version: 1.1
//------------------------------
#ifndef MENU_H
#define MENU_H
#include <vector>

//-------------------------------------------------------------------
// Including header-files
//-------------------------------------------------------------------
#include "MenuItem.h"

//------------------------------
// Classdefinition
//------------------------------
class Menu {

private:

	//Variables and vectors
	std::string header;
	std::vector<MenuItem> menuItems;

public:

	//Constructor
	Menu() {};

	//Methods
	void addItem(std::string menuText);
	void changeItem(std::string menuText, int elem);
	void printMenuItems();

	//Setters
	void setHeader(std::string pHeader) { header = pHeader; };

	//Getters
	int getMenuChoice(int max);
	std::vector<MenuItem> &getMenuItem() { return menuItems; }

};
#endif