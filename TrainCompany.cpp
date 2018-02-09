//-------------------------------------------------------------------
// Header filename: TrainCompany.cpp
// Robin Viktorsson 2017-06-01 13:46
// Description: The code in this file is doing alot. Simply because its the core of the TrainCompany-class. Examples:
//				It reads the stations, trains and trainroutes and inserts it into maps. It prints statistics and timetables to the user.
//				Most importantly it calls the functions which makes the train go into different trainstates: assemble, not_assembled, incomplete, ready, running, arrived, dissamble.
// Version 1.0
//-------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <sstream>
#include <iomanip>

//-------------------------------------------------------------------
// Including header-files
//-------------------------------------------------------------------
#include "TrainCompany.h"

//------------------------------------------------------------------------------
// Constructor
// Name: TrainCompany
// Description: Inherits the simulator and prepares (reads to maps/vectors) the trainstations, the trains and the trainroutes.
//------------------------------------------------------------------------------
TrainCompany::TrainCompany(std::shared_ptr<Simulation> pSimulator) : simulator(pSimulator), logLevel(1)
{
	prepareTrainStations();
	prepareTrainRoutes();
	prepareTrains();
}

//------------------------------------------------------------------------------
// Function definition 
// Name: prepareTrainStations
// Description: Reads all data about the trainstations from TrainStations.txt and adds that
//				information to maps and vectors in the code necessary to run the simulation
//------------------------------------------------------------------------------
void TrainCompany::prepareTrainStations()
{

	std::ifstream file;
	file.open("TrainStations.txt");
	if (!file.is_open()) //Make sure the file is opened otherwise theres nothing to be ready
		throw std::runtime_error("Could not open TrainStations.txt");

	//Regex-expressions
	std::regex nameExpr("([\\w.-]+)");
	std::regex groupExpr("\\(([^\\)]*)\\)");
	std::smatch match;

	/* Regex-expressions explained
	nameExpr - Simple explanation: It extracts the words from the file, which is the stationnames
	Advanced explanation:
	1st Capturing Group ("([\w.-]+)")
	" matches the character " literally (case sensitive)
	2nd Capturing Group ([\w.-]+)
	Match a single character present in the list below [\w.-]+
	+ Quantifier — Matches between one and unlimited times, as many times as possible, giving back as needed.
	\w matches any word character (equal to [a-zA-Z0-9_])
	.- matches a single character in the list .- (case sensitive)
	" matches the character " literally (case sensitive)

	groupExpr - Simple explanation: It extracts the characters within parenthesis no matter if its 3, 4 or 5 digits
	Advanced explanation:
	1st Capturing Group ("\(([^\)]*)\)")
	" matches the character " literally (case sensitive)
	\( matches the character ( literally (case sensitive)
	2nd Capturing Group ([^\)]*)
	Match a single character not present in the list below [^\)]*
	* Quantifier — Matches between zero and unlimited times, as many times as possible, giving back as needed (greedy)
	\) matches the character ) literally (case sensitive)
	\) matches the character ) literally (case sensitive)
	" matches the character " literally (case sensitive)
	*/

	//Lets create some variables to store the information somewhere
	std::string stationName;
	std::string str;

	//Loop through all lines in the file
	try {

		while (std::getline(file, str)) //Start to read the file and continue to do so until everything has been read or an expection has been cast
		{
			//Extract and save the stationname
			if (std::regex_search(str, match, nameExpr))
			{
				stationName = match[1]; //The name the station
				str = str.substr(match.str().size());
			}

			//Creating a pointer to a new station the station
			std::shared_ptr<Station> stationPtr(new Station(stationName));
			std::shared_ptr<Vehicle> vehiclePtr = nullptr; //...and creating an object of class Vehicle

			// Make an iterator to extract the groups of numbers to fetch the vehicles
			auto groups_begin = std::sregex_iterator(str.begin(), str.end(), groupExpr);
			auto groups_end = std::sregex_iterator();

			//Lets iterate through all groups of vehicles and get their information
			for (std::sregex_iterator i = groups_begin; i != groups_end; ++i)
			{
				std::stringstream ss{ (*i)[1] };
				std::vector<int> nums;
				std::string tmp;
				while (ss >> tmp) { nums.push_back(std::stoi(tmp)); };

				if (nums.size() == 4) //Pass the correct amount of parameters depending on which vehicletype which is going to be built
					vehiclePtr = VehicleFactory::buildVehicle(nums[0], nums[1], nums[2], nums[3]);
				else
					vehiclePtr = VehicleFactory::buildVehicle(nums[0], nums[1], nums[2], 0);

				statistics.countVehiclesAtStation(stationName); //Add vehicle to the statistics
				stationPtr->addVehicle(vehiclePtr); //Add vehicle to vehicles in Station.h
				vehicles[nums[0]] = vehiclePtr; //Add vehicle to vehicles in TrainCompany.h. Sorted by iD

				vehiclePtr->setLocation(stationPtr, Time(0, 0)); //Set the location of the vehicle

			}

			stations[stationName] = stationPtr; //Add the temporary stationPtr to stations-map	
		}
	}
	catch (std::ios_base::failure e) {
		std::cout << "Could not read TrainStations.txt..." << std::endl;
		throw;
	}

	file.close();
}

//------------------------------------------------------------------------------
// Function definition 
// Name: prepareTrainRoutes
// Description: Reads all data about the available trainroutes from TrainRoutes.txt and adds that
//				information to maps and vectors in the code necessary to run the simulation
//------------------------------------------------------------------------------
void TrainCompany::prepareTrainRoutes()
{
	std::ifstream file;
	file.open("TrainMap.txt");
	if (!file.is_open()) //Make sure the file is opened otherwise theres nothing to be ready
		throw std::runtime_error("Could not open TrainMap.txt");

	//Variables to store information
	std::string line;
	std::string departure, destination, distance;

	try {

		while (std::getline(file, line)) //Start to read the file and continue to do so until everything has been read or an expection has been cast
		{
			std::stringstream ss(line);
			ss >> departure >> destination >> distance;
			distances[departure].insert(std::pair<std::string, double>{destination, std::stod(distance)}); //Make sure the trainroutes are added back...
			distances[destination].insert(std::pair<std::string, double>{departure, std::stod(distance)}); //...and forth
		}

	}
	catch (std::ios_base::failure e) {
		std::cout << "Could not read TrainMap.txt..." << std::endl;
		throw;
	}

	file.close();
}

