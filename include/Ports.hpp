#include "api.h"
#include "pros/adi.hpp"

//Extra Motor Ports
extern pros::Motor FlywheelMotor1;
extern pros::Motor FlywheelMotor2;
extern pros::Motor intake1;
extern pros::Motor intake2;
extern pros::Motor roller;
extern pros::Motor indexer;

extern pros::Distance Hopper;
//ADI Ports
extern pros::ADIDigitalOut IndexerActuator;
extern pros::ADIDigitalOut IntakeActuator;
extern pros::ADIDigitalOut Endgame;
extern pros::ADIDigitalOut SageWall;
extern pros::ADIDigitalOut Tongue;