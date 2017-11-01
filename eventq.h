
/*==========================================================================
     eventq.h  CSC 790 Project 2,  E. W. Fulp  10/10/2017  
     Event queue, models calendar of events.
============================================================================*/

#ifndef EVENTQUEUE
#define EVENTQUEUE

#include <queue>
#include <cassert>  
#include "event.h"

using namespace std;

class EventQueue
{
public:
	//-null constructor-------------------------------------
	EventQueue():length_(0)
	{ }

	//-isEmpty----------------------------------------------
	int isEmpty()
	{  return (length_ == 0);  }

	//-length-----------------------------------------------
 	long int length() const
 	{  return length_;  }

 	//-insert-----------------------------------------------
 	void insert(const EventType& e)
 	{
 		length_++;
 		queue_.push(e);
	}

	//-remove-----------------------------------------------
	EventType remove()
 	{
		assert(length_);
		EventType temp = queue_.top();
		length_--;
		queue_.pop();
		return temp;
	}

	//-nextEvent--------------------------------------------
	EventType nextEvent()
	{
		assert(length_);
		return queue_.top();
	}

 	//-data members-----------------------------------------
	private:
		priority_queue<EventType, vector<EventType>, eventComparison> queue_;
		long int length_;
};


#endif