//------------------------------------------------------------------------------
// Function definition 
// Name: prepareTrain
// Description: Reads all data about the trains from TrainRoutes.txt thats gonna run in the simulation
//				and adds that information to maps and vectors in the code necessary to run the simulation
//------------------------------------------------------------------------------
void TrainCompany::prepareTrains()
{
	std::ifstream file;
	file.open("Trains.txt");
	if (!file.is_open()) //Make sure the file is opened otherwise theres nothing to be ready
		throw std::runtime_error("Could not open Trains.txt");

	//Variables used to store information in
	std::string line, depart, destination, vehicles;
	int id, maxspeed, sTimeHour, sTimeMin, eTimeHour, eTimeMin;
	Time starttime, endtime;
	char c;

	std::stringstream ss(line);
	try {

		while (std::getline(file, line)) //Start to read the file and continue to do so until everything has been read or an expection has been cast
		{

			ss.clear();
			ss.str(line);
			ss >> id; //Get TrainID
			ss >> depart >> destination; //Departure-location and destination

			//Set departure-time
			ss >> sTimeHour >> c >> sTimeMin;
			starttime.setHour(sTimeHour);
			starttime.setMinutes(sTimeMin);

			//Set arrival-time
			ss >> eTimeHour >> c >> eTimeMin;
			endtime.setHour(eTimeHour);
			endtime.setMinutes(eTimeMin);

			ss >> maxspeed; //Store maxspeed
			std::getline(ss, vehicles); //Get the vehicles

			auto depStation = stations.find(depart); //Find the departure-station
			auto destStation = stations.find(destination); //...and the destination

			//Lets create an temporary shared_pointer
			std::shared_ptr<Train> tempTrain(new Train(id, depart, destination, starttime, endtime, maxspeed, vehicles));

			//Assign the train its departure-location and destination
			tempTrain->setDepLocation(depStation->second);
			tempTrain->setDestLocation(destStation->second);

			if (depStation != stations.end())
				depStation->second->addTrain(tempTrain); //Add temptrain to station
			else
				std::cout << "Out of range!" << std::endl; //This has never been triggered so far and shouldnt so in the future.

			trains[id] = tempTrain;
		}
	}
	catch (std::ios_base::failure e) {
		std::cout << "Could not read Trains.txt..." << std::endl;
		throw;
	}
	file.close();

}

//------------------------------------------------------------------------------
// Function definition 
// Name: assembleTrain
// Description: Reads all data about the trains from TrainRoutes.txt thats gonna run in the simulation
//				and adds that information to maps and vectors in the code necessary to run the simulation
// Parameters:  A smart-pointer to the train that is going to be assembled
// Returns:		True if train was assembled, otherwise false
//------------------------------------------------------------------------------
bool TrainCompany::assembleTrain(std::shared_ptr<Train> pTrain)
{
	if (pTrain->assembleVehicles()) //Loads all the vehicles necessary to assemble the train
	{
		pTrain->setTrainState(ASSEMBLED); //Change the trainstate if the assemble-attempt was succesful

		//Writing logs
		statistics.writeToLogs(time.to_string(simulator->getCurrentTime()) + " Train [" + std::to_string(pTrain->getTrainID()) + "] (ASSEMBLED) from " + pTrain->getDepStation() + " " + time.to_string(pTrain->getEstimatedStartTime()) + " (" + time.to_string(pTrain->getStartTime()) + ") to " + pTrain->getDestStation() + " " + time.to_string(pTrain->getEstimatedArrivalTime()) + " (" + time.to_string(pTrain->getArrivalTime()) + ") is now assembled. ");

		//Only print the information to the console if the assembling happens within the simulationtimes
		if (simulator->getCurrentTime() >= simulator->getStartTime() && simulator->getCurrentTime() <= simulator->getEndTime()) {

			std::cout << simulator->getCurrentTime() << std::left << std::setw(3) << " Train [" << pTrain->getTrainID() << "] (ASSEMBLED) from " << pTrain->getDepStation() << " "; //Train, state, from
			std::cout << pTrain->getEstimatedStartTime() << " (" << pTrain->getStartTime() << ") to " << pTrain->getDestStation() << " "; //Starttime and destination
			std::cout << pTrain->getEstimatedArrivalTime() << " (" << pTrain->getArrivalTime() << ") is now assembled. " << std::endl;
		}
		return true;
	}
	else  //This will run if it was not possible to assemble the train
	{
		pTrain->setTrainState(INCOMPLETE); //Change the trainstate to incomplete

		//Writing logs and statistics
		statistics.writeToLogs(time.to_string(simulator->getCurrentTime()) + " Train [" + std::to_string(pTrain->getTrainID()) + "] (ASSEMBLED) from " + pTrain->getDepStation() + " " + time.to_string(pTrain->getEstimatedStartTime()) + " (" + time.to_string(pTrain->getStartTime()) + ") to " + pTrain->getDestStation() + " " + time.to_string(pTrain->getEstimatedArrivalTime()) + " (" + time.to_string(pTrain->getArrivalTime()) + ") could not be assembled. Trying again in 10 minutes. ");
		statistics.addDelayedTrain(" Train [" + std::to_string(pTrain->getTrainID()) + "] from " + pTrain->getDepStation() + " " + time.to_string(pTrain->getEstimatedStartTime()) + " (" + time.to_string(pTrain->getStartTime()) + ") to " + pTrain->getDestStation() + " " + time.to_string(pTrain->getEstimatedArrivalTime()) + " (" + time.to_string(pTrain->getArrivalTime()) + ")");
		statistics.setTotalDelay(10); //Adds 10 minutes to the total delaytime

		//Delay the starttime and arrivaltime with 10 minutes if the train could not assemble
		pTrain->setStartTime(pTrain->getStartTime() + 10);
		pTrain->setArrivalTime(pTrain->getArrivalTime() + 10);

		//Only print the information to the console if the assembling happens within the simulationtimes
		if (simulator->getCurrentTime() >= simulator->getStartTime() && simulator->getCurrentTime() <= simulator->getEndTime()) {

			//Print information only if its within runtime
			std::cout << simulator->getCurrentTime() << " Train [" << pTrain->getTrainID() << "] (ASSEMBLED) from " << pTrain->getDepStation() << " "; //Train, state, from
			std::cout << pTrain->getEstimatedStartTime() << " (" << pTrain->getStartTime() << ") to " << pTrain->getDestStation() << " "; //starttime and destination
			std::cout << pTrain->getEstimatedArrivalTime() << " (" << pTrain->getArrivalTime() << ") could not be assembled. Trying again in 10 minutes. " << std::endl;
		}

		return false;
	}
}

