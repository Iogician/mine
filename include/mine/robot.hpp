#pragma once
#include "drivetrain.hpp"
#include "subsystems.hpp"

using namespace pros;
using namespace std;

#define MAX_VOLTAGE 12000 //in millivolts
#define MAX_POWER 127 //pros units
#define REFRESH_RATE 50 //in milliseconds

namespace driver {
    #define STRAFE_DAMPEN 0
    #define THROTTLE_DAMPEN 0
    #define TURN_DAMPEN 0.1
    
    extern Controller ctrl;
    extern int refresh;

    void analogInputs();
    void digitalInputs();
    void feedback();
}

namespace programming {
    extern int routine;
    void runRoutine();
}