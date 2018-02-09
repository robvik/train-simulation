//-------------------------------------------------------------------
// Header filename: OpenGoodsWagon.h
// Description: The header-file for the OpenGoodsWagon-class. Contains all necessary variables, containers, constructor and function definitions.
//				Inherits from the Vehicle-class.
// Robin Viktorsson 2017-06-01 13:46
// Version 1.0
//-------------------------------------------------------------------
#ifndef OPEN_GOODSWAGON_H
#define OPEN_GOODSWAGON_H

//-------------------------------------------------------------------
// Including header-files
//-------------------------------------------------------------------
#include "Vehicle.h"

//------------------------------
// Classdefinition
//------------------------------
class OpenGoodsWagon : public Vehicle {

private:

	//Variables
	int weightCapacity;
	int squareMeters;

public:

	//Constructor
	OpenGoodsWagon(int pID, int pType, int pWeightCapacity, int pSquareMeters) : Vehicle(pID, pType), weightCapacity(pWeightCapacity), squareMeters(pSquareMeters) {};

	//Getters
	int getWeightCapacity() { return weightCapacity; }
	int getSquareMeters() { return squareMeters; }

};
#endif