//------------------------------------------------------------------------------
// Function definition 
// Name: makeTrainReady
// Description: Changes the trainstate to ready
// Parameters:  A smart-pointer to the train that is going into trainstate: READY
//------------------------------------------------------------------------------
void TrainCompany::makeTrainReady(std::shared_ptr<Train> pTrain)
{
	pTrain->setTrainState(READY); //Change the trainstate to READY

	//Writing logs
	statistics.writeToLogs(time.to_string(simulator->getCurrentTime()) + " Train [" + std::to_string(pTrain->getTrainID()) + "] (READY) from " + pTrain->getDepStation() + " " + time.to_string(pTrain->getEstimatedStartTime()) + " (" + time.to_string(pTrain->getStartTime()) + ") to " + pTrain->getDestStation() + " " + time.to_string(pTrain->getEstimatedArrivalTime()) + " (" + time.to_string(pTrain->getArrivalTime()) + ") is ready for departure. ");

	//Only print the information to the console if the assembling happens within the simulationtimes
	if (simulator->getCurrentTime() >= simulator->getStartTime() && simulator->getCurrentTime() <= simulator->getEndTime()) {
		std::cout << simulator->getCurrentTime() << " Train [" << pTrain->getTrainID() << "] (READY) from " << pTrain->getDepStation() << " "; //Train, state, from
		std::cout << pTrain->getEstimatedStartTime() << " (" << pTrain->getStartTime() << ") to " << pTrain->getDestStation() << " "; //Starttime and destination
		std::cout << pTrain->getEstimatedArrivalTime() << " (" << pTrain->getArrivalTime() << ") is ready for departure. " << std::endl;
	}

}

//------------------------------------------------------------------------------
// Function definition 
// Name: startTrain
// Description: Starts the train
// Parameters:  A smart-pointer to the train that is starting
// Returns: The estimated arrivaltime
//------------------------------------------------------------------------------
Time TrainCompany::startTrain(std::shared_ptr<Train> pTrain)
{
	pTrain->setTrainState(RUNNING); //Change the trainstate to RUNNING

	//Remove the train from departure-station
	auto stationIterator = stations.find(pTrain->getDepStation());
	if (stationIterator != stations.end())
		stationIterator->second->removeTrain(pTrain->getTrainID());
	else //Throw an expection if it could not be found. It should always be found, otherwise somethings wrong
		throw std::runtime_error("Could not find train at departure-location.");

	int distance; //Create an variable (type double) to store the distance in
	std::map<std::string, std::map <std::string, double>>::iterator iter;
	iter = distances.find(pTrain->getDepStation()); //Departstation
	if (iter != distances.end()) {
		std::map<std::string, double>::iterator innerIter;
		innerIter = iter->second.find(pTrain->getDestStation()); //Destinationstation
		if (innerIter != iter->second.end())
			distance = static_cast<int>(innerIter->second); //Distance was found and saved in distance
		else
			throw std::runtime_error("Could not find destination.");
	}
	else
		throw std::runtime_error("Could not find departure.");

	if (pTrain->getStartTime() > pTrain->getEstimatedStartTime()) //If the train is delayed
	{
		//Writing statistics
		statistics.writeToLogs(time.to_string(simulator->getCurrentTime()) + " Train [" + std::to_string(pTrain->getTrainID()) + "] (RUNNING) from " + pTrain->getDepStation() + " " + time.to_string(pTrain->getEstimatedStartTime()) + " (" + time.to_string(pTrain->getStartTime()) + ") to " + pTrain->getDestStation() + " " + time.to_string(pTrain->getEstimatedArrivalTime()) + " (" + time.to_string(pTrain->getArrivalTime()) + ") started. Is " + time.to_string(pTrain->getStartTime() - pTrain->getEstimatedStartTime()) + " minutes late.");

		//Only print the information to the console if the assembling happens within the simulationtimes
		if (simulator->getCurrentTime() >= simulator->getStartTime() && simulator->getCurrentTime() <= simulator->getEndTime()) {

			std::cout << simulator->getCurrentTime() << " Train [" << pTrain->getTrainID() << "] (RUNNING) from " << pTrain->getDepStation() << " "; //Train, state, from
			std::cout << pTrain->getEstimatedStartTime() << " (" << pTrain->getStartTime() << ") to " << pTrain->getDestStation() << " "; //Starttime and destination
			std::cout << pTrain->getEstimatedArrivalTime() << " (" << pTrain->getArrivalTime() << ") started. Is " << pTrain->getStartTime() - pTrain->getEstimatedStartTime() << " minutes late." << std::endl;
		}

		//The earliest possible time of arrival if train is going maxspeed
		Time expectedArrival = pTrain->getStartTime() + (60 * static_cast<double>(distance) / pTrain->getMaxSpeed());

		//If the earliest possible time of arrival is later than the estimated arrivaltime
		Time tempTime;
		if (expectedArrival <= pTrain->getEstimatedArrivalTime())
		{
			//Calculate the traveltime
			tempTime = pTrain->getEstimatedArrivalTime() - pTrain->getStartTime();
			double travelTime = tempTime.getHours() + static_cast<double>(tempTime.getMinutes()) / 60;

			pTrain->setAverageSpeed(distance / travelTime); //Set the average speed
			tempTime = pTrain->getEstimatedArrivalTime(); //Change the estimated arrivaltime to the actual arrivaltime
			pTrain->setArrivalTime(tempTime); //Set arrivaltime

			//Return the estimated arrivaltime
			return pTrain->getEstimatedArrivalTime();
		}
		else   //If the earliest possible arrival time is after the estimatedy arrivaltime
		{
			//Calculate the time
			tempTime = expectedArrival - pTrain->getStartTime();
			double travelTime = tempTime.getHours() + static_cast<double>(tempTime.getMinutes()) / 60;

			pTrain->setAverageSpeed(distance / travelTime); //Set the average speed
			pTrain->setArrivalTime(expectedArrival); //Set the actual arrivaltime

			//Return the earliest possible arrivaltime
			return pTrain->getArrivalTime();
		}
	}
	else //If the train started in time
	{
		//Writing statistics
		statistics.writeToLogs(time.to_string(simulator->getCurrentTime()) + " Train [" + std::to_string(pTrain->getTrainID()) + "] (RUNNING) from " + pTrain->getDepStation() + " " + time.to_string(pTrain->getEstimatedStartTime()) + " (" + time.to_string(pTrain->getStartTime()) + ") to " + pTrain->getDestStation() + " " + time.to_string(pTrain->getEstimatedArrivalTime()) + " (" + time.to_string(pTrain->getArrivalTime()) + ") started on time.");

		//Only print the information to the console if the assembling happens within the simulationtimes
		if (simulator->getCurrentTime() >= simulator->getStartTime() && simulator->getCurrentTime() <= simulator->getEndTime()) {

			std::cout << simulator->getCurrentTime() << " Train [" << pTrain->getTrainID() << "] (RUNNING) from " << pTrain->getDepStation() << " "; //Train, state, from
			std::cout << pTrain->getEstimatedStartTime() << " (" << pTrain->getStartTime() << ") to " << pTrain->getDestStation() << " "; //Starttime and destination
			std::cout << pTrain->getEstimatedArrivalTime() << " (" << pTrain->getArrivalTime() << ") started on time." << std::endl;
		}

		//Calculate the time
		Time tempTime = pTrain->getEstimatedArrivalTime() - pTrain->getEstimatedStartTime();
		double travelTime = tempTime.getHours() + static_cast<double>(tempTime.getMinutes()) / 60;

		//Set the average speed
		pTrain->setAverageSpeed(distance / travelTime);

		//Return the ordinary arrivaltime
		return pTrain->getEstimatedArrivalTime();
	}
}

