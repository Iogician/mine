#include "main.h"
#include "mine/robot.hpp"

using namespace pros;

void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_background_color(227,28,121);
	pros::lcd::clear();
}

void disabled() {}

void competition_initialize() {}

void autonomous() {}

using namespace driver;

void opcontrol() {

	while (true) {
		analogInputs();
		digitalInputs();

		delay(2);
	}
}
