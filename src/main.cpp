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

void autonomous() {}

using namespace driver;

void opcontrol() {

	while (true) {
		analogInputs();
		digitalInputs();
		feedback();

		delay(2);
	}
}
