#include "Endgame.hpp"
#include "Indexer.hpp"
#include "Intakes.hpp"
#include "autons.hpp"
#include "main.h"
#include "pros/rtos.h"
#include "pros/rtos.hpp"
#include "subsystems/Launcher.hpp"

/////
// For instalattion, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/
/////

const int DRIVE_SPEED =
    90; // This is 110/127 (around 87% of max speed).  We don't suggest making
        // this 127. If this is 127 and the robot tries to heading correct, it's
        // only correcting by making one side slower.  When this is 87%, it's
        // correcting by making one side faster and one side slower, giving
        // better heading correction.
const int TURN_SPEED = 90;
const int SWING_SPEED = 90;

///
// Constants
///

// It's best practice to tune constants when the robot is empty and with heavier
// game objects, or with lifts up vs down. If the objects are light or the cog
// doesn't change much, then there isn't a concern here.

void default_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void one_mogo_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void two_mogo_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void exit_condition_defaults() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}

void modified_exit_condition() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}

// START OF Fiesta AUTOS

















/**
  __  __       _       _          _         _                
 |  \/  | __ _| |_ ___| |__      / \  _   _| |_ ___  _ __  _ 
 | |\/| |/ _` | __/ __| '_ \    / _ \| | | | __/ _ \| '_ \(_)
 | |  | | (_| | || (__| | | |  / ___ \ |_| | || (_) | | | |_ 
 |_|  |_|\__,_|\__\___|_| |_| /_/   \_\__,_|\__\___/|_| |_(_)
                                                             
*/
void Frenzy_Rush_Mid()
{
  // Setup
  launcherSubsystem.setTarget(62, 62);
  Tongue.set_value(false);
  hopperActuator.set_value(false);

  //do the roller
  chassis.set_drive_pid(-6, 20);
  chassis.wait_drive();
  Roller_Auto(90);
  pros::delay(200);

  //Go for single disc on line
  Intake_Auto(600);
  chassis.set_swing_pid(RIGHT_SWING, -45, 50);
  chassis.wait_drive();

  chassis.set_drive_pid(5, 75);
  chassis.wait_drive();

  //Aim at goal and fire 3
  chassis.set_drive_pid(-5, 75);
  chassis.wait_drive();

  pros::delay(500);

  chassis.set_turn_pid(-4, 75);
  chassis.wait_drive();

  chassis.set_drive_pid(6, 30);
  chassis.wait_drive();

  Intake_Auto(-600);
  indexer.move_velocity(0);
  hopperActuator.set_value(true);

  pros::delay(500);
  launcherSubsystem.shootEmpty(20, 7);
  pros::delay(250);
  hopperActuator.set_value(false);

  //Get triple stack on midline
  Intake_Auto(600);

  chassis.set_drive_pid(-6, 30);
  chassis.wait_drive();

  chassis.set_turn_pid(55, 75);
  chassis.wait_drive();

  chassis.set_drive_pid(9, 75);
  chassis.wait_drive();

  Actuate_Auto(true);

  chassis.set_swing_pid(RIGHT_SWING, -45, 50);
  chassis.wait_drive();

  Actuate_Auto(false);
  pros::delay(500);

  launcherSubsystem.setTarget(59,59);

  chassis.set_drive_pid(-5, 30);
  chassis.wait_drive();

  chassis.set_drive_pid(5, 30);
  chassis.wait_drive();

  //Aim at goal and fire
  chassis.set_drive_pid(-6, 75);
  chassis.wait_drive();

  chassis.set_turn_pid(-13, 50);
  chassis.wait_drive();

  chassis.set_drive_pid(8, 30);
  chassis.wait_drive();

  pros::delay(500);

  Intake_Auto(-600);
  indexer.move_velocity(0);
  hopperActuator.set_value(true);

  pros::delay(500);
  launcherSubsystem.shootEmpty(20, 7);
  pros::delay(250);
  hopperActuator.set_value(false);

  //Go for triple stack

  chassis.set_drive_pid(-10, 30);
  chassis.wait_drive();

  Intake_Auto(600);

  chassis.set_turn_pid(45, 75);
  chassis.wait_drive();

  Actuate_Auto(true);

  chassis.set_drive_pid(14, 50);
  chassis.wait_drive();

  chassis.set_drive_pid(-1, 30);
  chassis.wait_drive();

  Actuate_Auto(false);
  pros::delay(500);

  launcherSubsystem.setTarget(57,57);

  chassis.set_drive_pid(-6, 50);
  chassis.wait_drive();

  chassis.set_drive_pid(24, 30);
  chassis.wait_drive();

  //Turn to goal and fire

  chassis.set_turn_pid(-29, 75);
  chassis.wait_drive();

  chassis.set_drive_pid(6, 50);
  chassis.wait_drive();

  pros::delay(500);

  Intake_Auto(-600);
  indexer.move_velocity(0);
  hopperActuator.set_value(true);

  pros::delay(500);
  launcherSubsystem.shootEmpty(20, 7);
  pros::delay(250);
  hopperActuator.set_value(false);

  //Get 3 discs on barrier

  chassis.set_turn_pid(-27.5, 30);
  chassis.wait_drive();

  chassis.set_drive_pid(-40, 50, true);
  chassis.wait_drive();

  chassis.set_turn_pid(10, 75);
  chassis.wait_drive();

  Intake_Auto(600);

  chassis.set_drive_pid(36, 30);
  chassis.wait_drive();

  //Aim at goal and fire

  pros::delay(500);

  chassis.set_drive_pid(-36, 75, true);
  chassis.wait_drive();

  chassis.set_turn_pid(-29, 75);
  chassis.wait_drive();

  chassis.set_drive_pid(40, 75, true);
  chassis.wait_drive();

  //Fire at goal

  Intake_Auto(-600);
  indexer.move_velocity(0);
  hopperActuator.set_value(true);

  pros::delay(500);
  launcherSubsystem.shootEmpty(20, 7);
  pros::delay(250);
  hopperActuator.set_value(false);

}









