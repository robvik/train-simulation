//-------------------------------------------------------------------
// Header filename: Train.cpp
// Description: Handles functions related to the Train-class. Such as adding, assemble and dissamble vehicles to/from a train
// Robin Viktorsson 2017-06-01 13:46
// Version 1.0
//-------------------------------------------------------------------
#include <sstream>

//-------------------------------------------------------------------
// Including header-files
//-------------------------------------------------------------------
#include "Train.h"

//------------------------------------------------------------------------------
// Constructor
// Description: Adds the vehicles to the vehicles-container
//------------------------------------------------------------------------------
Train::Train(int pTrainID, std::string pDepStation, std::string pDestStation, Time pDepTime, Time pArrTime, int pMaxSpeed, std::string pVehicles) : trainID(pTrainID), depStation(pDepStation), destStation(pDestStation), estimatedStartTime(pDepTime), startTime(pDepTime), estimatedArrivalTime(pArrTime), arrivalTime(pArrTime), maxSpeed(pMaxSpeed), avgSpeed(0), state(NOT_ASSEMBLED)
{

	int vehicleType;
	std::istringstream iss(pVehicles);
	while (iss >> vehicleType) //Write all the content
	{
		//Add the vehicletype and an empty pointer to the vehicle
		vehicles.push_back(std::make_pair(vehicleType, std::shared_ptr<Vehicle>(nullptr)));

		if (iss.eof() || iss.bad()) //Then we dont need to continue to read
			break;
	}
}

//------------------------------------------------------------------------------
// Function definition 
// Name: assembleVehicles
// Description: Tries to assemble all the locomotives, carriages and wagons to a train
//------------------------------------------------------------------------------
bool Train::assembleVehicles()
{
	bool vehicleRequestSuccess = true;
	bool allVehiclesAssembled = true;

	for (auto &vehicle : vehicles) //Iterate through all available vehicles
	{
		if (vehicle.second == nullptr) //If vehicle has not been loaded
		{
			vehicleRequestSuccess = depLocation->requestVehicle(vehicle.first, vehicle.second); //Search for vehicle
			if (vehicleRequestSuccess) //Change the location of the vehicle if it wasnt found
				vehicle.second->setLocation(shared_from_this(), getStartTime() - 30); //It should be 30-minutes before estimatedstarttime
		}

		if (!vehicleRequestSuccess) //If the vehicle was not found...
			allVehiclesAssembled = false; //...then change the bool
	}

	return allVehiclesAssembled; //Return whetever all vechicles has been loaded or not
}

//------------------------------------------------------------------------------
// Function definition 
// Name: disassembleVehicles
// Description: Tries to disassemble all the vehicles
//------------------------------------------------------------------------------
void Train::dissambleVehicles()
{
	for (auto &vehicle : vehicles) //Iterate through all available vehicles
	{
		destLocation->addVehicle(vehicle.second);		//Add vehicle to the station
		vehicle.second->setLocation(destLocation, getArrivalTime() + 20); //Change the vehicles location to the correct station. It should be 20 minutes after arrivaltime
		vehicle.second.reset(); //Remove the vehicle from the train
	}
}

//------------------------------------------------------------------------------
// Function definition 
// Name: getTrainStateAsString
// Description: Translates the trainstate, which is an integer, to a string which is returned
//------------------------------------------------------------------------------
std::string Train::getTrainStateAsString()
{
	switch (state) {
	case TrainState::NOT_ASSEMBLED: return "NOT ASSEMBLED";
	case TrainState::INCOMPLETE: return "INCOMPLETE";
	case TrainState::ASSEMBLED: return "ASSEMBLED";
	case TrainState::READY: return "READY";
	case TrainState::RUNNING: return "RUNNING";
	case TrainState::ARRIVED: return "ARRIVED";
	case TrainState::FINISHED: return "FINISHED";
	default: return "Unknown Trainstate";
	}
}
