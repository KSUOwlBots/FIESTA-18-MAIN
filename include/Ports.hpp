#include "api.h"
#include "pros/adi.hpp"

//Extra Motor Ports
extern pros::Motor FlywheelMotor1;
extern pros::Motor FlywheelMotor2;
extern pros::Motor intake1;
extern pros::Motor intake2;
extern pros::Motor roller;

//ADI Ports
extern pros::ADIDigitalOut IndexerActuator;
extern pros::ADIAnalogIn limit_switch;
extern pros::ADIDigitalOut Endgame;