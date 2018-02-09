//-------------------------------------------------------------------
// Header filename: ClosedGoodsWagon.h
// Description: The header-file for the ClosedGoodsWagon-class. Contains all necessary variables, containers, constructor and function definitions.
//				Inherits from the Vehicle-class.
// Robin Viktorsson 2017-06-01 13:46
// Version 1.0
//-------------------------------------------------------------------
#ifndef CLOSED_GOODSWAGON_H
#define CLOSED_GOODSWAGON_H

//-------------------------------------------------------------------
// Including header-files
//-------------------------------------------------------------------
#include "Vehicle.h"

//------------------------------
// Classdefinition
//------------------------------
class ClosedGoodsWagon : public Vehicle {

private:

	//Variables
	int volume;

public:

	//Constructor
	ClosedGoodsWagon(int pID, int pType, int pVolume) : Vehicle(pID, pType), volume(pVolume) {};

	//Getters
	int getCubicMeters() { return volume; }

};
#endif