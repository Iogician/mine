#include "main.h"

using namespace pros;

namespace drivetrain {
    #define LF_PORT 5
    #define RF_PORT 10
    #define LB_PORT 12
    #define RB_PORT 19
    #define COG_SHIFT 0.105 //a positive double will shift it forward; negative double shifts it backwards
    extern Motor LF;
    extern Motor RF;
    extern Motor LB;
    extern Motor RB;
    
    void move(int, int, int);
}
