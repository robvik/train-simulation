//-------------------------------------------------------------------
// Header filename: Vehicle.cpp
// Description: Contains functions related to the vehicle-class
// Robin Viktorsson 2017-06-01 13:46
// Version 1.0
//-------------------------------------------------------------------

//-------------------------------------------------------------------
// Including header-files
//-------------------------------------------------------------------
#include "Vehicle.h"

//------------------------------------------------------------------------------
// Function definition
// Name: setLocation
// Description: Sets the station-location of the vehicle
//------------------------------------------------------------------------------
void Vehicle::setLocation(std::shared_ptr<Station> pStation, Time pTime)
{

	if (pStation != nullptr) //Check if nullpointer
	{
		vehicleLocation.first = pStation; //Add position
		vehicleLocation.second.reset();  //Reset previous position
	}
}

//------------------------------------------------------------------------------
// Function definition
// Name: setLocation
// Description: Sets the train-location of the vehicle
//------------------------------------------------------------------------------
void Vehicle::setLocation(std::shared_ptr<Train> pTrain, Time pTime)
{
	if (pTrain != nullptr) //Check if nullpointer
	{
		vehicleLocation.first.reset(); //Add position
		vehicleLocation.second = pTrain; //Reset previous position
	}
}

//------------------------------------------------------------------------------
// Function definition
// Name: setLocation
// Description: Sets the train-location of the vehicle
// Returns: A string of the vehicles type
//------------------------------------------------------------------------------
std::string Vehicle::getVehicleTypeAsString()
{

	switch (type) {
	case VehicleType::SEAT_CARRIAGE: return "Seat carriage";
	case VehicleType::BED_CARRIAGE: return "Bed carriage";
	case VehicleType::OPEN_GOODSWAGON: return "Open Goodswagon";
	case VehicleType::CLOSED_GOODSWAGON: return "Closed Goodswagon";
	case VehicleType::ELECTRICITY_LOCOMOTIVE: return "Electric Locomotive";
	case VehicleType::DIESEL_LOCOMOTIVE: return "Diesel Locomotive";
	default: return "Unknown Vehicletype";
	}
}
