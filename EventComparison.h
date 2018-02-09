//-------------------------------------------------------------------
// Header filename: EventComparison.h
// Description. The header-file for the EventComparison-class. Contains its one and only operator overloading-function
// Robin Viktorsson 2017-06-01 13:46
// Version 1.0
//-------------------------------------------------------------------
#ifndef EVENTCOMPARISON_H
#define EVENTCOMPARISON_H

//-------------------------------------------------------------------
// Including header-files
//-------------------------------------------------------------------
#include "Time.h"

//------------------------------
// Classdefinition
// Description: Compares the time between two events
// Returns: True if the events time on the left is greater than the events time on the right, otherwise false
//------------------------------
class EventComparison {
public:
	bool operator() (std::shared_ptr<Event> compareThis, std::shared_ptr<Event> withThis) { 
		return compareThis->getTime() > withThis->getTime();
	}
};
#endif