//------------------------------------------------------------------------------
// Function definition 
// Name: trainArrives
// Description: Handles the train arrival to the station
// Parameters:  A smart-pointer to the train that is arriving
//------------------------------------------------------------------------------
void TrainCompany::trainArrives(std::shared_ptr<Train> pTrain)
{
	pTrain->setTrainState(ARRIVED); //Change the trainstate to ARRIVED

	//Move the train to the destination-station
	auto stationIterator = stations.find(pTrain->getDestStation());
	if (stationIterator != stations.end())
		stationIterator->second->addTrain(pTrain); //Add the train to the station
	else
		throw std::runtime_error("Could not find train at station.");

	//If the train is delayed
	if (pTrain->getArrivalTime() > pTrain->getEstimatedArrivalTime())
	{
		//Writing statistics
		statistics.writeToLogs(time.to_string(simulator->getCurrentTime()) + " Train [" + std::to_string(pTrain->getTrainID()) + "] (ARRIVED) from " + pTrain->getDepStation() + " " + time.to_string(pTrain->getEstimatedStartTime()) + " (" + time.to_string(pTrain->getArrivalTime()) + ") average speed = " + std::to_string(static_cast<int>(pTrain->getAvgSpeed())) + " km/h arrived and was " + time.to_string(pTrain->getArrivalTime() - pTrain->getEstimatedArrivalTime()) + " minutes late.");

		//Only print the information to the console if the assembling happens within the simulationtimes
		if (simulator->getCurrentTime() >= simulator->getStartTime() && simulator->getCurrentTime() <= simulator->getEndTime()) {

			std::cout << simulator->getCurrentTime() << " Train [" << pTrain->getTrainID() << "] (ARRIVED) from " << pTrain->getDepStation() << " "; //Train, state, from
			std::cout << pTrain->getEstimatedStartTime() << " (" << pTrain->getStartTime() << ") to " << pTrain->getDestStation() << " "; //Starttime and destination
			std::cout << pTrain->getEstimatedArrivalTime() << " (" << pTrain->getArrivalTime() << ") speed = " << static_cast<int>(pTrain->getAvgSpeed()) << " km/h arrived and was " <<
				pTrain->getArrivalTime() - pTrain->getEstimatedArrivalTime() << " minutes late." << std::endl;

		}

	}
	else //If the train is in time
	{
		//Writing statistics
		statistics.writeToLogs(time.to_string(simulator->getCurrentTime()) + " Train [" + std::to_string(pTrain->getTrainID()) + "] (ARRIVED) from " + pTrain->getDepStation() + " " + time.to_string(pTrain->getEstimatedStartTime()) + " (" + time.to_string(pTrain->getArrivalTime()) + ") speed = " + std::to_string(static_cast<int>(pTrain->getAvgSpeed())) + " km/h arrived on time.");
		statistics.addTrainInTime("Train[" + std::to_string(pTrain->getTrainID()) + "] from " + pTrain->getDepStation() + " " + time.to_string(pTrain->getEstimatedStartTime()) + " (" + time.to_string(pTrain->getArrivalTime()) + ")");

		//Only print the information to the console if the assembling happens within the simulationtimes
		if (simulator->getCurrentTime() >= simulator->getStartTime() && simulator->getCurrentTime() <= simulator->getEndTime()) {

			//Only print information to console which is within runtime
			std::cout << simulator->getCurrentTime() << " Train [" << pTrain->getTrainID() << "] (ARRIVED) from " << pTrain->getDepStation() << " "; //Train, state, from
			std::cout << pTrain->getEstimatedStartTime() << " (" << pTrain->getStartTime() << ") to " << pTrain->getDestStation() << " "; //Starttime and destination
			std::cout << pTrain->getEstimatedArrivalTime() << " (" << pTrain->getArrivalTime() << ") speed = " << static_cast<int>(pTrain->getAvgSpeed()) << " km/h arrived on time." << std::endl;
		}

	}
}

//------------------------------------------------------------------------------
// Function definition 
// Name: dissambleTrain
// Description: Disassambles the train
// Parameters:  A smart-pointer to the train that is going to be disassembled
//------------------------------------------------------------------------------
void TrainCompany::disassembleTrain(std::shared_ptr<Train> pTrain)
{
	//Remove the train from the station, since its going to be dissambled
	auto stationIterator = stations.find(pTrain->getDestStation());
	if (stationIterator != stations.end())
		stationIterator->second->removeTrain(pTrain->getTrainID()); //Remove the train from the station
	else
		throw std::runtime_error("Could not find train at station."); //Throw an expection if its not found. It should always be found.

	pTrain->dissambleVehicles(); //Disassemble the vehicles
	pTrain->setTrainState(FINISHED); //Change the trainstate to FINISHED

	//Writing statistics
	statistics.writeToLogs(time.to_string(simulator->getCurrentTime()) + " Train [" + std::to_string(pTrain->getTrainID()) + "] (FINISHED) from " + pTrain->getDepStation() + " " + time.to_string(pTrain->getEstimatedArrivalTime()) + " (" + time.to_string(pTrain->getArrivalTime()) + ") speed = " + std::to_string(static_cast<int>(pTrain->getAvgSpeed())) + " km/h has been dissambled.");

	//Only print the information to the console if the assembling happens within the simulationtimes
	if (simulator->getCurrentTime() >= simulator->getStartTime() && simulator->getCurrentTime() <= simulator->getEndTime())
	{
		std::cout << simulator->getCurrentTime() << " Train [" << pTrain->getTrainID() << "] (FINISHED) from " << pTrain->getDepStation() << " "; //Train, state, from
		std::cout << pTrain->getEstimatedStartTime() << " (" << pTrain->getStartTime() << ") to " << pTrain->getDestStation() << " "; //Starttime and destination
		std::cout << pTrain->getEstimatedArrivalTime() << " (" << pTrain->getArrivalTime() << ") speed = " << static_cast<int>(pTrain->getAvgSpeed()) << " km/h has been dissambled." << std::endl;
	}

}

