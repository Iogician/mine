#include "main.h"

using namespace pros;

namespace drivetrain {
    #define LF_PORT 5
    #define RF_PORT 10
    #define LB_PORT 12
    #define RB_PORT 19
    extern Motor LF;
    extern Motor RF;
    extern Motor LB;
    extern Motor RB;
    
    void move(int, int, int);
}
