//-------------------------------------------------------------------
// Header filename: Statistics.h
// Description: The header-file for the statistics-class. Contains all necessary variables, containers, conustructor and function definitions.
// Robin Viktorsson 2017-06-01 13:46
// Version 1.0
//-------------------------------------------------------------------
#ifndef STATISTICS_H
#define STATISTICS_H
#include <vector>
#include <memory>
#include <map>
#include <set>
#include <string>

//-------------------------------------------------------------------
// Including header-files
//-------------------------------------------------------------------
#include "Time.h"

//------------------------------
// Classdefinition
//------------------------------
class Statistics {

private:

	//Variables
	bool logsfirstTimeOpen;

	//Maps and lists
	std::map<std::string, int> vehicles;
	std::vector<std::string> delayedTrains;
	std::vector<std::string> trainsInTime;

	//Times
	Time totalDelay;

public:

	//Constructor
	Statistics() : totalDelay(0, 0) { logsfirstTimeOpen = true; };

	//Methods
	void writeToLogs(std::string pLogText);
	void countVehiclesAtStation(std::string pStation);
	void addTrainInTime(std::string pTrainInTime) { trainsInTime.push_back(pTrainInTime); }
	void addDelayedTrain(std::string pDelayedTrain) { delayedTrains.push_back(pDelayedTrain); }

	//Setters
	void setTotalDelay(int pDelay) { totalDelay = totalDelay + pDelay; }

	//Getters
	Time getTotalDelay() { return totalDelay; }
	std::vector<std::string> getDelayedTrains() { return delayedTrains; }
	std::vector<std::string> getTrainsInTime() { return trainsInTime; }
	std::map<std::string, int> getVehiclesAmount() { return vehicles; }
};
#endif