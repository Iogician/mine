#include "mine/robot.hpp"
#include "pros/llemu.hpp"
#include <string>

using namespace std;
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

        if (R1) intake::run(50);
        else if (R2) intake::run(-100);
        else intake::run(0);
    }  
    int refresh = 0;
    void feedback() {
        refresh += 2;

        int ballProximity = intake::proximityCheck();
        if (intake::targetSpeed > 0 && ballProximity >= PROXIMITY_THRESHOLD) ctrl.rumble(".");
        
        if (refresh >= REFRESH_RATE) {
            refresh = 0;
            float heading = drivetrain::getHeading();
            int X = drivetrain::getDistance('X');
            int Y = drivetrain::getDistance('Y');
            int hue = intake::sensor.get_hue();
            int saturation = intake::sensor.get_saturation();
            int brightness = intake::sensor.get_brightness();

            lcd::set_text(1, "Heading: " + to_string(heading));
            lcd::set_text(2, "Coordinates: (" + to_string(X) + ", " + to_string(Y) + ")");
            lcd::set_text(3, "Proximity: " + to_string(ballProximity));
            lcd::set_text(4, "Object HSV: (" + to_string(hue) + ", " + to_string(saturation) + ", " + to_string(brightness) + ")");
        }
    }
}

namespace programming {
    int routine = 1;

    void autonomous1() {
        driver::ctrl.rumble(".");
        drivetrain::turn(90, 75);
    }
    void autonomous2() {
        driver::ctrl.rumble("..");
    }
    void autonomous3() {
        driver::ctrl.rumble("...");
    }
    void runRoutine() {
        if (routine == 1) autonomous1();
        else if (routine == 2) autonomous2();
        else if (routine == 3) autonomous3();
    }
}