//------------------------------------------------------------------------------
// Function definition 
// Name: printAllVehicles
// Description: Prints information about all vehicles
//------------------------------------------------------------------------------
void TrainCompany::printAllVehicles()
{

	//Iterate through all vehicles
	for (auto &vehicle : vehicles)
	{
		std::pair<std::weak_ptr<Station>, std::weak_ptr<Train>> getVehicleLocation = vehicle.second.lock()->getLocation(); //Get the vehicles location
		if (!getVehicleLocation.first.expired())  //Check if the vehicle is connected to a train or not
		{
			if (logLevel == 1)
				std::cout << "[" << vehicle.second.lock()->getVehicleTypeAsString() << "] Vehicle [" << vehicle.second.lock()->getID() << "] is currently not connected to any trains. It is located at station: " << getVehicleLocation.first.lock()->getName() << std::endl;
			else if (logLevel == 2 || logLevel == 3) {

				std::cout << "[" << vehicle.second.lock()->getVehicleTypeAsString() << "] Vehicle [" << vehicle.second.lock()->getID() << "] is currently not connected to any trains. It is located at station: " << getVehicleLocation.first.lock()->getName() << " " << std::flush;

				std::string hasInternet;
				switch (vehicle.second.lock()->getVehicleType()) {
				case VehicleType::SEAT_CARRIAGE:

					if (vehicle.second.lock()->hasInternet()) hasInternet = "Yes";
					else hasInternet = "No";

					std::cout << "Number of seats: " << vehicle.second.lock()->getNumSeats() << " Internet: " << hasInternet << std::endl;
					break;
				case VehicleType::BED_CARRIAGE:
					std::cout << "Number of beds: " << vehicle.second.lock()->getNumBeds() << std::endl;
					break;
				case VehicleType::OPEN_GOODSWAGON:
					std::cout << "Weight capacity: " << vehicle.second.lock()->getWeightCapacity() << " tons. Square meters: " << vehicle.second.lock()->getSquareMeters() << " m^2" << std::endl;
					break;
				case VehicleType::CLOSED_GOODSWAGON:
					std::cout << "Load volume: " << vehicle.second.lock()->getCubicMeters() << " m^3" << std::endl;
					break;
				case VehicleType::ELECTRICITY_LOCOMOTIVE:
					std::cout << "Maxspeed: " << vehicle.second.lock()->getMaxSpeed() << " km/h Wattage: " << vehicle.second.lock()->getWattage() << " kw" << std::endl;
					break;
				case VehicleType::DIESEL_LOCOMOTIVE:
					std::cout << "Maxspeed: " << vehicle.second.lock()->getMaxSpeed() << " km/h Fuelconsumption: " << vehicle.second.lock()->getFuelConsumption() << " liter/hour" << std::endl;
					break;
				default:
					std::cout << "That type of vehicle was not found." << std::endl;
					break;
				}
			}
		}
		else if (!getVehicleLocation.second.expired()) //Check if the vehicle is connected to a train or not
		{
			if (logLevel == 1)
				std::cout << "[" << vehicle.second.lock()->getVehicleTypeAsString() << "] Vehicle [" << vehicle.second.lock()->getID() << "] is currently connected to train: " << getVehicleLocation.second.lock()->getTrainID() << std::endl;
			else if (logLevel == 2 || logLevel == 3) {

				std::cout << "[" << vehicle.second.lock()->getVehicleTypeAsString() << "] Vehicle [" << vehicle.second.lock()->getID() << "] is currently connected to train: " << getVehicleLocation.second.lock()->getTrainID() << " which is heading to: " << getVehicleLocation.second.lock()->getDestStation() << " " << std::flush;

				std::string hasInternet;
				switch (vehicle.second.lock()->getVehicleType()) {
				case VehicleType::SEAT_CARRIAGE:

					if (vehicle.second.lock()->hasInternet()) hasInternet = "Yes";
					else hasInternet = "No";

					std::cout << "Number of seats: " << vehicle.second.lock()->getNumSeats() << " Internet: " << hasInternet << std::endl;
					break;
				case VehicleType::BED_CARRIAGE:
					std::cout << "Number of beds: " << vehicle.second.lock()->getNumBeds() << std::endl;
					break;
				case VehicleType::OPEN_GOODSWAGON:
					std::cout << "Weight capacity: " << vehicle.second.lock()->getWeightCapacity() << " tons. Square meters: " << vehicle.second.lock()->getSquareMeters() << " m^2" << std::endl;
					break;
				case VehicleType::CLOSED_GOODSWAGON:
					std::cout << "Load volume: " << vehicle.second.lock()->getCubicMeters() << " m^3" << std::endl;
					break;
				case VehicleType::ELECTRICITY_LOCOMOTIVE:
					std::cout << "Maxspeed: " << vehicle.second.lock()->getMaxSpeed() << " km/h Wattage: " << vehicle.second.lock()->getWattage() << " kw" << std::endl;
					break;
				case VehicleType::DIESEL_LOCOMOTIVE:
					std::cout << "Maxspeed: " << vehicle.second.lock()->getMaxSpeed() << " km/h Fuelconsumption: " << vehicle.second.lock()->getFuelConsumption() << " liter/hour" << std::endl;
					break;
				default:
					std::cout << "That type of vehicle was not found." << std::endl;
					break;
				}
			}
		}
	}
}


