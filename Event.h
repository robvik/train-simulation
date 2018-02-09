//-------------------------------------------------------------------
// Header filename: Event.h
// Description: The header-file for the event-class. Contains all necessary subclasses for each events which is inheriting the event-class
// Robin Viktorsson 2017-06-01 13:46
// Version 1.0
//-------------------------------------------------------------------
#ifndef EVENT_H
#define EVENT_H
#include <memory>

//-------------------------------------------------------------------
// Including header-files
//-------------------------------------------------------------------
#include "Time.h"
#include "Station.h"
#include "Train.h"

//-------------------------------------------------------------------
// Forward declarations
//-------------------------------------------------------------------
class Simulation;
class TrainCompany;

//------------------------------
// Classdefinition - Event
//------------------------------
class Event {
protected:

	//Instance of the Time-class
	Time time;

public:

	//Constructor and deconstructor
	Event(Time pTime) : time(pTime) {}
	virtual ~Event() {}

	//Methods
	virtual void processEvent() = 0; //This function will process every event

	//Getters
	Time getTime() const { return time; } //Retrieve the time of the event
};

//------------------------------
// Classdefinition - AssembleEvent
// Description: Will try to assemble the trains and the carriages
//				Inherits Event.
//------------------------------
class AssembleEvent : public Event {
private:

	//Smart-pointers
	std::shared_ptr<Simulation> simulator;
	std::shared_ptr<Train> train;
	std::shared_ptr<TrainCompany> trainCompany;

public:

	//Constructor
	AssembleEvent(std::shared_ptr<Simulation> pSimulation, std::shared_ptr<TrainCompany> pTrainCompany, std::shared_ptr<Train> pTrain, Time pTime) :
		Event(pTime), simulator(pSimulation), trainCompany(pTrainCompany), train(pTrain) {}

	//Methods
	virtual void processEvent();
};

//------------------------------
// Classdefinition - ReadyEvent
// Description: Make the train ready when its assembled
//				Inherits Event.
//------------------------------
class ReadyEvent : public Event {
private:

	//Smart-pointers
	std::shared_ptr<Simulation> simulator;
	std::shared_ptr<Train> train;
	std::shared_ptr<TrainCompany> trainCompany;

public:

	//Constructor
	ReadyEvent(std::shared_ptr<Simulation> pSimulation, std::shared_ptr<TrainCompany> pTrainCompany, std::shared_ptr<Train> pTrain, Time pTime) :
		Event(pTime), simulator(pSimulation), trainCompany(pTrainCompany), train(pTrain) {}

	//Methods
	virtual void processEvent();
};

//------------------------------
// Classdefinition - StartEvent
// Description: An event for starting the train
//				Inherits Event.
//------------------------------
class StartEvent : public Event {
private:

	//Smart-pointers
	std::shared_ptr<Simulation> simulator;
	std::shared_ptr<Train> train;
	std::shared_ptr<TrainCompany> trainCompany;

public:

	//Constructor
	StartEvent(std::shared_ptr<Simulation> pSimulation, std::shared_ptr<TrainCompany> pTrainCompany, std::shared_ptr<Train> pTrain, Time pTime)
		: Event(pTime), simulator(pSimulation), trainCompany(pTrainCompany), train(pTrain) {}

	//Methods
	virtual void processEvent();
};

//------------------------------
// Classdefinition - ArriveEvent
// Description: An event for the train to arrive at station
//				Inherits Event.
//------------------------------
class ArriveEvent : public Event {
private:

	//Smart-pointers
	std::shared_ptr<Simulation> simulator;
	std::shared_ptr<Train> train;
	std::shared_ptr<TrainCompany> trainCompany;

public:

	//Constructor
	ArriveEvent(std::shared_ptr<Simulation> pSimulation, std::shared_ptr<TrainCompany> pTrainCompany, std::shared_ptr<Train> pTrain, Time pTime)
		: Event(pTime), simulator(pSimulation), trainCompany(pTrainCompany), train(pTrain) {}

	//Methods
	virtual void processEvent();
};

//------------------------------
// Classdefinition - DissambleEvent
// Description: An event for dissamling the train
//				Inherits Event.
//------------------------------
class DisassembleEvent : public Event {
private:

	//Smart-pointers
	std::shared_ptr<Simulation> simulator;
	std::shared_ptr<Train> train;
	std::shared_ptr<TrainCompany> trainCompany;

public:

	//Constructor
	DisassembleEvent(std::shared_ptr<Simulation> pSimulation, std::shared_ptr<TrainCompany> pTrainCompany, std::shared_ptr<Train> pTrain, Time pTime)
		: Event(pTime), simulator(pSimulation), trainCompany(pTrainCompany), train(pTrain) {}

	//Methods
	virtual void processEvent();
};

//------------------------------
// Classdefinition - EndTimeEvent
// Description: An event for ending the simulation based on endtime
//				Inherits Event.
//------------------------------
class EndTimeEvent : public Event {
private:

	//Smart-pointer
	std::shared_ptr<Simulation> simulator;

public:

	//Constructor
	EndTimeEvent(std::shared_ptr<Simulation> pSimulation, Time pTime)
		: Event(pTime), simulator(pSimulation) {}

	//Methods
	virtual void processEvent();
};
#endif