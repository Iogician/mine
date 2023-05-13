#include "main.h"

using namespace pros;

namespace intake {
    #define INTAKE_PORT1 -6
    #define INTAKE_PORT2 -9
    #define OPTICAL_PORT 7
    #define PROXIMITY_THRESHOLD 245

    extern int targetSpeed;
    extern MotorGroup motors;
    extern Optical sensor;
    void run(double percent = 100, int time = 0, bool search = false);
    int proximityCheck(void);
}