#include "mine/robot.hpp"

namespace intake {
    Motor motor1(INTAKE_PORT1);
    Motor motor2(-INTAKE_PORT2);
    Motor_Group motors({motor1, motor2});

    void run(double percent, int time)
    {
        percent /= 100;
        motors.set_brake_modes(E_MOTOR_BRAKE_BRAKE);
        motors.move_voltage(MAX_VOLTAGE * percent);
        if (time > 0) {
            delay(time);
            motors.move_voltage(0);
        }
    }
}