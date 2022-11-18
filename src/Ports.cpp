#include "main.h"
#include "pros/adi.hpp"
#include "pros/motors.h"

//Extra Motor Ports
pros::Motor FlywheelMotor1(12, MOTOR_GEARSET_36);
pros::Motor FlywheelMotor2(11, MOTOR_GEARSET_36);

pros::Motor intake1(19, MOTOR_GEARSET_6);
pros::Motor intake2(20, MOTOR_GEARSET_6);
pros::Motor roller(11, MOTOR_GEARSET_36);

//ADI Ports
pros::ADIDigitalOut IndexerActuator('H');
pros::ADIAnalogIn limit_switch('B');
pros::ADIDigitalOut Endgame('C', true);
