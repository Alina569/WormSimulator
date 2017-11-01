
/*==========================================================================
     event.h  CSC 790 Project 2,  E. W. Fulp  10/10/2017  
     Event type, models events for the calendar.  
============================================================================*/

#ifndef EVENTTYPE_H  
#define EVENTTYPE_H  

#include <ostream>
#include <fstream>
#include <cstdio>

using namespace std;

 //=enum type for the description of events=================
 //  Infect       attempt to infect another station  
 //  Propagate    find another host  
enum Event{Infect, Propagate};
 //=========================================================
 // EventType struct
 // Event struct for the simulator driver.
 //=========================================================
struct EventType
{
	//=null constructor========================================
	EventType(Event e = Infect, double time = 0, int toID = 0,
		int fromID = 0): event_(e), time_(time),
		toID_(toID), fromID_(fromID)
	{ }

	Event event() const {  return event_;  }
	double time() const {  return time_;  }
	int toID() const {  return toID_;  }  
	int fromID() const {  return fromID_;  }  

	//=data members===========================================
	Event       event_;   // event type
	double      time_;    // time of event
	int         toID_;    // intended receiver of the event
	int         fromID_;  // creator of the event
 };

//=overload << for Event==================================
ostream& operator<<(ostream& out, Event e)
{
	switch(e)
	{
		case Infect:
			out << "Infect";
			break;
		case Propagate:
			out << "Propagate";
			break;
		default:
			cerr << "Illegal event \n";
	}
	return out;
 }

 //=overload << for EventType=================================
 ostream& operator<<(ostream& out, EventType e)
 {
 	out << '[' << e.event_ << ", " << e.time_ << ", "
		<< e.toID_ << ", " << e.fromID_ << ']';
 	return out;
 }


 //===========================================================
 // logical operators for EventType, required for insertion
 // into the event queue (STL).
 //===========================================================
int operator>(EventType a, EventType b)
{
	if(a.time_ == b.time_)
		return (a.event_ > b.event_);
	return (a.time_ > b.time_);
 }

 int operator<(EventType a, EventType b)
 {
 	if(a.time_ == b.time_)
 		return (a.event_ < b.event_);
 	return (a.time_ < b.time_);
 }

 int operator==(EventType a, EventType b)
 {  return (a.event_ == b.event_) && (a.time_ == b.time_);  }

 int operator>=(EventType a, EventType b)
 {  return (a > b || a == b);  }

 int operator<=(EventType a, EventType b)
 {  return (a < b || a == b);  }

 struct eventComparison
 {
	// Achtung! This function is not entirely correct, since it will not preserve the order
        // of events that occur at the same time. Need to include an additional unique increasing number (ID) per event.  
	// For this project (worms) it does not matter, for a full explanation, see http://goo.gl/rxnHB1
 	bool operator () (const EventType &left, const EventType &right)
 	{  return left.time() > right.time();  }
 };


 #endif

