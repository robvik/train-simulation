//-------------------------------------------------------------------
// Header filename: DieselLocomotive.h
// Description: The header-file for the DieselLocomotive-class. Contains all necessary variables, containers, constructor and function definitions.
//				Inherits from the Vehicle-class.
// Robin Viktorsson 2017-06-01 13:46
// Version 1.0
//-------------------------------------------------------------------
#ifndef DIESEL_LOCOMOTIVE_H
#define DIESEL_LOCOMOTIVE_H

//-------------------------------------------------------------------
// Including header-files
//-------------------------------------------------------------------
#include "Vehicle.h"

//------------------------------
// Classdefinition
//------------------------------
class DieselLocomotive : public Vehicle {

private:

	//Variables
	int maxSpeed;
	int fuelConsumption;

public:

	//Constructor
	DieselLocomotive(int pID, int pType, int pMaxSpeed, int pFuelConsumption) : Vehicle(pID, pType), maxSpeed(pMaxSpeed), fuelConsumption(pFuelConsumption) {};

	//Getters
	int getMaxSpeed() { return maxSpeed; }
	int getFuelConsumption() { return fuelConsumption; }
};
#endif