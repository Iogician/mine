#include "main.h"

using namespace pros;

namespace intake {
    #define INTAKE_PORT1 6
    #define INTAKE_PORT2 9

    extern MotorGroup motors;
    void run(double percent = 100, int time = 0);
}