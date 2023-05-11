#include "mine/robot.hpp"
#include "pros/motors.h"

namespace drivetrain {
    Motor LF(LF_PORT, E_MOTOR_GEAR_600);
    Motor RF(-RF_PORT, E_MOTOR_GEAR_600);
    Motor LB(LB_PORT, E_MOTOR_GEAR_600);
    Motor RB(-RB_PORT, E_MOTOR_GEAR_600);

    void move(int strafe, int throttle, int turn)
    {
        LF.move(throttle + turn - (strafe * (1 - COG_SHIFT)));
        RF.move(throttle - turn + (strafe * (1 - COG_SHIFT)));
        LB.move(throttle + turn + (strafe * (1 + COG_SHIFT)));
        RB.move(throttle - turn - (strafe * (1 + COG_SHIFT)));
    }
}