//-------------------------------------------------------------------
// Header filename: Statistics.cpp
// Description: This file handles the functions related to writing logs and statistics which can be presented to the user or inserted in files.
// Robin Viktorsson 2017-06-01 13:46
// Version 1.0
//-------------------------------------------------------------------
#include <fstream>
#include <iostream>
#include <sstream>

//-------------------------------------------------------------------
// Including header-files
//-------------------------------------------------------------------
#include "Statistics.h"

//------------------------------------------------------------------------------
// Function definition 
// Name: writeToLogs
// Description: Writes a certain string to a logfile
// Parameter: Parameter contains a string of the message which is suppose to be added to the logfile
//------------------------------------------------------------------------------
void Statistics::writeToLogs(std::string pLogText)
{
	std::ofstream myfile;
	if (logsfirstTimeOpen) { //If its the first time this file opens it should overwrite existing content...
		myfile.open("Trainsim.log", std::ios::out | std::ios::trunc);
		logsfirstTimeOpen = false;
	}
	else
		myfile.open("Trainsim.log", std::ios_base::app | std::ios::out); //...otherwise we append it

	if (myfile.is_open()) { //Make sure file is opened
		myfile << pLogText << std::endl;
		myfile.close();
	}
	else
		throw std::runtime_error("Unable to open file Trainsim.log");
}

//------------------------------------------------------------------------------
// Function definition 
// Name: countVehiclesAtStation
// Description: Counts/keeps track of the amount of vehicles at each station at the start of the program
// Parameter: The name of the station of which the amount of vehicles should be increased
//------------------------------------------------------------------------------
void Statistics::countVehiclesAtStation(std::string pStation)
{

	if (vehicles.find(pStation) == vehicles.end()) //Try to find the station
		vehicles.insert(std::pair<std::string, int>(pStation, 1)); //If station wasnt found, then add it to the map
	else
		vehicles[pStation] += 1; //Increase it by 1 if it was found

}