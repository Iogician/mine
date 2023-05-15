#include "mine/robot.hpp"

namespace drivetrain {
    Motor LF(LF_PORT, E_MOTOR_GEAR_600);
    Motor RF(-RF_PORT, E_MOTOR_GEAR_600);
    Motor LB(LB_PORT, E_MOTOR_GEAR_600);
    Motor RB(-RB_PORT, E_MOTOR_GEAR_600);
    MotorGroup ALL({LF, RF, LB, RB});
    ADIGyro gyro(8);
    Distance distanceSensor(13);
    ADIUltrasonic ultrasonic(3, 4);

    float maintainedHeading = 0;

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
        if (axis == 'X')  distance = distanceSensor.get() / 10;
        else distance = ultrasonic.get_value();
        return distance;
    }
    void brake(bool mode) {
        if (mode) ALL.set_brake_modes(E_MOTOR_BRAKE_BRAKE);
        else ALL.set_brake_modes(E_MOTOR_BRAKE_COAST);
    }
    void initializeEncoders()
    {
        ALL.set_encoder_units(E_MOTOR_ENCODER_ROTATIONS);
        ALL.tare_position();
    }
    double inInches(double amount, double diameter = WHEEL_DIAMETER) {
        double inches = M_PI * diameter;
        return inches;
    }
    bool inRange(double current, double target, double tolerance) {
        bool yes = (current >= target - tolerance && current <= target + tolerance);
        return yes;
    }
    void drive(char type, double distance, int speed, bool mode) {
        brake();
        if (mode == USE_ENCODER) {
            initializeEncoders();
            double currentPosition = inInches(RF.get_position());
            while (!inRange(currentPosition, distance, LINEAR_TOLERANCE)) {
                turn(maintainedHeading, 35);
                currentPosition = inInches(RF.get_position());
                double power;
                if (currentPosition < distance) {
                    power = ((distance - currentPosition) / distance) * LINEAR_KP;
                }
                else {
                    currentPosition += 0.001; //prevents a divide by 0 error
                    power = -((currentPosition - distance) / currentPosition) * LINEAR_KP;
                }
                if (power > 1) power = 1;
                else if (power < -1) power = -1;
                power *= speed;       
                //debug stuff
                lcd::set_text(1, "Position: " + to_string(currentPosition));
                lcd::set_text(2, "Linear Diff: " + to_string(distance - currentPosition));
                lcd::set_text(3, "Drive Power: " + to_string(power));                             
                move(power * (type == 'X'), power * (type == 'Y'), 0);
                delay(2);
            }
        }
        else if (mode == USE_SENSOR) {
            double currentDistance = getDistance(type);
            while (!inRange(currentDistance, distance, LINEAR_TOLERANCE)) {
                turn(maintainedHeading, 35);
                currentDistance = RF.get_position();
                double power;
                if (currentDistance < distance) {
                    power = ((distance - currentDistance) / distance) * LINEAR_KP;
                }
                else {
                    currentDistance += 0.001; //prevents a divide by 0 error
                    power = -((currentDistance - distance) / currentDistance) * LINEAR_KP;
                }
                if (power > 1) power = 1;
                else if (power < -1) power = -1;
                power *= speed;
                //debug stuff
                lcd::set_text(1, "Position: " + to_string(currentDistance));
                lcd::set_text(2, "Linear Diff: " + to_string(distance - currentDistance));
                lcd::set_text(3, "Drive Power: " + to_string(power));                
                move(power * (type == 'X'), power * (type == 'Y'), 0);
                delay(2);
            }           
        }
    }
    void turn(float heading, int speed) {
        maintainedHeading = heading;
        float power = 0;
        float current = getHeading();

        brake();

        while (!inRange(current, heading, ANGULAR_TOLERANCE)) {
            current = getHeading();
            float adjusted = current;

            if (current > 180 && heading < 180) adjusted -= 360;
            else if (current < 180 && heading > 180) adjusted += 360;

            current = adjusted;            
            float angleDifference = fabs(heading - current);

            float direction = 0;

            if (current < heading) direction = 1;
            else if (current > heading) direction = -1;
            else direction = 0;
            if (angleDifference < ANGULAR_TOLERANCE) power = 0;
            else {
                power = (angleDifference / 360) * ANGULAR_KP;
                power = fabs(power) * direction;
            };
            power *= speed;

            //debug stuff
            lcd::set_text(5, "Heading: " + to_string(getHeading()));
            lcd::set_text(6, "Angular Diff: " + to_string(angleDifference));
            lcd::set_text(7, "Turn Power: " + to_string((int) power));

            move(0, 0, power);

            delay(2);
        }
    }
}