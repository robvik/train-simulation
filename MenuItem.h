//------------------------------
// Header filename: MenuItem.h
// Description: The header-file for the MenuItem-class. Contains all necessary variables, constructors, setters and getters.
// Author: Robin Viktorsson 2017-06-01 08:57
// Version 1.1
//------------------------------
#ifndef MENUITEM_H
#define MENUITEM_H
#include <vector>

//------------------------------
// Classdefinition
//------------------------------
class MenuItem {

private:

	//Variables
	std::string menuText;

public:

	//Constructors
	MenuItem() {};
	MenuItem(std::string pMenuText) : menuText(pMenuText) {};

	//Setters
	void setMenuText(std::string pMenuText) { menuText = pMenuText; }

	//Getters
	std::string getMenuText() const { return menuText; }
};
#endif