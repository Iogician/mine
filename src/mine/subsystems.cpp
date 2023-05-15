#include "mine/robot.hpp"

namespace intake {
    Motor motor1(INTAKE_PORT1);
    Motor motor2(-INTAKE_PORT2);
    Motor_Group motors({motor1, motor2});
    Optical sensor(OPTICAL_PORT);

    int targetSpeed = 0;

    void run(double percent, int time, bool search)
    {
        sensor.set_led_pwm(percent);
        targetSpeed = percent;
        percent /= 100;
        motors.set_brake_modes(E_MOTOR_BRAKE_BRAKE);
        motors.move_voltage(MAX_VOLTAGE * percent);

        if (time > 0) {
            delay(time);
            motors.move_voltage(0);
            targetSpeed = 0;
            sensor.set_led_pwm(0);
        }
        else if (search) {
            while (proximityCheck() < PROXIMITY_THRESHOLD) {
                delay(sensor.get_integration_time());
            }
            motors.move_voltage(0);
            targetSpeed = 0;
            sensor.set_led_pwm(0);
        }
    }

    int proximityCheck()
    {
        //sensor.set_integration_time(100);
        int proximity = sensor.get_proximity();

        if (sensor.get_hue() < 80 || sensor.get_hue() > 150) {
            proximity = 0;
        }

        return proximity;
    }
}