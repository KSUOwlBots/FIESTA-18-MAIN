#include "main.h"
#include "pros/adi.hpp"
#include "pros/motors.h"

//Extra Motor Ports
pros::Motor FlywheelMotor1(13, MOTOR_GEARSET_36, true);
pros::Motor FlywheelMotor2(20, MOTOR_GEARSET_36, false);

pros::Motor intake1(18, MOTOR_GEARSET_6, true);
pros::Motor intake2(15, MOTOR_GEARSET_6, true);
pros::Motor roller(16, MOTOR_GEARSET_36);
pros::Motor indexer(5, MOTOR_GEARSET_6, true);

pros::Distance HopperDistance(17);

//ADI Ports
pros::ADIDigitalOut hopperActuator('G', false);
pros::ADIDigitalOut IntakeActuator('F', true);
pros::ADIDigitalOut Endgame_Chassis('H', false);
pros::ADIDigitalOut Endgame_Lift('E', false);
pros::ADIDigitalOut SageWall('D', false);
pros::ADIDigitalOut Tongue('C');
