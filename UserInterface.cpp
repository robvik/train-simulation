//-------------------------------------------------------------------
// Filename: UserInterface.cpp
// Description: This file is responsible for all userinterface-related code. It creates and presents the menu/submenus to the user.
//				It also creates instances of the classes: Simulation and Traincompany aswell as assigning some important values necessary for the simulation to start.
//				Whenever the user choose a menu-option the corresponding function is called.
// Robin Viktorsson 2017-06-01 12:46
// Version 1.0
//-------------------------------------------------------------------
//------------------------------------------------------------------------------
// Including header-files
//------------------------------------------------------------------------------
#include "UserInterface.h"

//------------------------------------------------------------------------------
// Constructor
// Name: UserInterface
// Description: Instantiates instances of Simulation, Traincompany and sets up the menus and their contents/options which will be presented to the user.
//------------------------------------------------------------------------------
UserInterface::UserInterface() : //Instantiates new instances of the classes to smart-pointers. Initiates time: 10 minutes time-interval between events.
	simulator(new Simulation()), trainCompany(new TrainCompany(simulator)), timeInterval(Time(0, 10))
{

	//Setting up the StartMenu
	startMenu.setHeader("************* START MENU *************");
	startMenu.addItem("Change start time [00:00]");
	startMenu.addItem("Change end time [23:59]");
	startMenu.addItem("Start simulation");
	startMenu.addItem("Exit");

	//Setting up the SimulationMenu
	simulationMenu.setHeader("*********** SIMULATION MENU ***********");
	simulationMenu.addItem("Change interval [00:10]");
	simulationMenu.addItem("Run next interval");
	simulationMenu.addItem("Next event");
	simulationMenu.addItem("Finish");
	simulationMenu.addItem("Change log level [Low]");
	simulationMenu.addItem("Train menu");
	simulationMenu.addItem("Station menu");
	simulationMenu.addItem("Vehicle menu");
	simulationMenu.addItem("Exit");

	//Setting up the TrainMenu
	trainMenu.setHeader("********** TRAIN MENU **********");
	trainMenu.addItem("Search train by train id");
	trainMenu.addItem("Search train by vehicle id");
	trainMenu.addItem("Show all trains");
	trainMenu.addItem("Print Timetable");
	trainMenu.addItem("Change log level [Low]");
	trainMenu.addItem("Back");

	//Setting up the StationMenu
	stationMenu.setHeader("********** STATION MENU **********");
	stationMenu.addItem("Show station names");
	stationMenu.addItem("Show station by name");
	stationMenu.addItem("Show all stations");
	stationMenu.addItem("Change log level [Low]");
	stationMenu.addItem("Back");

	//Setting up the VehicleMenu
	vehicleMenu.setHeader("********** VEHICLE MENU **********");
	vehicleMenu.addItem("Show vehicle by id");
	vehicleMenu.addItem("Show all vehicles");
	vehicleMenu.addItem("Change log level [Low]");
	vehicleMenu.addItem("Back");

	//Setting up logLevelMenu
	logLevelMenu.setHeader("********** LOG MENU **********");
	logLevelMenu.addItem("Low log level");
	logLevelMenu.addItem("Normal log level");
	logLevelMenu.addItem("High log level");
	logLevelMenu.addItem("Back");

}

//------------------------------------------------------------------------------
// Function definition 
// Name: run
// Description: The first method which is run. It initiates the start- and endtime and presents the user to the mainmenu
//------------------------------------------------------------------------------
void UserInterface::run()
{
	//Default starttime and endtime is 00:00 and 23:59
	simulator->setStartTime(Time(00, 00));
	simulator->setEndTime(Time(23, 59));

	//Show the mainmenu
	mainMenu();
}

//------------------------------------------------------------------------------
// Function definition 
// Name: mainMenu
// Description: This menu is the initiating menu which allows the user to setup conditions for the
// simulation such as start time and end time
//------------------------------------------------------------------------------
void UserInterface::mainMenu() {

	const int menuChoices = 4;
	bool go = true;
	do {

		startMenu.printMenuItems();
		switch (startMenu.getMenuChoice(menuChoices)) {

		case 1: //Change start-time
			changeStartTime();
			break;

		case 2: //Change end-time
			changeEndTime();
			break;

		case 3: //Start simulation
			startSimulation();
			simulationSubMenu();
			go = false; //Make sure the user cant return to the startmenu
			break;

		case 4: //Quit the program
			go = false;
			break;
		}
	} while (go);
}