/**
  ____  _    _ _ _          _         _                
 / ___|| | _(_) | |___     / \  _   _| |_ ___  _ __  _ 
 \___ \| |/ / | | / __|   / _ \| | | | __/ _ \| '_ \(_)
  ___) |   <| | | \__ \  / ___ \ |_| | || (_) | | | |_ 
 |____/|_|\_\_|_|_|___/ /_/   \_\__,_|\__\___/|_| |_(_)
                                                       
*/
void Default2()
{
  launcherSubsystem.setTarget(58, 58);
  hopperActuator.set_value(true);
  pros::delay(1000);
  launcherSubsystem.shootEmpty(1, 5);
}

void Default()
{
  //Set up functions
  launcherSubsystem.setTarget(56, 56);
  Tongue.set_value(false);
  hopperActuator.set_value(false);

  //Turn roller

  chassis.set_drive_pid(-7, 20);

  pros::delay(250);
  Roller_Auto(180);
  pros::delay(250);

  chassis.wait_drive();

  //Go for single disc on line

  Intake_Auto(600);
  chassis.set_drive_pid(5, 50);
  chassis.wait_drive();

  chassis.set_turn_pid(-45, 75);
  chassis.wait_drive();

  chassis.set_drive_pid(18, 50);
  chassis.wait_drive();

  chassis.set_turn_pid(90, 75);
  chassis.wait_drive();

  //Spin second roller

  chassis.set_drive_pid(-16, 30);
  chassis.wait_drive();

  Roller_Auto(180);
  pros::delay(500);

  //Aim at far goal

  chassis.set_drive_pid(14, 75);
  chassis.wait_drive();

  chassis.set_turn_pid(0, 75);
  chassis.wait_drive();

  //Fire at goal

  Intake_Auto(-600);
  indexer.move_velocity(0);
  hopperActuator.set_value(true);

  pros::delay(500);
  launcherSubsystem.shootEmpty(10, 10);
  pros::delay(250);
  hopperActuator.set_value(false);

  //Go for triple stack on line

  Intake_Auto(600);

  chassis.set_drive_pid(-5, 75);
  chassis.wait_drive();

  chassis.set_turn_pid(45, 75);
  chassis.wait_drive();

  Actuate_Auto(true);

  chassis.set_drive_pid(15, 50);
  chassis.wait_drive();

  chassis.set_drive_pid(-2, 20);
  chassis.wait_drive();

  Actuate_Auto(false);
  pros::delay(500);

  chassis.set_drive_pid(-6, 30);
  chassis.wait_drive();

  chassis.set_drive_pid(18, 30);
  chassis.wait_drive();

  //Aim at goal and fire

  launcherSubsystem.setTarget(55, 55);

  chassis.set_drive_pid(-5, 50);
  chassis.wait_drive();

  chassis.set_turn_pid(98, 75);
  chassis.wait_drive();

  Intake_Auto(-600);
  indexer.move_velocity(0);
  hopperActuator.set_value(true);
  pros::delay(250);
  launcherSubsystem.shootEmpty(10, 10);
  pros::delay(250);
  hopperActuator.set_value(false);

  //Pick up next triple stack
  
  launcherSubsystem.setTarget(43, 43);

  Intake_Auto(600);

  chassis.set_turn_pid(85, 50);
  chassis.wait_drive();

  chassis.set_drive_pid(16, 50);
  chassis.wait_drive();

  chassis.set_drive_pid(18, 30);
  chassis.wait_drive();

  pros::delay(500);

  //Aim at goal and fire

  chassis.set_turn_pid(106, 75);
  chassis.wait_drive();

  Intake_Auto(-600);
  indexer.move_velocity(0);
  hopperActuator.set_value(true);

  pros::delay(250);
  launcherSubsystem.shootEmpty(1, 5);
  pros::delay(250);
  hopperActuator.set_value(false);

  

  //Go for 3 line

  launcherSubsystem.setTarget(49, 49);

  Intake_Auto(600);

  chassis.set_drive_pid(-7, 30);
  chassis.wait_drive();

  chassis.set_turn_pid(45, 75);
  chassis.wait_drive();

  chassis.set_drive_pid(88, 75, true);
  chassis.wait_drive();

  //Aim at goal and fire

  chassis.set_turn_pid(175, 75);
  chassis.wait_drive();

  Intake_Auto(-600);
  indexer.move_velocity(0);
  hopperActuator.set_value(true);

  pros::delay(250);
  launcherSubsystem.shootEmpty(10, 10);
  pros::delay(250);
  hopperActuator.set_value(false);

  

  //Go for next triple stack

  Intake_Auto(600);

  chassis.set_drive_pid(-8, 75);
  chassis.wait_drive();

  chassis.set_turn_pid(270, 75);
  chassis.wait_drive();

  Actuate_Auto(true);

  chassis.set_drive_pid(18, 30);
  chassis.wait_drive();

  chassis.set_drive_pid(-2, 30);
  chassis.wait_drive();

  Actuate_Auto(false);
  pros::delay(150);

  chassis.set_drive_pid(-5, 30);
  chassis.wait_drive();

  chassis.set_drive_pid(11, 15);
  chassis.wait_drive();

  chassis.set_turn_pid(280, 75);
  chassis.wait_drive();

  pros::delay(500);
  //Fire at goal

  Intake_Auto(-600);
  indexer.move_velocity(0);
  hopperActuator.set_value(true);

  pros::delay(250);
  launcherSubsystem.shootEmpty(10, 10);
  hopperActuator.set_value(false);

  //Go for second triple stack

  launcherSubsystem.setTarget(40, 40);
  Intake_Auto(600);

  chassis.set_turn_pid(265, 75);
  chassis.wait_drive();

  chassis.set_drive_pid(12, 30);
  chassis.wait_drive();

  chassis.set_drive_pid(-2, 30);
  chassis.wait_drive();
 
  pros::delay(500);

  chassis.set_drive_pid(18, 30);
  chassis.wait_drive();

  //Aim at goal and fire

  chassis.set_turn_pid(281, 75);
  chassis.wait_drive();

  Intake_Auto(-600);
  indexer.move_velocity(0);
  hopperActuator.set_value(true);

  pros::delay(250);
  launcherSubsystem.shootEmpty(10, 10);
  hopperActuator.set_value(false);
  pros::delay(250);

  //Go for midline discs

  launcherSubsystem.setTarget(57, 57);

  Intake_Auto(600);

  chassis.set_turn_pid(135, 50);
  chassis.wait_drive();
  
  chassis.set_drive_pid(24, 50);
  chassis.wait_drive();

  chassis.set_turn_pid(45, 50);
  chassis.wait_drive();

  chassis.set_drive_pid(48, 75, true);
  chassis.wait_drive();

  chassis.set_drive_pid(-6, 50);
  chassis.wait_drive();

  //Aim at goal and fire

  chassis.set_turn_pid(180, 75);
  chassis.wait_drive();

  Intake_Auto(-600);
  indexer.move_velocity(0);
  hopperActuator.set_value(true);

  pros::delay(250);
  launcherSubsystem.shootEmpty(10, 10);
  hopperActuator.set_value(false);
  pros::delay(250);

  //Turn for rushing midline

  Intake_Auto(600);

  chassis.set_turn_pid(225, 50);
  chassis.wait_drive();

  chassis.set_drive_pid(150, 100, true);
  chassis.wait_drive();

  chassis.set_drive_pid(-6, 30);
  chassis.wait_drive();

  //Turn to goal and fire

  chassis.set_turn_pid(90, 75);
  chassis.wait_drive();

  Intake_Auto(-600);
  indexer.move_velocity(0);
  hopperActuator.set_value(true);

  pros::delay(250);
  launcherSubsystem.shootEmpty(10, 10);
  hopperActuator.set_value(false);
  pros::delay(250);

  //Turn for endgame

  chassis.set_turn_pid(45, 75);
  chassis.wait_drive();
  }

