//-------------------------------------------------------------------
// Header filename: Simulation.cpp
// Robin Viktorsson 2017-06-01 13:46
// Description: This class handles simulation-related functions. Such as running the next events or all of them at once.
//				In other words it schedules and pops events from the eventqueue
// Version 1.0
//-------------------------------------------------------------------
#include <memory>

//-------------------------------------------------------------------
// Including header-files
//-------------------------------------------------------------------
#include "Simulation.h"
#include "Time.h"
#include "Event.h"

//------------------------------------------------------------------------------
// Function definition 
// Name: scheduleEvent
// Description: Adds another event in the eventque
// Parameter: Smart-pointer to the event thats gonna be added
//------------------------------------------------------------------------------
void Simulation::scheduleEvent(std::shared_ptr<Event> pNewEvent)
{
	eventQueue.push(pNewEvent);
}

//------------------------------------------------------------------------------
// Function definition 
// Name: runNextInterval
// Description: The simulation will run forward. How much forward is dependent on the parameter
// Parameter: Instance of the Time-class which contains information about how much forward the simulation should go
//------------------------------------------------------------------------------
void Simulation::runNextInterval(Time pTimeInterval)
{
	simulateToTime = simulateToTime + pTimeInterval; //The simulation is forwarded to this time.

	while (!eventQueue.empty() && !isSimulationFinished && (eventQueue.top())->getTime() < simulateToTime)
	{
		std::shared_ptr<Event> nextEvent = eventQueue.top(); //Get next event from queue
		eventQueue.pop(); //Remove that event from the queue
		currentTime = nextEvent->getTime(); //Change the current time
		nextEvent->processEvent(); //Process the event
	}

	if (isSimulationFinished) //If the visible simulation has been reached...
	{
		std::cout << "The endtime you selected has been reached. No more logs will be written to the console." << std::endl;
		simulateToTime = currentTime; //...then current time is same as simulateToTime
	}

	if (eventQueue.empty()) //If queue is empty
	{
		isSimulationFinished = true;	//Set isSimulationFinished to true
		simulateToTime = currentTime; //simulateToTime is then same as currentTime...
		endTime = currentTime; //...and endtime aswell
	}
}

//------------------------------------------------------------------------------
// Function definition 
// Name: runNextEvent
// Description: Simulates the next event
//------------------------------------------------------------------------------
void Simulation::runNextEvent()
{
	if (isSimulationFinished)
		std::cout << "Simulation has finished already. There is nothing more to print" << std::endl;

	//If queue aint empty and the next event is before endtime
	if (!eventQueue.empty() && eventQueue.top()->getTime() < endTime)
	{
		std::shared_ptr<Event> nextEvent = eventQueue.top(); //Get next event from queue
		eventQueue.pop();	//Remove that event from the queue
		currentTime = nextEvent->getTime(); //Change the current time
		nextEvent->processEvent(); //Process the event
	}
	else //If queue is empty or that event will run after the endtime
		isSimulationFinished = true; //Then finish the simulation

	simulateToTime = currentTime; //Set simulateToTime to currentTime
}

//------------------------------------------------------------------------------
// Function definition 
// Name: runAllEvents
// Description: Runs all events and finishes the simulation
//------------------------------------------------------------------------------
void Simulation::runAllEvents()
{
	if (isSimulationFinished)
		std::cout << "Simulation has finished already. There is nothing more to print" << std::endl;

	while (!eventQueue.empty()) //Iterate through the eventqueue as long as there are events to pop
	{
		std::shared_ptr<Event> nextEvent = eventQueue.top(); //Get next event from queue
		eventQueue.pop();	//Remove that event from the queue
		currentTime = nextEvent->getTime(); //Change the current time
		nextEvent->processEvent(); //Process the event
	}
}