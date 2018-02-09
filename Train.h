//-------------------------------------------------------------------
// Header filename: Train.h
// Description: The header-file for the Train-class. Contains all necessary variables, containers, conustructor and function definitions.
// Robin Viktorsson 2017-05-02 13:46
// Version 1.0
//-------------------------------------------------------------------
#ifndef TRAIN_H
#define TRAIN_H
#include <iostream>
#include <vector>
#include <memory>
#include <string>

//-------------------------------------------------------------------
// Including header-files
//-------------------------------------------------------------------
#include "Vehicle.h"
#include "Station.h"
#include "Time.h"

//------------------------------
// Enum
//------------------------------
enum TrainState { NOT_ASSEMBLED = 0, INCOMPLETE = 1, ASSEMBLED = 2, READY = 3, RUNNING = 4, ARRIVED = 5, FINISHED = 6 };

//------------------------------
// Classdefinition
//------------------------------
class Train : public std::enable_shared_from_this<Train> {

private:

	//Vector
	std::vector<std::pair<int, std::shared_ptr<Vehicle>>> vehicles;

	//Variables and smart-pointers
	int trainID;
	std::string depStation;
	std::string destStation;
	std::shared_ptr<Station> depLocation;
	std::shared_ptr<Station> destLocation;
	int maxSpeed;
	double avgSpeed;
	TrainState state;

	//Times 
	Time estimatedStartTime;
	Time estimatedArrivalTime;
	Time startTime;
	Time arrivalTime;

public:

	//Constructors and destructor
	Train() {};
	Train(int pTrainID, std::string pDepStation, std::string pDestStation, Time pDepTime, Time pArrTime, int pMaxSpeed, std::string pVehicles);
	~Train() {};

	//Methods
	bool assembleVehicles();
	void dissambleVehicles();

	//Setters
	void setTrainID(int pTrainID) { trainID = pTrainID; }
	void setAverageSpeed(double pAvgSpeed) { avgSpeed = pAvgSpeed; }
	void setMaxSpeed(int pMaxSpeed) { maxSpeed = pMaxSpeed; }
	void setTrainState(TrainState pTrainState) { state = pTrainState; }
	void setDestLocation(std::shared_ptr<Station> pDestLocation) { destLocation = pDestLocation; }
	void setDepLocation(std::shared_ptr<Station> pDepLocation) { depLocation = pDepLocation; }

	//Setters (time-related)
	void setStartTime(Time pTime) { startTime = pTime; }
	void setArrivalTime(Time pTime) { arrivalTime = pTime; }

	//Getters
	int getTrainID() { return trainID; }
	std::string getDepStation() { return depStation; }
	std::string getDestStation() { return destStation; }
	int getMaxSpeed() { return maxSpeed; }
	double getAvgSpeed() { return avgSpeed; }
	TrainState getTrainState() { return state; }
	std::string getTrainStateAsString();
	std::vector<std::pair<int, std::shared_ptr<Vehicle>>> getVehicles() const { return vehicles; }

	//Getters (time-related)
	Time getEstimatedStartTime() const { return estimatedStartTime; }
	Time getEstimatedArrivalTime() const { return estimatedArrivalTime; }
	Time getStartTime() const { return startTime; }
	Time getArrivalTime() const { return arrivalTime; }
};
#endif