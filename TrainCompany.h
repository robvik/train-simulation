//-------------------------------------------------------------------
// Header filename: TrainCompany.h
// Description: The header-file for the TrainCompany-class. Contains all necessary variables, containers, conustructor and function definitions.
// Robin Viktorsson 2017-06-01 13:46
// Version 1.0
//-------------------------------------------------------------------
#ifndef TRAINCOMPANY_H
#define TRAINCOMPANY_H
#include <queue>
#include <vector>
#include <fstream>
#include <memory>
#include <map>

//-------------------------------------------------------------------
// Including header-files
//-------------------------------------------------------------------
#include "Station.h"
#include "Vehicle.h"
#include "Train.h"
#include "VehicleFactory.h"
#include "Simulation.h"
#include "Statistics.h"

//------------------------------
// Classdefinition
//------------------------------
class TrainCompany {

private:

	//Simulation-pointer
	std::shared_ptr<Simulation> simulator;

	//Maps
	std::map<std::string, std::shared_ptr<Station>> stations; //all the stations
	std::map<int, std::shared_ptr<Train>> trains; //all the trains
	std::map<int, std::weak_ptr<Vehicle>> vehicles; //all the vehicles 
	std::map<std::string, std::map<std::string, double>> distances; //distances between all routes

	//Instances of other classes
	Statistics statistics;
	Time time;

	//Loglevel
	int logLevel;

	//Initializing setup
	void prepareTrains();
	void prepareTrainStations();
	void prepareTrainRoutes();

public:

	//Constructors and destructor
	TrainCompany() {}; //Make sure the correct constructor is running, otherwise there might be issues
	TrainCompany(std::shared_ptr<Simulation> pSimulator);
	~TrainCompany() {};

	//Methods
	void printTimeTable(); //Print the timetable for all trains
	void printStatistics(); //Show statistics
	void printAllVehicles();	//Print information about all vehicles
	void printVehicleByID(int pVehicleID); //Finds and prints information about a specific vehicle based on ID
	void printTrainByID(int pTrainID);	//Prints information about a specific train based on train id
	void printAllTrains(); //Prints information about all trains
	void printStationNames(); //Prints the names of all stations
	void printStation(std::string pStationName); //Prints information about a specific station based on its name
	void printAllStations(); //Prints all information about all stations

	//Event-related methods
	bool assembleTrain(std::shared_ptr<Train> pTrain);	//Tries to assemble the train
	void makeTrainReady(std::shared_ptr<Train> pTrain);	//Make sure the train is ready for takeoff!
	Time startTrain(std::shared_ptr<Train> pTrain);	//Start a train
	void trainArrives(std::shared_ptr<Train> pTrain);	//Train is arriving
	void disassembleTrain(std::shared_ptr<Train> pTrain);	//Dissamble the train

	//Setters
	void setLogLevel(int pLogLevel) { logLevel = pLogLevel; }

	//Getters
	std::map<int, std::shared_ptr<Train>> getTrains() { return trains; } //Returns all the trains
};
#endif