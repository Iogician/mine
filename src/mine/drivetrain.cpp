#include "mine/robot.hpp"
#include "pros/adi.hpp"
#include "pros/motors.h"

namespace drivetrain {
    Motor LF(LF_PORT, E_MOTOR_GEAR_600);
    Motor RF(-RF_PORT, E_MOTOR_GEAR_600);
    Motor LB(LB_PORT, E_MOTOR_GEAR_600);
    Motor RB(-RB_PORT, E_MOTOR_GEAR_600);
    ADIGyro gyro(8);
    Distance distanceSensor(13);
    ADIUltrasonic ultrasonic(3, 4);

    void move(int strafe, int throttle, int turn)
    {
        LF.move(throttle + turn - (strafe * (1 - COG_SHIFT)));
        RF.move(throttle - turn + (strafe * (1 - COG_SHIFT)));
        LB.move(throttle + turn + (strafe * (1 + COG_SHIFT)));
        RB.move(throttle - turn - (strafe * (1 + COG_SHIFT)));
    }
    float getHeading()
    {
        float heading = gyro.get_value();
        heading /= 10;
        if (heading < 0) {
            heading += 360.0;
        }
        return heading;
    }
    int getDistance(char axis)
    {
        int distance = PROS_ERR;
        if (axis == 'X') {
            distance = distanceSensor.get() / 10;
        }
        else {
            distance = ultrasonic.get_value();
        }
        return distance;
    }
}