//------------------------------------------------------------------------------
// Function definition 
// Name: simulationSubMenu
// Description: Once the simulation has started this menu allows the user to control the simulation
//------------------------------------------------------------------------------
void UserInterface::simulationSubMenu()
{
	const int menuChoices = 9;
	bool go = true;
	do {

		simulationMenu.printMenuItems();
		switch (simulationMenu.getMenuChoice(menuChoices)) {

		case 1: //Change intervaltime
			changeInterval();
			break;

		case 2: //Run next interval
			runNextInterval();
			break;

		case 3: //Next event
			runNextEvent();
			break;

		case 4: //Finish
			runAllEvents();
			break;

		case 5: //Change log level [Low]
			logSubMenu();
			break;

		case 6: //Train submenu
			trainSubMenu();
			break;

		case 7: //Station submenu
			stationSubMenu();
			break;

		case 8: //Vehicle submenu
			vehicleSubMenu();
			break;

		case 9: //Quit the program
			go = false;
			break;
		}
	} while (go);
}

//------------------------------------------------------------------------------
// Function definition 
// Name: trainSubMenu
// Description: This menu allows the user to gather information about all trains
//------------------------------------------------------------------------------
void UserInterface::trainSubMenu()
{
	const int menuChoices = 6;
	bool go = true;
	do {

		trainMenu.printMenuItems();
		switch (trainMenu.getMenuChoice(menuChoices)) {

		case 1: //Search train by ID
			searchTrainByID();
			break;

		case 2: //Search train by vehicle ID
			searchTrainByVehicleID();
			break;

		case 3: //Show all trains
			showAllTrains();
			break;

		case 4: //Print timetable of all trains
			printTimeTable();
			break;

		case 5: //Change log level [Low]
			logSubMenu();
			break;

		case 6: //Quit the program
			go = false;
			break;
		}
	} while (go);
}

//------------------------------------------------------------------------------
// Function definition 
// Name: stationSubMenu
// Description: This menu allows the user to gather information about all stations
//------------------------------------------------------------------------------
void UserInterface::stationSubMenu()
{
	const int menuChoices = 5;
	bool go = true;
	do {

		stationMenu.printMenuItems();
		switch (stationMenu.getMenuChoice(menuChoices)) {

		case 1: //Show station names
			showStationNames();
			break;

		case 2: //Show station by name
			showStationByName();
			break;

		case 3: //Show all stations
			showAllStations();
			break;

		case 4: //Change log level [Low]
			logSubMenu();
			break;

		case 5: //Quit the program
			go = false;
			break;
		}
	} while (go);
}

//------------------------------------------------------------------------------
// Function definition 
// Name: vehicleSubMenu
// Description: This menu allows the user to gather information about all existing vehicles
//------------------------------------------------------------------------------
void UserInterface::vehicleSubMenu()
{
	const int menuChoices = 4;
	bool go = true;
	do {

		vehicleMenu.printMenuItems();
		switch (vehicleMenu.getMenuChoice(menuChoices)) {

		case 1: //Show vehicle by id
			searchTrainByVehicleID();
			break;

		case 2: //Show all vehicles
			showAllVehicles();
			break;

		case 3: //Change log level [Low]
			logSubMenu();
			break;

		case 4: //Back to main program
			go = false;
			break;
		}
	} while (go);
}

//------------------------------------------------------------------------------
// Function definition 
// Name: logSubMenu
// Description: Consists of three different choices to justify how detailed the logging will be
//------------------------------------------------------------------------------
void UserInterface::logSubMenu()
{
	const int menuChoices = 4;
	bool go = true;
	do {

		logLevelMenu.printMenuItems();
		std::string sLogLevel;
		int iLogLevel;
		switch (logLevelMenu.getMenuChoice(menuChoices)) {
		case 1: //Low log level
			sLogLevel = "[Low]";
			iLogLevel = 1;
			break;

		case 2: //Normal log level
			sLogLevel = "[Normal]";
			iLogLevel = 2;
			break;

		case 3: //High log level
			sLogLevel = "[High]";
			iLogLevel = 3;
			break;

		case 4: //Back to main program
			go = false;
			break;
		}

		if (go) {

			//Inform the user
			std::cout << "The loglevel is now: " + sLogLevel << std::endl;

			//Change the text of the submenus
			simulationMenu.changeItem("Change log level " + sLogLevel, 4);
			trainMenu.changeItem("Change log level " + sLogLevel, 4);
			stationMenu.changeItem("Change log level " + sLogLevel, 3);
			vehicleMenu.changeItem("Change log level " + sLogLevel, 2);
			trainCompany->setLogLevel(iLogLevel);
		}

	} while (go);
}

