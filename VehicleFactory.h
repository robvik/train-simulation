//-------------------------------------------------------------------
// Header filename: VehicleFactory.h
// Description: The header-file for the VehicleFactory-class. Contains all necessary conustructor, destructor and function definitions.
// Robin Viktorsson 2017-06-01 13:46
// Version 1.0
//-------------------------------------------------------------------
#ifndef VEHICLEFACTORY_H
#define VEHICLEFACTORY_H
#include <iostream>
#include <vector>

//-------------------------------------------------------------------
// Including header-files
//-------------------------------------------------------------------
#include "BedCarriage.h"
#include "SeatCarriage.h"
#include "ClosedGoodsWagon.h"
#include "OpenGoodsWagon.h"
#include "ElectricityLocomotive.h"
#include "DieselLocomotive.h"

//------------------------------
// Classdefinition
//------------------------------
class VehicleFactory {

public:

	//Constructor and destructors
	VehicleFactory() {};
	~VehicleFactory() {};

	//Methods
	std::shared_ptr<Vehicle> static buildVehicle(int pID, int pType, int param0, int param1);

};
#endif