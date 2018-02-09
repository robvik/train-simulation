//-------------------------------------------------------------------
// Header filename: VehicleFactory.cpp
// Description: Contains the one and only function related to VehicleFactory.
// Robin Viktorsson 2017-06-01 13:46
// Version 1.0
//-------------------------------------------------------------------
#include <iostream>
#include <memory>

//-------------------------------------------------------------------
// Including header-files
//-------------------------------------------------------------------
#include "VehicleFactory.h"
#include "Vehicle.h"

//------------------------------------------------------------------------------
// Function definition
// Name: buildVehicle
// Description: This function is inspired by factory design pattern and builds the correct vehicle based on vehicletype which is sent as parameter
// Return: An shared-pointer to the type of vehicle thats going to be built
//------------------------------------------------------------------------------
std::shared_ptr<Vehicle> VehicleFactory::buildVehicle(int pID, int pType, int param0, int param1) {

	switch (pType) {
	case VehicleType::SEAT_CARRIAGE: return std::shared_ptr<Vehicle>(new SeatCarriage(pID, pType, param0, param1));
	case VehicleType::BED_CARRIAGE: return std::shared_ptr<Vehicle>(new BedCarriage(pID, pType, param0));
	case VehicleType::OPEN_GOODSWAGON: return std::shared_ptr<Vehicle>(new OpenGoodsWagon(pID, pType, param0, param1));
	case VehicleType::CLOSED_GOODSWAGON: return std::shared_ptr<Vehicle>(new ClosedGoodsWagon(pID, pType, param0));
	case VehicleType::ELECTRICITY_LOCOMOTIVE: return std::shared_ptr<Vehicle>(new ElectricityLocomotive(pID, pType, param0, param1));
	case VehicleType::DIESEL_LOCOMOTIVE: return std::shared_ptr<Vehicle>(new DieselLocomotive(pID, pType, param0, param1));
	default:
		throw std::runtime_error("VehicleType could not be found");
	}
}