//------------------------------------------------------------------------------
// Function definition 
// Name: startSimulation
// Description: Initiates the simulation
//------------------------------------------------------------------------------
void UserInterface::startSimulation()
{
	for (auto &trains : trainCompany->getTrains()) //Iterate through all trains and push events to the evenqueue. 
		simulator->scheduleEvent(std::make_shared<AssembleEvent>(simulator, trainCompany, trains.second, trains.second->getEstimatedStartTime() - 30)); //All trains should start to try assemble 30 minutes before estimated starttime

	simulator->scheduleEvent(std::make_shared<EndTimeEvent>(simulator, simulator->getEndTime())); //The simulation which is presented to the console out should have a stoptime
	simulator->runNextInterval(simulator->getStartTime()); //Make sure the simulation which is visible to the user starts at the correct time
}

//------------------------------------------------------------------------------
// Function definition 
// Name: changeStartTime
// Description: Allows the user to change the start time of the simulation
//------------------------------------------------------------------------------
void UserInterface::changeStartTime()
{
	bool validInput = true;
	Time startTime;
	do {
		//Clear the buffer just in case
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		//Lets make sure the user choose a starttime of the simulation
		std::cout << "Choose starttime for the simulation (HH:MM): " << std::flush;
		std::cin >> startTime;

		if (std::cin.fail()) { //Did the input fail?
			std::cout << "That is not a valid input. Please try again." << std::endl;
			validInput = false;
		}
		else if (startTime >= simulator->getEndTime()) { //Make sure starttime is before endtime
			std::cout << "The starttime you enter has to be before the endtime. Please try again." << std::endl;
			validInput = false;
		}
		else {
			simulator->setStartTime(startTime); //Set starttime
			startMenu.changeItem("Change start time [" + startTime.to_string(startTime) + "]", 0); //Change all affected submenus
			validInput = true;
		}

	} while (!validInput); //Loop until the input is valid
}

//------------------------------------------------------------------------------
// Function definition 
// Name: changeEndTime
// Description: Allows the user to change the end time of the simulation
//------------------------------------------------------------------------------
void UserInterface::changeEndTime()
{
	bool validInput = true;
	Time endTime;
	do
	{
		//Clear the buffer just in case
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		//Lets make sure the user choose a endtime of the simulation
		std::cout << "Choose endtime for the simulation (HH:MM): " << std::flush;
		std::cin >> endTime;

		if (std::cin.fail()) { //Did the input fail?
			std::cout << "That is not a valid input. Please try again." << std::endl;
			validInput = false;
		}
		else if (endTime <= simulator->getStartTime()) { //Make sure endtime is after starttime
			std::cout << "The endtime you enter has to be after the starttime. Please try again." << std::endl;
			validInput = false;
		}
		else {
			simulator->setEndTime(endTime);  //Set endtime
			startMenu.changeItem("Change end time [" + endTime.to_string(endTime) + "]", 1);
			validInput = true;
		}

	} while (!validInput);
}

//------------------------------------------------------------------------------
// Function definition 
// Name: changeInterval
// Description: Modifies the length of the timeintervals which is used when running the simulation based on timegaps
//------------------------------------------------------------------------------
void UserInterface::changeInterval()
{

	bool validInput = true;
	Time tempIntervalTime;
	do {
		//Clear the buffer just in case
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		//Lets make sure the user choose a time-interval of the simulation
		std::cout << "Choose a time interval for the simulation (HH:MM): " << std::flush;
		std::cin >> tempIntervalTime;

		if (std::cin.fail()) { //Did the input fail?
			std::cout << "That is not a valid input. Please try again." << std::endl;
			validInput = false;
		}
		else if (tempIntervalTime >= simulator->getEndTime()) { //Make sure the intervaltime doesnt exceed the endtime
			std::cout << "The intervalTime cant pass the endtime. Please try again." << std::endl;
			validInput = false;
		}
		else {
			timeInterval = tempIntervalTime; //Assign the tempIntervalTime to the timeInterval if everything went smoothly
			simulationMenu.changeItem("Change interval [" + timeInterval.to_string(timeInterval) + "]", 0); //Change the name of the menuitem
			validInput = true;
		}

	} while (!validInput); //Loop until the input is valid

}