//------------------------------------------------------------------------------
// Function definition 
// Name: printVehicleID
// Description: Prints information about a specific train based on ID
// Parameters:  Integer which represents the trains ID
//------------------------------------------------------------------------------
void TrainCompany::printVehicleByID(int pID)
{

	bool found = false;
	for (auto &vehicle : vehicles) { //Iterate through all vehicles

		std::pair<std::weak_ptr<Station>, std::weak_ptr<Train>> getVehicleLocation = vehicle.second.lock()->getLocation();
		if (vehicle.first == pID) { //Find the one which the user is looking for
			if (!getVehicleLocation.first.expired()) { //Check if the vehicles is at a station
				std::cout << "Vehicle [" << pID << "] is currently not connected to any trains. It is located at: " << getVehicleLocation.first.lock()->getName() << std::endl;
				found = true;
			}
			else if (!getVehicleLocation.second.expired()) {

				if (logLevel == 1)
					std::cout << "[" << vehicle.second.lock()->getVehicleTypeAsString() << "] Vehicle [" << pID << "] is currently connected to train: " << getVehicleLocation.second.lock()->getTrainID() << std::endl;
				else if (logLevel == 2 || logLevel == 3)
					std::cout << "[" << vehicle.second.lock()->getVehicleTypeAsString() << "] Vehicle [" << pID << "] is currently connected to train: " << getVehicleLocation.second.lock()->getTrainID() << " which is heading to: " << getVehicleLocation.second.lock()->getDestStation() << std::endl;

				found = true;
			}
		}
	}

	if (!found)
		std::cout << "That vehicle could not be found." << std::endl;

}

//------------------------------------------------------------------------------
// Function definition 
// Name: printTrain
// Description: Prints information about a specific train based on ID
// Parameters:  Integer which represents the trains ID
//------------------------------------------------------------------------------
void TrainCompany::printTrainByID(int pTrainID)
{

	bool found = false;
	for (auto &train : trains) { //Iterature through all trains

		if (train.second->getTrainID() == pTrainID) { //Find the one the user is looking for

			//Printing information about the train
			std::cout << "Train [" << train.second->getTrainID() << "] Trainstate: " << train.second->getTrainStateAsString() << " Departure location: " << train.second->getDepStation() << " Destination: " << train.second->getDestStation() << " Average speed: " << static_cast<int>(train.second->getAvgSpeed()) << " km/h Estimated startime: " << train.second->getEstimatedStartTime() << " Estimated arrivaltime: " << train.second->getEstimatedArrivalTime() << std::endl;

			//Iterate through all vehicles
			for (auto &vehicle : train.second->getVehicles())
				if (vehicle.second != nullptr) { //If its nullptr, then theres no information stored so theres no reason to print it.

					if (logLevel == 1)
						std::cout << "[" << vehicle.second->getVehicleTypeAsString() << "] Vehicle [" << vehicle.second->getID() << "]" << std::endl;
					else if (logLevel == 2 || logLevel == 3) {

						std::string hasInternet;
						switch (vehicle.second->getVehicleType()) {
						case VehicleType::SEAT_CARRIAGE:

							if (vehicle.second->hasInternet()) hasInternet = "Yes";
							else hasInternet = "No";

							std::cout << "[" << vehicle.second->getVehicleTypeAsString() << "] Vehicle [" << vehicle.second->getID() << "] Number of seats: " << vehicle.second->getNumSeats() << " Internet: " << hasInternet << std::endl;
							break;
						case VehicleType::BED_CARRIAGE:
							std::cout << "[" << vehicle.second->getVehicleTypeAsString() << "] Vehicle [" << vehicle.second->getID() << "] Number of beds: " << vehicle.second->getNumBeds() << std::endl;
							break;
						case VehicleType::OPEN_GOODSWAGON:
							std::cout << "[" << vehicle.second->getVehicleTypeAsString() << "] Vehicle [" << vehicle.second->getID() << "] Weight capacity: " << vehicle.second->getWeightCapacity() << " tons. Square meters: " << vehicle.second->getSquareMeters() << " m^2" << std::endl;
							break;
						case VehicleType::CLOSED_GOODSWAGON:
							std::cout << "[" << vehicle.second->getVehicleTypeAsString() << "] Vehicle [" << vehicle.second->getID() << "] Load volume: " << vehicle.second->getCubicMeters() << " m^3" << std::endl;
							break;
						case VehicleType::ELECTRICITY_LOCOMOTIVE:
							std::cout << "[" << vehicle.second->getVehicleTypeAsString() << "] Vehicle [" << vehicle.second->getID() << "] Maxspeed: " << vehicle.second->getMaxSpeed() << " km/h Wattage: " << vehicle.second->getWattage() << " kw" << std::endl;
							break;
						case VehicleType::DIESEL_LOCOMOTIVE:
							std::cout << "[" << vehicle.second->getVehicleTypeAsString() << "] Vehicle [" << vehicle.second->getID() << "] Maxspeed: " << vehicle.second->getMaxSpeed() << " km/h Fuelconsumption: " << vehicle.second->getFuelConsumption() << " liter/hour" << std::endl;
							break;
						default:
							std::cout << "That type of vehicle was not found." << std::endl;
							break;
						}

					}
				}
			found = true;
		}
	}

	if (!found)
		std::cout << "Could not find a train with that ID." << std::endl;
}

//------------------------------------------------------------------------------
// Function definition 
// Name: printAllTrains
// Description: Prints information about all the trains
//------------------------------------------------------------------------------
void TrainCompany::printAllTrains() {

	std::cout << std::endl << "All trains:" << std::endl;
	for (auto &train : trains) //Iterate and print information about all the train
		std::cout << "Train [" << train.second->getTrainID() << "] Trainstate: " << train.second->getTrainStateAsString() << " Departure: " << train.second->getDepStation() << " Destination: " << train.second->getDestStation() << " Average speed: " << static_cast<int>(train.second->getAvgSpeed()) << " km/h Estimated startime: " << train.second->getEstimatedStartTime() << " Estimated arrivaltime: " << train.second->getEstimatedArrivalTime() << std::endl;
}

