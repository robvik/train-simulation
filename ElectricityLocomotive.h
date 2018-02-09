//-------------------------------------------------------------------
// Header filename: ElectricityLocomotive.h
// Description: The header-file for the ElectricityLocomotive-class. Contains all necessary variables, containers, constructor and function definitions.
//				Inherits from the Vehicle-class.
// Robin Viktorsson 2017-06-01 13:46
// Version 1.0
//-------------------------------------------------------------------
#ifndef ELECTRICITY_LOCOMOTIVE_H
#define ELECTRICITY_LOCOMOTIVE_H

//-------------------------------------------------------------------
// Including header-files
//-------------------------------------------------------------------
#include "Vehicle.h"

//------------------------------
// Classdefinition
//------------------------------
class ElectricityLocomotive : public Vehicle {

private:

	//Variables
	int maxSpeed;
	int wattage;

public:

	//Constructor
	ElectricityLocomotive(int pID, int pType, int pMaxSpeed, int pWattage) : Vehicle(pID, pType), maxSpeed(pMaxSpeed), wattage(pWattage) {};

	//Getters
	int getMaxSpeed() { return maxSpeed; }
	int getWattage() { return wattage; }

};
#endif