#pragma once
#include "drivetrain.hpp"
#include "subsystems.hpp"

using namespace pros;

#define MAX_VOLTAGE 12000 //in millivolts

namespace driver {
    #define STRAFE_DAMPEN 0
    #define THROTTLE_DAMPEN 0
    #define TURN_DAMPEN 0.1
    extern Controller ctrl;

    void analogInputs();
    void digitalInputs();
}

namespace programming {
    extern int routine;
    void runRoutine();
}