#include "mine/robot.hpp"

using namespace pros;

namespace driver {
    Controller ctrl(E_CONTROLLER_MASTER);

    void analogInputs() {
        int analogLeftX = ctrl.get_analog(E_CONTROLLER_ANALOG_LEFT_X) * (1 - STRAFE_DAMPEN);
        int analogLeftY = ctrl.get_analog(E_CONTROLLER_ANALOG_LEFT_Y) * (1 - THROTTLE_DAMPEN);
        int analogRightX = ctrl.get_analog(E_CONTROLLER_ANALOG_RIGHT_X) * (1 - TURN_DAMPEN);

        drivetrain::move(analogLeftX, analogLeftY, analogRightX);
    }
    void digitalInputs() {
        bool R1 = ctrl.get_digital(E_CONTROLLER_DIGITAL_R1);
        bool R2 = ctrl.get_digital(E_CONTROLLER_DIGITAL_R2);

        if (R1) intake::run();
        else if (R2) intake::run(-100);
        else intake::run(0);
    }  
}

namespace programming {
    int routine = 1;
}