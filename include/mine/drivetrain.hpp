#include "main.h"
#include "pros/adi.hpp"
#include "pros/distance.hpp"
#include "pros/motors.hpp"

using namespace pros;

namespace drivetrain {
    //initialization
    #define LF_PORT 5
    #define RF_PORT 10
    #define LB_PORT 12
    #define RB_PORT 19
    //scalars
    #define LINEAR_KP 4
    #define ANGULAR_KP 4
    #define COG_SHIFT 0.105 //a positive double will shift it forward; negative double shifts it backwards
    //odometry
    #define WHEEL_DIAMETER 2.00
    #define LINEAR_TOLERANCE 1.0
    #define ANGULAR_TOLERANCE 0.5
    //function constants
    #define USE_ENCODER false
    #define USE_SENSOR true  
    #define STRAFE 'X'  
    #define STRAIGHT 'Y'

    extern Motor LF;
    extern Motor RF;
    extern Motor LB;
    extern Motor RB;
    extern ADIGyro gyro;
    extern Distance distance;
    extern ADIUltrasonic ultrasonic;

    extern float maintainedHeading;

    void move(int, int, int);
    float getHeading(void);
    int getDistance(char);
    void drive(char, double, int speed = 127, bool mode = USE_ENCODER);
    void turn(float, int speed = 127);
}