//------------------------------------------------------------------------------
// Function definition 
// Name: runNextInterval
// Description: Runs the next interval
//------------------------------------------------------------------------------
void UserInterface::runNextInterval()
{
	simulator->runNextInterval(timeInterval);

	//Make sure statistics is printed if the simulation is finished and statistics has not been printed before
	if (simulator->getSimulationFinished() && !simulator->getStatisticsPrinted()) {
		trainCompany->printStatistics();
		simulator->setStatisticsPrinted(true);
	}
}

//------------------------------------------------------------------------------
// Function definition 
// Name: runNextEvent
// Description: Runs the next event
//------------------------------------------------------------------------------
void UserInterface::runNextEvent()
{
	simulator->runNextEvent();

	//Make sure statistics is printed if the simulation is finished and statistics has not been printed before
	if (simulator->getSimulationFinished() && !simulator->getStatisticsPrinted()) {
		trainCompany->printStatistics();
		simulator->setStatisticsPrinted(true);
	}
}

//------------------------------------------------------------------------------
// Function definition 
// Name: runAllEvents
// Description: Runs all existing events and therefore finished the simulation
//------------------------------------------------------------------------------
void UserInterface::runAllEvents()
{
	simulator->runAllEvents();

	//Make sure statistics is printed if the simulation is finished and statistics has not been printed before
	if (simulator->getSimulationFinished() && !simulator->getStatisticsPrinted()) {
		trainCompany->printStatistics();
		simulator->setStatisticsPrinted(true);
	}
}

//------------------------------------------------------------------------------
// Function definition 
// Name: searchTrainByID
// Description: Searches and gathers information about a specific train by ID which is presented to the user
//------------------------------------------------------------------------------
void UserInterface::searchTrainByID()
{
	std::cout << "Search train by ID:" << std::endl;

	std::cin.get();
	int trainID;
	std::cout << "Enter train id for the train you want information for: " << std::flush;
	std::cin >> trainID;

	trainCompany->printTrainByID(trainID);
}

//------------------------------------------------------------------------------
// Function definition 
// Name: searchVehicleByID
// Description: Show information about an vehicle based on its ID
//------------------------------------------------------------------------------
void UserInterface::searchTrainByVehicleID()
{
	std::cout << "Search train by vehicle ID: " << std::endl;

	std::cin.get();
	int vehicleID;
	std::cout << "Enter the vehicle id for the vehicle you wish to get information about: " << std::flush;
	std::cin >> vehicleID;

	trainCompany->printVehicleByID(vehicleID);
}

//------------------------------------------------------------------------------
// Function definition 
// Name: showAllTrains
// Description: Print information about all trains
//------------------------------------------------------------------------------
void UserInterface::showAllTrains()
{
	trainCompany->printAllTrains();
}

//------------------------------------------------------------------------------
// Function definition 
// Name: showStationNames
// Description: Shows the name of all stations
//------------------------------------------------------------------------------
void UserInterface::showStationNames()
{
	trainCompany->printStationNames();
}

//------------------------------------------------------------------------------
// Function definition 
// Name: showStationByName
// Description: Print information about a specific station
//------------------------------------------------------------------------------
void UserInterface::showStationByName()
{
	std::cout << "Show station by name" << std::endl;

	std::cin.get();
	std::string stationName;
	std::cout << "Which station would you like to know more about?: " << std::flush;
	std::getline(std::cin, stationName);

	trainCompany->printStation(stationName);
}

//------------------------------------------------------------------------------
// Function definition 
// Name: printAllStations
// Description: Prints information about all trainstations
//------------------------------------------------------------------------------
void UserInterface::showAllStations()
{
	trainCompany->printAllStations();
}

//------------------------------------------------------------------------------
// Function definition 
// Name: showAllVehicles
// Description: Shows information of all vehicles
//------------------------------------------------------------------------------
void UserInterface::showAllVehicles()
{
	trainCompany->printAllVehicles();
}

//------------------------------------------------------------------------------
// Function definition 
// Name: printStatistics
// Description: Print statistics of the simulation
//------------------------------------------------------------------------------
void UserInterface::printStatistics()
{
	trainCompany->printStatistics();
}

//------------------------------------------------------------------------------
// Function definition 
// Name: printTimeTable
// Description: Calls trainCompany->printTimeTable which prints the timetable of all trains
//------------------------------------------------------------------------------
void UserInterface::printTimeTable()
{
	trainCompany->printTimeTable();
}