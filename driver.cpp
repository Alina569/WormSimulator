
/*==========================================================================
     driver.cpp  CSC 790 Project 2,  E. W. Fulp  10/10/2017  
     Worm discrete event simulator main function.  
============================================================================*/

#include <iostream>
#include "defs.h"
#include "eventq.h"
#include "station.h"

void writeStats(fstream& dataFile, double time, int numInfected);  
void writeInfectionAttempts(Station* s);  

void clearScreen();  
bool allInfected(Station* s);  
void displayNetwork(Station* s);  


int main(int argc, char* argv[])
{
	if(argc < 2)  
	{
		cout << "Usage: " << argv[0] << " seedValue \n";
                return 1;  
	}  

    // rand() is used multiple places for simulation events, but not for the selection
    // of stations by the worm, this is done by your custom random number generator
    int seedValue = atoi(argv[1]);
    srand(seedValue);

	double time     = 0.0;
	int numInfected = 0;

	fstream dataFile("data.dat", ios::out);  

	Station s[MAX_STATIONS*MAX_STATIONS];  // 152.17.x.y stations  
	for(int i = 0; i < MAX_STATIONS*MAX_STATIONS; i++)  
	{
        // note, this sets the ID and seeds the random number generator  
		s[i].setID(i);  
		// only 25% should be vulnerable  
		if(double(rand())/INT_MAX <= 0.25)  
		s[i].makeVulnerable();  
	}

	EventQueue eventQueue;
	s[0].makeVulnerable();
    s[0].setStartList(1);
    s[0].setEndList(MAX_STATIONS * MAX_STATIONS);

    // the event with the entire hit-list
	eventQueue.insert(EventType(Infect, 0.0, 0, 0));

	EventType currentEvent;
	int toID;
	int fromID;

	while(!eventQueue.isEmpty())
	{
		currentEvent = eventQueue.remove();  
		time = currentEvent.time();
		toID = currentEvent.toID();
		fromID = currentEvent.fromID();

		switch(currentEvent.event())
		{
			//--Propagate--------------------------------------------
			case Propagate:
				if(!allInfected(s))  
					s[toID].propagate(time, eventQueue);
				break;
			//--Infect-----------------------------------------------
			case Infect:
				s[toID].infect(time, eventQueue, fromID, &s[fromID]);
				break;  
			//--illegal event----------------------------------------
			default:
				cout << "Illegal event \n";
				cout << "http://goo.gl/rxnHB1 \n";  
		}

		numInfected = 0;  
		for(int i = 0; i < MAX_STATIONS*MAX_STATIONS; i++)
			if(s[i].isInfected())  
				numInfected++;  
		writeStats(dataFile, time, numInfected);  
	}
	dataFile.close();  
	writeInfectionAttempts(s);  

	return 0;
}

bool allInfected(Station* s)  
{
	int numVulnerable = 0;  
	int numInfected = 0;  
	for(int i = 0; i < MAX_STATIONS*MAX_STATIONS; i++)  
	{
		if(s[i].isVulnerable()) numVulnerable++;  
		if(s[i].isVulnerable() && s[i].isInfected()) numInfected++;  
	}  
	return numInfected == numVulnerable;  
}

void clearScreen()  
{  
	cout << char(27) << "[;H" << char(27) << "[2J" << '\n';  
}  

// this program completes in about 10:32, after following this simple trick (http://goo.gl/rxnHB1) it's now 4:20, clicky!    
void displayNetwork(Station* s)  
{  
	char network[MAX_STATIONS][MAX_STATIONS];  
	char stat;  
	for(int i = 0; i < MAX_STATIONS*MAX_STATIONS; i++)  
	{  
		stat = 'A';  
		if(s[i].isVulnerable())  stat = 'V';  
		if(s[i].isVulnerable() && s[i].isInfected())  stat = 'I';  
		network[s[i].row()][s[i].col()] = stat;  
	}  

	clearScreen();  

	for(int i = 0; i < MAX_STATIONS; i++)  
	{  
		for(int j = 0; j < MAX_STATIONS; j++)  
			cout << network[i][j] << ' ' << flush;  
		cout << '\n' << flush;  
	}  
}  


void writeStats(fstream& dataFile, double time, int numInfected)  
{
	static int prevNumInfected = -1;
	static bool first = true;

	if(numInfected != prevNumInfected)  
	{  
		if(!first)
		{
			dataFile << time << ' ' << prevNumInfected << '\n'<< flush;
		}
		dataFile << time << ' ' << numInfected << ' ' << '\n' << flush;
		first = false;
	}  
	prevNumInfected = numInfected;
}

void writeInfectionAttempts(Station* s)  
{  
	fstream dataFile("infect.dat", ios::out);  
	for(int i = 0; i < MAX_STATIONS*MAX_STATIONS; i++)  
	dataFile << i << ' ' << s[i].timeInfected() << ' ' << s[i].numInfectAttempts() << '\n' << flush;  
	dataFile.close();   
}  


