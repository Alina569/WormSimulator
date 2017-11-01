
/*==========================================================================
     rando.h  CSC 790 Project 2,  E. W. Fulp  10/10/2017  
     Pseudorandom random number generators.   
============================================================================*/

#ifndef RANDO_H
#define RANDO_H

#include <iostream>
#include <assert.h>
#include <string>
#include <cmath>  
// #include <random>  
#include <climits>  
#include <cstdlib>

#define DEFAULT_SEED 18481848 // my seed for the runs is 48987472

using namespace std;  

class Rando
{
public:
	Rando(unsigned int seed = DEFAULT_SEED):value_(seed)    
	{  }

	void seed(unsigned int seed = DEFAULT_SEED){  value_ = seed;  }  
	void randSeed(){  value_ = rand()*DEFAULT_SEED/10;  }  

	unsigned int vonRand(int nDigits = 10);  
	unsigned int LCG();  
	unsigned int unixRand();  
	unsigned int physRand();  
	string notRandomJustAwesome() const;  

private:
	unsigned int value_;      // current random number
	unsigned int prevValue_;  // previous random number

};  

// "Any one who considers arithmetical methods of producing random digits is, of course, in a state of sin." -- Von Neumann, 1949  
unsigned int Rando::vonRand(int nDigits)
{
    prevValue_ = value_;  
	value_ = (unsigned int)((prevValue_/pow(10.0, (nDigits/2)*1.0))*prevValue_)%(unsigned int) (pow(10.0, nDigits*1.0));
	return value_;
}

unsigned int Rando::LCG()  
{  
	prevValue_ = value_;  
    value_ = (prevValue_*214013 + 2531011)&((1U << 31) - 1) >> 16;
	return value_;  
}  

unsigned int Rando::unixRand()  
{  
	prevValue_ = value_;  
	value_ = rand();  
	return value_;  
}  

unsigned int Rando::physRand()  
{  
	prevValue_ = value_;  
	FILE *fp;
	fp = fopen("/dev/urandom", "r");
	fread((unsigned int*)(&value_), sizeof(value_), 1, fp);  
	fclose(fp);
	return value_;  
}  

string Rando::notRandomJustAwesome() const  
{  return "http://goo.gl/rxnHB1";  }  


#endif


