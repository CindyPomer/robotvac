#ifndef _STIMULATION_H_
#define _STIMULATION_H_

// Includes
#include "Sensor.h"
#include "KeyboardAlgo.h"
#include "House.h"
#include "Tracker.h"

//Class forward Decleraion
class KeyboardAlgo;
class House;

class Stimulation{

public:
	// Public Functions
	Direction Step();


private:

	// Private Data Members
	Direction lastDir;
	KeyboardAlgo keyAlgo;
	House house;

};


#endif