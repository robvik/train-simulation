//-------------------------------------------------------------------
// Header filename: UserInterface.h
// Description: The header-file for the UserInterface-class. Contains all necessary variables, instances of other classes, containers, constructor and function definitions.
// Robin Viktorsson 2017-06-01 13:46
// Version 1.0
//-------------------------------------------------------------------
#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include <memory>
#include <string>

//-------------------------------------------------------------------
// Including header-files
//-------------------------------------------------------------------
#include "Simulation.h"
#include "TrainCompany.h"
#include "Menu.h"
#include "Time.h"

//------------------------------
// Classdefinition
//------------------------------
class UserInterface {
private:

	//Current timeInterval-time
	Time timeInterval;

	//Smart-pointers
	std::shared_ptr<Simulation> simulator;
	std::shared_ptr<TrainCompany> trainCompany;

	//Instances of menu-classes
	Menu startMenu;
	Menu simulationMenu;
	Menu trainMenu;
	Menu stationMenu;
	Menu vehicleMenu;
	Menu logLevelMenu;

	//Menu-methods
	void mainMenu();
	void simulationSubMenu();
	void trainSubMenu();
	void stationSubMenu();
	void vehicleSubMenu();
	void logSubMenu();

	//Methods (Initializing simulation)
	void changeStartTime();
	void changeEndTime();
	void startSimulation();

	//Methods (Simulation/Event-related)
	void changeInterval();
	void runNextInterval();
	void runNextEvent();
	void runAllEvents();

	//Methods (Statistics)
	void printStatistics();
	void printTimeTable();

	//Methods (Trainmenu-related)
	void searchTrainByID();
	void searchTrainByVehicleID();
	void showAllTrains();

	//Methods (Stationmenu-related)
	void showStationNames();
	void showStationByName();
	void showAllStations();

	//Methods (Vehiclemenu-related)
	void showAllVehicles();

public:

	//Constructor
	UserInterface();

	//Run-method
	void run();
};
#endif