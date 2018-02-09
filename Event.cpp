//-------------------------------------------------------------------
// Header filename: Event.cpp
// Description: Contains all the processEvent-functions of all events. The code in this files try to execute the scheduled events by calling the event-functions in TrainCompany.cpp
//				If the events cant be succesfully processed for some reason, it will most likely schedule a new event. It will also do so if the events are processed succesfully.
// Robin Viktorsson 2017-06-01 13:46
// Version 1.0
//-------------------------------------------------------------------

//-------------------------------------------------------------------
// Including header-files
//-------------------------------------------------------------------
#include "Event.h"
#include "TrainCompany.h"
#include "Simulation.h"

//------------------------------------------------------------------------------
// Function definition 
// Name: AssembleEvent::processEvent()
// Description: This event tries to assemble the train
//------------------------------------------------------------------------------
void AssembleEvent::processEvent()
{

	if (trainCompany->assembleTrain(train)) //If the train succesfully assembled
	{
		if (time + 20 <= Time(23, 59)) //No trains should be assembled after 23.59
			simulator->scheduleEvent(std::make_shared<ReadyEvent>(simulator, trainCompany, train, time + 20)); //Its ready to go from ASSEMBLE -> READY	
	}
	else //If the train fails to assemble
	{
		if (time + 10 <= Time(23, 59)) //No trains should be assembled after 23.59
			simulator->scheduleEvent(std::make_shared<AssembleEvent>(simulator, trainCompany, train, time + 10)); //Try to assemble it at a later stage (10 minutes later)		
	}
}

//------------------------------------------------------------------------------
// Function definition 
// Name: ReadyEvent::processEvent()
// Description: This event tries to make the train ready
//------------------------------------------------------------------------------
void ReadyEvent::processEvent()
{
	trainCompany->makeTrainReady(train); //Make the train ready

	if (time + 10 <= Time(23, 59)) //If time is before midnight
		simulator->scheduleEvent(std::make_shared<StartEvent>(simulator, trainCompany, train, time + 10)); //Add startevent for the train
}

//------------------------------------------------------------------------------
// Function definition 
// Name: StartEvent::processEvent()
// Description: Lets try to start the train
//------------------------------------------------------------------------------
void StartEvent::processEvent()
{
	Time arrivalTime = trainCompany->startTrain(train); //Try to start the train

	//Add an ArriveEvent to the train
	simulator->scheduleEvent(std::make_shared<ArriveEvent>(simulator, trainCompany, train, arrivalTime));
}

//------------------------------------------------------------------------------
// Function definition 
// Name: ArriveEvent::processEvent()
// Description: Event for the trains arrival
//------------------------------------------------------------------------------
void ArriveEvent::processEvent()
{
	trainCompany->trainArrives(train); //Call the trainArrive-function from TrainCompany

	//Add an disassembleevent to the train. It arrived, now it needs to dissamble
	simulator->scheduleEvent(std::make_shared<DisassembleEvent>(simulator, trainCompany, train, time + 20)); //20 minutes after the train has trainstate ARRIVED it should start to dissassemble and try change state to FINISHED
}

//------------------------------------------------------------------------------
// Function definition 
// Name: DissambleEvent::processEvent()
// Description: Event for the trains arrival
//------------------------------------------------------------------------------
void DisassembleEvent::processEvent()
{
	trainCompany->disassembleTrain(train); //Makes sure the train dissambles
}

//------------------------------------------------------------------------------
// Function definition 
// Name: EndTimeEvent::processEvent()
// Description: Finish the visible simulation
//------------------------------------------------------------------------------
void EndTimeEvent::processEvent()
{
	simulator->setSimulationFinished(true);
}