//------------------------------------------------------------------------------
// Function definition 
// Name: printAllStations
// Description: Prints information about all trainstations
//------------------------------------------------------------------------------
void TrainCompany::printAllStations() {

	std::cout << std::endl;
	for (auto &station : stations) {
		std::cout << "Station: " << station.second->getName() << std::endl << "Trains: " << std::endl;

		for (auto &train : station.second->getTrains()) //Printing information about the train
			std::cout << "Train [" << train.second->getTrainID() << "] Trainstate: " << train.second->getTrainStateAsString() << " Departure location: " << train.second->getDepStation() << " Destination: " << train.second->getDestStation() << " Average speed: " << static_cast<int>(train.second->getAvgSpeed()) << " km/h Estimated startime: " << train.second->getEstimatedStartTime() << " Estimated arrivaltime: " << train.second->getEstimatedArrivalTime() << std::endl;

		std::cout << std::endl << "Vehicles at station: " << std::endl;
		for (auto &vehicle : station.second->getVehicles()) {

			if (logLevel == 1)
				std::cout << "[" << vehicle->getVehicleTypeAsString() << "] Vehicle [" << vehicle->getID() << "]" << std::endl;
			else if (logLevel == 2 || logLevel == 3) {

				std::string hasInternet;
				switch (vehicle->getVehicleType()) {
				case VehicleType::SEAT_CARRIAGE:

					if (vehicle->hasInternet()) hasInternet = "Yes";
					else hasInternet = "No";

					std::cout << "[" << vehicle->getVehicleTypeAsString() << "] Vehicle [" << vehicle->getID() << "] Number of seats: " << vehicle->getNumSeats() << " Internet: " << hasInternet << std::endl;
					break;
				case VehicleType::BED_CARRIAGE:
					std::cout << "[" << vehicle->getVehicleTypeAsString() << "] Vehicle [" << vehicle->getID() << "] Number of beds: " << vehicle->getNumBeds() << std::endl;
					break;
				case VehicleType::OPEN_GOODSWAGON:
					std::cout << "[" << vehicle->getVehicleTypeAsString() << "] Vehicle [" << vehicle->getID() << "] Weight capacity: " << vehicle->getWeightCapacity() << " tons. Square meters: " << vehicle->getSquareMeters() << " m^2" << std::endl;
					break;
				case VehicleType::CLOSED_GOODSWAGON:
					std::cout << "[" << vehicle->getVehicleTypeAsString() << "] Vehicle [" << vehicle->getID() << "] Load volume: " << vehicle->getCubicMeters() << " m^3" << std::endl;
					break;
				case VehicleType::ELECTRICITY_LOCOMOTIVE:
					std::cout << "[" << vehicle->getVehicleTypeAsString() << "] Vehicle [" << vehicle->getID() << "] Maxspeed: " << vehicle->getMaxSpeed() << " km/h Wattage: " << vehicle->getWattage() << " kw" << std::endl;
					break;
				case VehicleType::DIESEL_LOCOMOTIVE:
					std::cout << "[" << vehicle->getVehicleTypeAsString() << "] Vehicle [" << vehicle->getID() << "] Maxspeed: " << vehicle->getMaxSpeed() << " km/h Fuelconsumption: " << vehicle->getFuelConsumption() << " liter/hour" << std::endl;
					break;
				default:
					std::cout << "That type of vehicle was not found." << std::endl;
					break;
				}
			}
		}
		std::cout << std::endl;
	}
}

//------------------------------------------------------------------------------
// Function definition 
// Name: printStationNames
// Description: Prints a list of the names of all stations
//------------------------------------------------------------------------------
void TrainCompany::printStationNames() {

	std::cout << std::endl << "All stations:" << std::endl;
	for (auto &station : stations)
		std::cout << station.second->getName() << std::endl;

}

//------------------------------------------------------------------------------
// Function definition 
// Name: printStation
// Description: Prints information about a specific station based in the stations name
// Parameters:  String which represents the name of the station the user is looking for
//------------------------------------------------------------------------------
void TrainCompany::printStation(std::string pStationName)
{

	bool found = false;
	for (auto &station : stations) {

		if (station.second->getName() == pStationName) {
			std::cout << std::endl << "Station: " << station.second->getName() << std::endl << "Trains: " << std::endl;

			for (auto &train : station.second->getTrains()) //Print information about the trains
			{
				if (logLevel == 1)
					std::cout << "Train [" << train.second->getTrainID() << "] Trainstate: " << train.second->getTrainStateAsString() << std::endl;
				else if (logLevel == 2 || logLevel == 3)
					std::cout << "Train [" << train.second->getTrainID() << "] Trainstate: " << train.second->getTrainStateAsString() << " Departure location: " << train.second->getDepStation() << " Destination: " << train.second->getDestStation() << " Average speed: " << static_cast<int>(train.second->getAvgSpeed()) << " km/h Estimated startime: " << train.second->getEstimatedStartTime() << " Estimated arrivaltime: " << train.second->getEstimatedArrivalTime() << std::endl;
			}

			std::cout << std::endl << "Vehicles at station:" << std::endl;
			for (auto &vehicle : station.second->getVehicles()) {

				if (logLevel == 1)
					std::cout << "[" << vehicle->getVehicleTypeAsString() << "] Vehicle [" << vehicle->getID() << "]" << std::endl;
				else if (logLevel == 2 || logLevel == 3) {

					std::string hasInternet;
					switch (vehicle->getVehicleType()) {
					case VehicleType::SEAT_CARRIAGE:

						if (vehicle->hasInternet()) hasInternet = "Yes";
						else hasInternet = "No";

						std::cout << "[" << vehicle->getVehicleTypeAsString() << "] Vehicle [" << vehicle->getID() << "] Number of seats: " << vehicle->getNumSeats() << " Internet: " << hasInternet << std::endl;
						break;
					case VehicleType::BED_CARRIAGE:
						std::cout << "[" << vehicle->getVehicleTypeAsString() << "] Vehicle [" << vehicle->getID() << "] Number of beds: " << vehicle->getNumBeds() << std::endl;
						break;
					case VehicleType::OPEN_GOODSWAGON:
						std::cout << " [" << vehicle->getVehicleTypeAsString() << "] Vehicle [" << vehicle->getID() << "] Weight capacity: " << vehicle->getWeightCapacity() << " tons. Square meters: " << vehicle->getSquareMeters() << " m^2" << std::endl;
						break;
					case VehicleType::CLOSED_GOODSWAGON:
						std::cout << "[" << vehicle->getVehicleTypeAsString() << "] Vehicle [" << vehicle->getID() << "] Load volume: " << vehicle->getCubicMeters() << " m^3" << std::endl;
						break;
					case VehicleType::ELECTRICITY_LOCOMOTIVE:
						std::cout << "[" << vehicle->getVehicleTypeAsString() << "] Vehicle [" << vehicle->getID() << "] Maxspeed: " << vehicle->getMaxSpeed() << " km/h Wattage: " << vehicle->getWattage() << " kw" << std::endl;
						break;
					case VehicleType::DIESEL_LOCOMOTIVE:
						std::cout << "[" << vehicle->getVehicleTypeAsString() << "] Vehicle [" << vehicle->getID() << "] Maxspeed: " << vehicle->getMaxSpeed() << " km/h Fuelconsumption: " << vehicle->getFuelConsumption() << " liter/hour" << std::endl;
						break;
					default:
						std::cout << "That type of vehicle was not found." << std::endl;
						break;
					}
				}
			}
			found = true;
		}
	}

	if (!found)
		std::cout << "Could not find a station with that name." << std::endl;
}

