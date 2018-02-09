//-------------------------------------------------------------------
// Header filename: Vehicle.h
// Description: The header-file for the Vehicle-class. Contains all necessary variables, containers, conustructor and function definitions.
// Robin Viktorsson 2017-06-01 13:46
// Version 1.0
//-------------------------------------------------------------------
#ifndef VEHICLE_H
#define VEHICLE_H
#include <iostream>
#include <vector>
#include <memory>

//-------------------------------------------------------------------
// Including header-files
//-------------------------------------------------------------------
#include "Time.h"
#include "Statistics.h"

//------------------------------
// Enum
//------------------------------
enum VehicleType { SEAT_CARRIAGE = 0, BED_CARRIAGE = 1, OPEN_GOODSWAGON = 2, CLOSED_GOODSWAGON = 3, ELECTRICITY_LOCOMOTIVE = 4, DIESEL_LOCOMOTIVE = 5 };

//------------------------------
// Forward Declarations
//------------------------------
class Station;
class Train;

//------------------------------
// Classdefinition
//------------------------------
class Vehicle {

private:

	//Variables and containers
	int id;
	int type;
	std::pair<std::weak_ptr<Station>, std::weak_ptr<Train>> vehicleLocation;
	std::vector<std::string> vehicleInfo;

public:

	//Constructors and destructor
	Vehicle() {};
	Vehicle(int pID, int pType) { id = pID; type = pType; };
	~Vehicle() {};

	//Setters
	void setLocation(std::shared_ptr<Station>, Time time);
	void setLocation(std::shared_ptr<Train>, Time time);

	//Getters (non-virtual)
	int getID() { return id; }
	int getVehicleType() { return type; }
	std::string getVehicleTypeAsString();
	std::vector<std::string> getVehicleInfo() { return vehicleInfo; }
	std::pair<std::weak_ptr<Station>, std::weak_ptr<Train>> getLocation() const { return vehicleLocation; }

	//Getters (virtuals)
	virtual int getMaxSpeed() { return 0; }
	virtual int getNumBeds() { return 0; }
	virtual int getNumSeats() { return 0; }
	virtual int getFuelConsumption() { return 0; }
	virtual int getWattage() { return 0; }
	virtual int getSquareMeters() { return 0; }
	virtual int getWeightCapacity() { return 0; }
	virtual int getCubicMeters() { return 0; }
	virtual bool hasInternet() { return false; }

};
#endif