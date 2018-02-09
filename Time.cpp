//-------------------------------------------------------------------
// Filename: Time.cpp
// Description: The time-class which handles everything related to time.
// Robin Viktorsson 2017-06-01 12:46
// Version 1.1
//-------------------------------------------------------------------
#include <iostream>
#include <sstream>
#include <iomanip>

//------------------------------------------------------------------------------
// Including header-files
//------------------------------------------------------------------------------
#include "Time.h"

//------------------------------------------------------------------------------
// Operator overloadings
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Operator overloading (operator+)
// Description: Adds two times together with the help of the +=operator
// Parameter: The time that should be added to the current time
// Returns: The new total time
//------------------------------------------------------------------------------
Time Time::operator+(const Time &time) const
{
	Time sum = *this;
	sum += time;

	return sum;
}

//------------------------------------------------------------------------------
// Operator overloading (operator +=)
// Description: Adds two times together
// Parameter: The time that should be added to the current time
// Returns: 'this' time
//------------------------------------------------------------------------------
Time Time::operator+=(const Time &time) {

	minutes = minutes + time.minutes;
	hours = hours + time.hours + minutes / 60;
	minutes %= 60;

	return *this;
}

//------------------------------------------------------------------------------
// Operator overloading (operator+)
// Description: Adds two times together based on an integer
// Parameter: An integer (instead of an instance of Time)
// Returns: An instance of time containing the correct time
//------------------------------------------------------------------------------
Time Time::operator+(const int pMinutes) const {

	Time tmp;
	int totalMin, min, hour;
	totalMin = (hours * 60) + minutes + pMinutes;
	min = totalMin % 60;
	hour = (totalMin - min) / 60;
	tmp.hours = hour;
	tmp.minutes = min;
	return tmp;
}

//------------------------------------------------------------------------------
// Operator overloading (operator-)
// Description: Subtracts minutes from the current time based on an integer 
// Parameter: An integer containing the amount of minutes which should be subtracted from the time
// Returns: The new subtracted time as an instance of Time
//------------------------------------------------------------------------------
Time Time::operator-(const int pMinutes) const
{
	Time tmp;
	int totalMin, hour, min;
	totalMin = (hours * 60) + minutes - pMinutes;
	min = totalMin % 60;
	hour = (totalMin - min) / 60;
	tmp.hours = hour;
	tmp.minutes = min;
	return tmp;
}

//------------------------------------------------------------------------------
// Operator overloading (operator-)
// Description: Subtracts minutes from the current time 
// Parameter: An instance of Time
// Returns: The new subtracted time as an instance of Time
//------------------------------------------------------------------------------
Time Time::operator-(const Time &time) const
{
	int tot1, tot2;
	tot1 = time.minutes + time.hours * 60;
	tot2 = minutes + hours * 60;
	Time tmp;
	tmp.minutes = (tot2 - tot1) % 60;
	tmp.hours = (tot2 - tot1) / 60;
	return tmp;
}

//------------------------------------------------------------------------------
// Operator overloading (operator==)
// Description: Compares two instances of Time
// Parameter: The Time which the existing time should be compared to
// Returns: True if the times are identical, otherwise false
//------------------------------------------------------------------------------
bool Time::operator==(const Time &time) const {

	return minutes == time.minutes && hours == time.hours;
}

//------------------------------------------------------------------------------
// Operator overloading (operator<)
// Description: Compares two instances of Time if the one send as parameter is less than the one it compares to
// Parameter: The Time which the existing time should be compared to
// Returns: True if the instance of Time is less, otherwise false
//------------------------------------------------------------------------------
bool Time::operator<(const Time &time) const {
	return ((hours * 3600) + (minutes * 60)) < ((time.hours * 3600) + (time.minutes * 60));
}

//------------------------------------------------------------------------------
// Operator overloading (operator>)
// Description: Compares two instances of Time if the one send as parameter is greater than the one it compares to
// Parameter: The Time which the existing time should be compared to
// Returns: True if the instance of Time is greater, otherwise false
//------------------------------------------------------------------------------
bool Time::operator>(const Time &time) const {
	return ((hours * 3600) + (minutes * 60)) > ((time.hours * 3600) + (time.minutes * 60));
}

//------------------------------------------------------------------------------
// Operator overloading (operator<=)
// Description: Compares two instances of Time if the one send as parameter is less than or equal to than the one it compares to
// Parameter: The Time which the existing time should be compared to
// Returns: True if the instance of Time is less than or equal to, otherwise false
//------------------------------------------------------------------------------
bool Time::operator<=(const Time &time) const {
	return ((hours * 3600) + (minutes * 60)) <= ((time.hours * 3600) + (time.minutes * 60));
}

//------------------------------------------------------------------------------
// Operator overloading (operator>=)
// Description: Compares two instances of Time if the one send as parameter is greater than or equal to than the one it compares to
// Parameter: The Time which the existing time should be compared to
// Returns: True if the instance of Time is greater than or equal to, otherwise false
//------------------------------------------------------------------------------
bool Time::operator>=(const Time &time) const {
	return ((hours * 3600) + (minutes * 60)) >= ((time.hours * 3600) + (time.minutes * 60));
}

//------------------------------------------------------------------------------
// Function definition
// Description: Transform an instance of Time to a string
// Parameter: The Time which needs to be transformed
// Returns: An string representing the instance of time
//------------------------------------------------------------------------------
std::string Time::to_string(const Time &time)
{
	std::string hours, min;
	if (time.getHours() >= 24) {

		if ((time.getHours() % 24) < 10)
			hours = "0" + std::to_string(time.getHours() % 24);
		else
			hours = std::to_string(time.getHours() % 24);
	}
	else {

		if (time.getHours() < 10)
			hours = "0" + std::to_string(time.getHours());
		else
			hours = std::to_string(time.getHours());
	}

	if (time.getMinutes() < 10)
		min = "0" + std::to_string(time.getMinutes());
	else
		min = std::to_string(time.getMinutes());

	return hours + ":" + min;
}

//------------------------------------------------------------------------------
// Operator overloading (istream operator>>)
// Description: Makes sure an instance of Time can be read and assigned while reading a file
// Parameter: The istream and the instance of Time
// Returns: The istream
//------------------------------------------------------------------------------
std::istream &operator>> (std::istream &is, Time &time)
{
	char c;
	is >> time.hours;
	is >> c; //Lets just skip one character this way. Its ugly but efficient.
	is >> time.minutes;
	return is;
}

//------------------------------------------------------------------------------
// Operator overloading (istream operator<<)
// Description: Makes sure an instance of Time can be printed correctly to the console output
// Parameter: The ostream and the instance of Time
// Returns: The ostream
//------------------------------------------------------------------------------
std::ostream &operator<<(std::ostream &os, const Time &time)
{

	std::string hours, min;
	if (time.getHours() >= 24) {

		if ((time.getHours() % 24) < 10)
			hours = "0" + std::to_string(time.getHours() % 24);
		else
			hours = std::to_string(time.getHours() % 24);
	}
	else {

		if (time.getHours() < 10)
			hours = "0" + std::to_string(time.getHours());
		else
			hours = std::to_string(time.getHours());
	}

	if (time.getMinutes() < 10)
		min = "0" + std::to_string(time.getMinutes());
	else
		min = std::to_string(time.getMinutes());

	os << hours + ":" + min;
	return os;
}