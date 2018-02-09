//-------------------------------------------------------------------
// Header filename: Station.cpp
// Description: Station.cpp handles function related to whats happening at the trainstation. Examples: Adds a train and vehicles to the station aswell as removing it.
// Robin Viktorsson 2017-06-01 13:46
// Version 1.0
//-------------------------------------------------------------------
#include <algorithm>

//-------------------------------------------------------------------
// Including header-files
//-------------------------------------------------------------------
#include "Station.h"
#include "Train.h"

//------------------------------------------------------------------------------
// Function definition 
// Name: addVehicle
// Description: Adds a vechicle to the vehicles-container
// Parameter: Smart-pointer to the vehicle which is going to be added to the vehicles-container
//------------------------------------------------------------------------------
void Station::addVehicle(std::shared_ptr<Vehicle> pVehicle)
{
	vehicles.insert(pVehicle);
}

//------------------------------------------------------------------------------
// Function definition 
// Name: requestVehicle
// Description: Searches and request a specific vehicletype from the station. If the vehicletype was found, then its removed from the station
// Parameter: Smart-pointer to the vehicle which is going to be added to the vehicles-container
// Returns: True if vehicle was found and removed from the station, otherwise false
//------------------------------------------------------------------------------
bool Station::requestVehicle(int pVehicleType, std::shared_ptr<Vehicle>& pVehicle)
{

	std::set<std::shared_ptr<Vehicle>, VehicleComparison>::iterator it;
	for (it = vehicles.begin(); it != vehicles.end(); it++) { //Iteratre through all vehicles...
		if (pVehicleType == (*it)->getVehicleType()) { //...and see if you can find the requested type
			if (it != vehicles.end()) {
				pVehicle = *it; //If so pass it to pVehicle...
				vehicles.erase(it); //...and erase it and return true
				return true;
			}
		}
	}

	return false;	//return false if vehicletype wasnt found
}

//------------------------------------------------------------------------------
// Function definition 
// Name: addTrain
// Description: Add train to the map trains
//------------------------------------------------------------------------------
void Station::addTrain(std::shared_ptr<Train> pTrain) {

	trains[pTrain->getTrainID()] = pTrain;
}