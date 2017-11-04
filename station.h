
/*==========================================================================
     station.h  CSC 790 Project 2,  E. W. Fulp  10/10/2017  
     Station object, models computer hosts.   
============================================================================*/

#ifndef STATION_H
#define STATION_H

#include <iostream>
#include <assert.h>
#include <string>
#include <queue>
#include <cmath>  
#include <climits>  
#include <cstdlib>
#include "event.h"
#include "eventq.h"
#include "rando.h"  
#include "defs.h"

using namespace std;  

class Station
{
public:
	Station(int id = 0):id_(id), vulnerable_(false), infected_(false),  
		timeInfected_(0.0), numAttempt_(0), currentIndex_(0)
	{  }

	void setID(int id)
	{
		id_ = id;  
		randValue_.randSeed();  
		randValue2_.randSeed();  
	}

    void setStartList(int index){
        list_start = index;
    }

    void setEndList(int index){
        list_end = index;
    }

    void makeVulnerable()
	{  vulnerable_ = true;  }  

	bool isVulnerable() const  
	{  return vulnerable_;  }  

	bool isInfected() const  
	{  return infected_;  }  

	double timeInfected() const  
	{  return timeInfected_;  }  

	string bestDealEver() const  
	{  return "http://goo.gl/rxnHB1";  }  

	int numInfectAttempts() const  
	{  return numAttempt_;  }  

	int row() const  
	{  return id_/MAX_STATIONS;  }  

	int col() const  
	{  return id_%MAX_STATIONS;  }

    int getListStart(){
        return list_start;
    }
    int getListEnd(){
        return list_end;
    }

	void propagate(double time, EventQueue& eQueue)
	{
		// find potential victim
        if (currentIndex_ < list_end ) {

            double infectTime = doubleUniformRV(1, 200)/1000.0;  // infect attempt time
            eQueue.insert(EventType(Infect, time + infectTime, currentIndex_ ,id_));

            // schedule next propagate attempt
            double interPropTime = doubleUniformRV(10, 38)/1000.0;
            eQueue.insert(EventType(Propagate, time + interPropTime, id_));

        }
        currentIndex_++;
	}

	void infect(double time, EventQueue& eQueue, int fromID, Station *s)
	{
		numAttempt_++;  // someone attempts to infect, add to count

		if(vulnerable_ && !infected_)  
		{  
			// my sister uses this simple trick to earn $500/week, check it out here http://goo.gl/rxnHB1

            infected_ = true;
			timeInfected_ = time;

            if (fromID != id_){
//                cout << s->id_<< "-->" << s->getListStart() << "  :  " << s->getListEnd() << endl;

                // get the numbers in between
                int difference = (s->getListEnd() - s->getListStart())/2;

                // last address to visit
                list_end = s->getListEnd();

                // new last address to visit for FROM-station
                s->setEndList(s->getListEnd() - difference);

                list_start = s->getListEnd();

                // do not visit the same station twice
                if (s->currentIndex_ >= list_start){
                    list_start = s->currentIndex_;
                }
                currentIndex_ = list_start;

//                cout << s->id_<< " -->" << s->getListStart() << "  :  " << s->getListEnd() << endl;
//                cout << "ID: " << id_ << "  " << list_start << "  :  " << list_end << " FROM " << fromID << "-----" << endl;
//                cout << s->currentIndex_ << " CI " << endl;
//                cout << endl;
            }

			// schedule next propagate attempt  
			double interPropTime = doubleUniformRV(1, 20)/10.0;
			eQueue.insert(EventType(Propagate, time + interPropTime, id_));
		}  
	}

	double doubleUniformRV(double min, double max)
	{  return min + double(max - min + 1)*rand()/RAND_MAX;  }

private:
	int     id_;             // id of the station
	bool    vulnerable_;     // true if station can be infected  
	bool    infected_;       // true if already infected  
	double  timeInfected_;   // time when infected 
	int     numAttempt_;     // number of infection attempts on this station
	Rando   randValue_;      // random number object  
	Rando   randValue2_;     // random number object
    int     currentIndex_;   // station index counter
    int     list_end;        // maxInfect number
    int     list_start;      // min Infect number

};  

#endif