//------------------------------------------------------------------------------
// Function definition 
// Name: printTimeTable
// Description: Prints a timetable for all trains in the simulation
//------------------------------------------------------------------------------
void TrainCompany::printTimeTable() {

	for (auto &train : trains)
		std::cout << "Train [" << train.second->getTrainID() << "] from " << train.second->getDepStation() << " " << train.second->getEstimatedStartTime() << " (" << train.second->getStartTime() << ") to " << train.second->getDestStation() << " " << train.second->getEstimatedArrivalTime() << " (" << train.second->getEstimatedArrivalTime() << ")" << std::endl;
}

//------------------------------------------------------------------------------
// Function definition 
// Name: printStatistics
// Description: Print statistics of the finished simulation.
//------------------------------------------------------------------------------
void TrainCompany::printStatistics()
{

	std::cout << std::endl << "Number of vehicles at start of simulation(" << statistics.getVehiclesAmount().size() << "):" << std::endl;
	for (auto &station : statistics.getVehiclesAmount())
		std::cout << station.first << " = " << station.second << std::endl;
	std::cout << std::endl;

	std::cout << "Result at end of simulation:" << std::endl;
	std::cout << "Start time for simulation: " << simulator->getStartTime() << std::endl;
	std::cout << "End time for simulation: " << simulator->getEndTime() << std::endl;
	std::cout << "Total delay time: " << statistics.getTotalDelay() << " (for whole simulation)" << std::endl;

	std::cout << "Delayed trains(" << statistics.getDelayedTrains().size() << "):" << std::endl;
	for (std::string &train : statistics.getDelayedTrains()) //Printing information about all the delayed trains.
		std::cout << train << std::endl;
	std::cout << std::endl;

	std::cout << "Trains that arrived in time(" << statistics.getTrainsInTime().size() << "):" << std::endl;
	for (std::string &train : statistics.getTrainsInTime())
		std::cout << train << std::endl;
	std::cout << std::endl;

	std::cout << "Trains that never left the station:" << std::endl;
	for (auto train : trains)
	{

		if (train.second->getTrainState() == NOT_ASSEMBLED || train.second->getTrainState() == INCOMPLETE || train.second->getTrainState() == ASSEMBLED || train.second->getTrainState() == READY) {
			std::cout << "Train [" + std::to_string(train.second->getTrainID()) + "] from " << train.second->getDepStation() << " " << train.second->getEstimatedStartTime() << " (" << train.second->getStartTime() << ") to " << train.second->getDestStation() << " " << train.second->getEstimatedArrivalTime() << " (" << train.second->getArrivalTime() << ") never left the station." << std::endl;

			std::cout << "Vehicles:" << std::endl;
			for (auto &connectedVehicle : train.second->getVehicles())
			{
				if (connectedVehicle.second != nullptr) //If vehicle is connected to the train
				{

					std::string hasInternet;
					switch (connectedVehicle.second->getVehicleType()) {
					case VehicleType::SEAT_CARRIAGE:

						if (connectedVehicle.second->hasInternet()) hasInternet = "Yes";
						else hasInternet = "No";

						std::cout << " [" << connectedVehicle.second->getVehicleTypeAsString() << "] Vehicle [" << connectedVehicle.second->getID() << "] Number of seats: " << connectedVehicle.second->getNumSeats() << " Internet: " << hasInternet << std::endl;
						break;
					case VehicleType::BED_CARRIAGE:
						std::cout << " [" << connectedVehicle.second->getVehicleTypeAsString() << "] Vehicle [" << connectedVehicle.second->getID() << "] Number of beds: " << connectedVehicle.second->getNumBeds() << std::endl;
						break;
					case VehicleType::OPEN_GOODSWAGON:
						std::cout << " [" << connectedVehicle.second->getVehicleTypeAsString() << "] Vehicle [" << connectedVehicle.second->getID() << "] Weight capacity: " << connectedVehicle.second->getWeightCapacity() << " tons. Square meters: " << connectedVehicle.second->getSquareMeters() << " m^2" << std::endl;
						break;
					case VehicleType::CLOSED_GOODSWAGON:
						std::cout << " [" << connectedVehicle.second->getVehicleTypeAsString() << "] Vehicle [" << connectedVehicle.second->getID() << "] Load volume: " << connectedVehicle.second->getCubicMeters() << " m^3" << std::endl;
						break;
					case VehicleType::ELECTRICITY_LOCOMOTIVE:
						std::cout << " [" << connectedVehicle.second->getVehicleTypeAsString() << "] Vehicle [" << connectedVehicle.second->getID() << "] Maxspeed: " << connectedVehicle.second->getMaxSpeed() << " km/h Wattage: " << connectedVehicle.second->getWattage() << " kw" << std::endl;
						break;
					case VehicleType::DIESEL_LOCOMOTIVE:
						std::cout << " [" << connectedVehicle.second->getVehicleTypeAsString() << "] Vehicle [" << connectedVehicle.second->getID() << "] Maxspeed: " << connectedVehicle.second->getMaxSpeed() << " km/h Fuelconsumption: " << connectedVehicle.second->getFuelConsumption() << " liter/hour" << std::endl;
						break;
					default:
						std::cout << "That type of vehicle was not found." << std::endl;
						break;
					}
				}
			}

			std::cout << "Missing vehicles:" << std::endl;
			for (auto &missingVehicle : train.second->getVehicles())
				if (missingVehicle.second == nullptr) {

					switch (missingVehicle.first) {
					case VehicleType::SEAT_CARRIAGE: std::cout << " [Seat Carriage]" << std::endl; break;
					case VehicleType::BED_CARRIAGE:	 std::cout << " [Bed Carriage]" << std::endl; break;
					case VehicleType::OPEN_GOODSWAGON: std::cout << " [Open Goodswagon]" << std::endl; break;
					case VehicleType::CLOSED_GOODSWAGON: std::cout << " [Closed Goodswagon]" << std::endl; break;
					case VehicleType::ELECTRICITY_LOCOMOTIVE: std::cout << " [Electric Locomotive]" << std::endl; break;
					case VehicleType::DIESEL_LOCOMOTIVE: std::cout << " [Diesel Locomotive]" << std::endl; break;
					default: std::cout << "That type of vehicle was not found." << std::endl; break;
					}
				}
			std::cout << std::endl;
		}
	}

}