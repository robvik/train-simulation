//-------------------------------------------------------------------
// Header filename: Simulation.h
// Description: The header-file for the simulation-class. Contains all necessary variables, instances of classes, queues, constructors and function definitions.
// Robin Viktorsson 2017-06-01 13:46
// Version 1.0
//-------------------------------------------------------------------
#ifndef SIMULATION_H
#define SIMULATION_H
#include <queue>
#include <vector>
#include <memory>

//-------------------------------------------------------------------
// Including header-files
//-------------------------------------------------------------------
#include "Event.h"
#include "EventComparison.h"

//------------------------------
// Classdefinition
//------------------------------
class Simulation {
private:

	//Variable and instances of the Time-class
	Time currentTime;	// Time for last event
	Time simulateToTime;	// Simulate to this time
	Time startTime;		// Starttime for simulation
	Time endTime;	// Endtime for simulation
	bool isSimulationFinished;	// Is simulation finished? (true if finished, false if not)
	bool wasStatisticsPrinted;  // Was statistics printed at the end of the simulation?

	//The Eventqueue which stores all the events
	std::priority_queue<std::shared_ptr<Event>, std::vector<std::shared_ptr<Event>>, EventComparison> eventQueue;

public:

	//Constructor
	Simulation() : eventQueue() { wasStatisticsPrinted = false; }

	//Methods
	void scheduleEvent(std::shared_ptr<Event> pNewEvent);
	void runNextInterval(Time pTimeInterval);
	void runNextEvent();
	void runAllEvents();

	//Setters
	void setStartTime(Time pStartTime) { startTime = pStartTime; }
	void setEndTime(Time pEndTime) { endTime = pEndTime; }
	void setSimulationFinished(bool pIsSimulationFinished) { isSimulationFinished = pIsSimulationFinished; }
	void setStatisticsPrinted(bool pWasStatisticsPrinted) { wasStatisticsPrinted = pWasStatisticsPrinted; }

	//Getters
	Time getCurrentTime() const { return currentTime; }		//Get time since last event
	Time getStartTime() const { return startTime; }		//Get starttime for simulation
	Time getEndTime() const { return endTime; }		//Get endtime for simulation
	Time getSimulateToTime() const { return simulateToTime; }	//Get time which simulation is running until
	bool getSimulationFinished() const { return isSimulationFinished; } //Get if simulation is done or not
	bool getStatisticsPrinted() const { return wasStatisticsPrinted; } //Get if statistics was printed or not already
};

#endif