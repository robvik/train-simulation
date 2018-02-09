//-------------------------------------------------------------------
// Header filename: SeatCarriage.h
// Description: The header-file for the SeatCarriage-class. Contains all necessary variables, containers, constructor and function definitions.
//				Inherits from the Vehicle-class.
// Robin Viktorsson 2017-06-01 13:46
// Version 1.0
//-------------------------------------------------------------------
#ifndef SEATCARRIAGE_H
#define SEATCARRIAGE_H

//-------------------------------------------------------------------
// Including header-files
//-------------------------------------------------------------------
#include "Vehicle.h"

//------------------------------
// Classdefinition
//------------------------------
class SeatCarriage : public Vehicle {

private:

	//Variables
	int nrOfSeats;
	int internet;

public:

	//Constructor
	SeatCarriage(int pID, int pType, int pNrOfSeats, int pInternet) : Vehicle(pID, pType), nrOfSeats(pNrOfSeats), internet(pInternet) {};

	//Getters
	int getNumSeats() { return nrOfSeats; }
	bool hasInternet() { if (internet == 1) return true; else return false; }

};
#endif