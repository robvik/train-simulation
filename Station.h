//-------------------------------------------------------------------
// Header filename: Station.h
// Description: The header-file for the station-class. Contains variables, function definitions, setters and getters aswell as forward declarations...
// Robin Viktorsson 2017-06-01 13:46
// Version 1.0
//-------------------------------------------------------------------
#ifndef STATION_H
#define STATION_H

#include <vector>
#include <memory>
#include <map>
#include <set>
#include <string>

//-------------------------------------------------------------------
// Including header-files
//-------------------------------------------------------------------
#include "VehicleComparison.h"
#include "Vehicle.h"

//------------------------------
// Forward declarations
//------------------------------
class VehicleComparison;
class Train;

//------------------------------
// Classdefinition
//------------------------------
class Station {

private:

	//Variables and containers
	std::string stationName;
	std::map<int, std::shared_ptr<Train>> trains;
	std::set<std::shared_ptr<Vehicle>, VehicleComparison> vehicles;

public:

	//Constructor
	Station() {};
	Station(std::string pStationName) { stationName = pStationName; };
	~Station() {};

	//Methods
	void addTrain(std::shared_ptr<Train> pTrain);
	void addVehicle(std::shared_ptr<Vehicle> pVehicle);
	void removeTrain(int pTrainID) { auto it = trains.find(pTrainID); if (it != trains.end()) { trains.erase(pTrainID); } };
	bool requestVehicle(int pVehicleType, std::shared_ptr<Vehicle> &pVehicle);

	//Getters
	std::string getName() { return stationName; }
	std::map<int, std::shared_ptr<Train>> getTrains() const { return trains; }
	std::set<std::shared_ptr<Vehicle>, VehicleComparison> getVehicles() const { return vehicles; }

};
#endif