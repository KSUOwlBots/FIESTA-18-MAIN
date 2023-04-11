#include "main.h"
#include "pros/adi.hpp"
#include "pros/motors.h"

//Extra Motor Ports
pros::Motor FlywheelMotor1(13, MOTOR_GEARSET_36);
pros::Motor FlywheelMotor2(19, MOTOR_GEARSET_36);

pros::Motor intake1(18, MOTOR_GEARSET_6, true);
pros::Motor intake2(15, MOTOR_GEARSET_6, true);
pros::Motor roller(15, MOTOR_GEARSET_36);
pros::Motor indexer(5, MOTOR_GEARSET_36, true);

pros::Distance Hopper(16);

//ADI Ports
pros::ADIDigitalOut hopperActuator('G', false);
pros::ADIDigitalOut IntakeActuator('F');
pros::ADIDigitalOut Endgame('A', false);
pros::ADIDigitalOut SageWall('B', false);
pros::ADIDigitalOut Tongue('C');
