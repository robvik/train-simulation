//-------------------------------------------------------------------
// Header filename: VehicleComparison.h
// Description: The header-file for the VehicleComparison-class. Contains the one and only operator overloading-function
// Robin Viktorsson 2017-06-01 13:46
// Version 1.0
//-------------------------------------------------------------------
#ifndef VEHICLECOMPARISON_H
#define VEHICLECOMPARISON_H

//-------------------------------------------------------------------
// Including header-files
//-------------------------------------------------------------------
#include "Vehicle.h"

//------------------------------
// Classdefinition
// Description: Compares the ID between two vehicles
// Returns: True if the id of the vehicle to the left is greater than the id of the vehicle to the right, otherwise false
//------------------------------
class VehicleComparison {
public:
	bool operator() (std::shared_ptr<Vehicle> compareThis, std::shared_ptr<Vehicle> withThis) {
		return compareThis->getID() > withThis->getID();
	};
};
#endif