#include "main.h"
#include "mine/robot.hpp"

using namespace pros;

void initialize() {
	lcd::initialize();
	lcd::set_background_color(227,28,121);
	lcd::set_text_color(0,0,0);
	lcd::clear();
	drivetrain::gyro.reset();
}

void disabled() {}

void competition_initialize() {}

using namespace programming;
using namespace driver;

void autonomous() {
	runRoutine();
}

void opcontrol() {

	drivetrain::brake(false);

	while (true) {
		analogInputs();
		digitalInputs();
		feedback();

		delay(2);
	}
}
