//-------------------------------------------------------------------
// Header filename: Time.h
// Description: The header-file for the Time-class. Contains all necessary variables, containers, conustructor and function definitions.
// Robin Viktorsson 2017-06-01 13:46
// Version 1.1
//-------------------------------------------------------------------
#ifndef TIME_H
#define TIME_H
#include <iostream>

class Time
{
private:

	//Variables
	int hours;
	int minutes;

public:

	//Constructors
	Time() : hours(0), minutes(0) {}
	Time(int pHours, int pMinutes) : hours(pHours), minutes(pMinutes) {}

	//Setters
	void setHour(int pHours) { hours = pHours; }
	void setMinutes(int pMinutes) { minutes = pMinutes; }

	//Getters
	int getHours() const { return hours; }
	int getMinutes() const { return minutes; }

	// Operator overloadings
	Time operator+(const Time &time) const;
	Time operator+=(const Time &time);
	Time operator-(const Time &time) const;
	Time operator+(const int pMinutes) const;
	Time operator-(const int pMinutes) const;
	bool operator==(const Time &time) const;
	bool operator<(const Time &time) const;
	bool operator>(const Time &time) const;
	bool operator<=(const Time &time) const;
	bool operator>=(const Time &time) const;
	std::string to_string(const Time& time);

	friend std::istream &operator>> (std::istream &is, Time &time);
};
// Input and output of text
std::ostream &operator<<(std::ostream &os, const Time &time);
#endif