void swing_example() {
  // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
  // The second parameter is target degrees
  // The third parameter is speed of the moving side of the drive

  chassis.set_swing_pid(ez::LEFT_SWING, 45, SWING_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_until(12);

  chassis.set_swing_pid(ez::RIGHT_SWING, 0, SWING_SPEED);
  chassis.wait_drive();
}

///
// Auto that tests everything
///
void combining_movements() {
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_swing_pid(ez::RIGHT_SWING, -45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_drive();
}

///
// Interference example
///
void tug(int attempts) {
  for (int i = 0; i < attempts - 1; i++) {
    // Attempt to drive backwards
    printf("i - %i", i);
    chassis.set_drive_pid(-12, 127);
    chassis.wait_drive();

    // If failsafed...
    if (chassis.interfered) {
      chassis.reset_drive_sensor();
      chassis.set_drive_pid(-2, 20);
      pros::delay(1000);
    }
    // If robot successfully drove back, return
    else {
      return;
    }
  }
}

// If there is no interference, robot will drive forward and turn 90 degrees.
// If interfered, robot will drive forward and then attempt to drive backwards.
void interfered_example() {
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  if (chassis.interfered) {
    tug(3);
    return;
  }

  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();
}

// . . .
// Make your own autonomous functions here!
// . . .