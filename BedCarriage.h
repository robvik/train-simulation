//-------------------------------------------------------------------
// Header filename: BedCarriage.h
// Description: The header-file for the BedCarriage-class. Contains all necessary variables, containers, constructor and function definitions.
//				Inherits from the Vehicle-class.
// Robin Viktorsson 2017-06-01 13:46
// Version 1.0
//-------------------------------------------------------------------
#ifndef BEDCARRIAGE_H
#define BEDCARRIAGE_H

//-------------------------------------------------------------------
// Including header-files
//-------------------------------------------------------------------
#include "Vehicle.h"

//------------------------------
// Classdefinition
//------------------------------
class BedCarriage : public Vehicle {

private:

	//Variables
	int nrOfBeds;

public:

	//Constructor
	BedCarriage(int pID, int pType, int pNrOfBeds) : Vehicle(pID, pType), nrOfBeds(pNrOfBeds) {};

	//Getters
	int getNumBeds() { return nrOfBeds; }

};
#endif