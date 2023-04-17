#include "Endgame.hpp"
#include "Flywheel.hpp"
#include "Indexer.hpp"
#include "Intakes.hpp"
#include "autons.hpp"
#include "main.h"
#include "pros/rtos.h"
#include "pros/rtos.hpp"

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

void Frenzy_Rush_Mid()
{
  // Setup
  pros::delay(300);
  pros::Task IndexerTask(FlywheelAutoCtrl);
  newFlywheelVelocity(70);
  Actuate_Auto(true);
  Tongue.set_value(true);
  hopperActuator.set_value(true);

  //do the roller
  Roller_Auto(90);
  pros::delay(200);
  chassis.set_turn_pid(-9, 70);
  chassis.wait_drive();
  chassis.set_drive_pid(17, 75, true);
  pros::delay(750);

  // Shoot 2 preloads
  IndexAutoCtrl(1);
  pros::delay(750);
  IndexAutoCtrl(1);
  pros::delay(750);
  
  // Collect 1st 3-stack
  hopperActuator.set_value(false);
  Intake_Auto(600);
  Actuate_Auto(false);
  pros::delay(300);
  chassis.set_drive_pid(-6, 30);
  chassis.wait_drive();
  chassis.set_drive_pid(6, 30);
  chassis.wait_drive();

  pros::delay(1000);
  Intake_Auto(-600);
  Actuate_Auto(true);
  indexer.move_velocity(0);
  hopperActuator.set_value(true);

  // Shoot 3 shots
  pros::delay(250);
  IndexAutoCtrl(1);
  pros::delay(800);
  IndexAutoCtrl(1);
  pros::delay(800);
  IndexAutoCtrl(2);
  pros::delay(800);
  hopperActuator.set_value(false);

  // go to 2nd 3 stack
  chassis.set_drive_pid(-13, 75, true);
  chassis.wait_drive();
  chassis.set_turn_pid(45, 70);
  chassis.wait_drive();
  Intake_Auto(600);
  Actuate_Auto(true);
  chassis.set_drive_pid(22, 75);
  chassis.wait_drive();
  pros::delay(250);

  // Get 2nd 3-stack
  Actuate_Auto(false);
  Intake_Auto(600);
  chassis.set_drive_pid(-6, 30);
  chassis.wait_drive();
  chassis.set_drive_pid(6, 30);
  chassis.wait_drive();
  pros::delay(250);


  // Turn to goal and get in shooting position
  Intake_Auto(-600);
  chassis.set_turn_pid(-20, 70);
  chassis.wait_drive();
  indexer.move_velocity(0);
  hopperActuator.set_value(true);
  pros::delay(800);

  // Shoot 3 shots
  IndexAutoCtrl(1);
  pros::delay(850);
  IndexAutoCtrl(1);
  pros::delay(850);
  IndexAutoCtrl(2);
  pros::delay(800);

  //drive back to low goal
  hopperActuator.set_value(false);
  chassis.set_drive_pid(-18, 75, true);
  chassis.wait_drive();
  chassis.set_turn_pid(90, 70);
  chassis.wait_drive();
  Intake_Auto(-600);  //outtake in case opponents missed disks are on field
  chassis.set_drive_pid(28, 75);
  chassis.wait_drive();
  pros::delay(250);

  //intake 3 by low goal
  chassis.set_turn_pid(0,70);
  chassis.wait_drive();
  pros::delay(250);
  Intake_Auto(600);
  chassis.set_drive_pid(35,40,true);
  chassis.wait_drive();
  pros::delay(250);
  indexer.move_velocity(0);
  newFlywheelVelocity(90);

  

  //drive back to low goal entrance
  //intake 3 by low goal
  chassis.set_drive_pid(-35,75, true);
  chassis.wait_drive();
  chassis.set_turn_pid(-33,70);
  chassis.wait_drive();
  pros::delay(500);
  hopperActuator.set_value(true);
  pros::delay(250);
  // Shoot 3 shots
  IndexAutoCtrl(1);
  pros::delay(850);
  IndexAutoCtrl(1);
  pros::delay(850);
  IndexAutoCtrl(2);
  pros::delay(800);
}

/*
**     / ____|  | |      (_)  | |  | | 
**    | (___    | |  __   __  | |  | |   ____
**     \___ \   | |/ /   | |  | |  | |  / __|
**     ____) |  |   <    | |  | |  | |  \__ \
**    |_____/   |_|\_\   |_|  |_|  |_|  |___/
*/

void Default()
{
  //Set up functions
  pros::Task IndexerTask(FlywheelAutoCtrl);
  newFlywheelVelocity(73);
  Tongue.set_value(true);
  hopperActuator.set_value(false);

  //Turn roller

  chassis.set_drive_pid(-5, 20);

  pros::delay(150);
  Roller_Auto(180);
  pros::delay(250);

  chassis.wait_drive();

  //Go for single disc on line

  Intake_Auto(600);
  chassis.set_drive_pid(5, 50);
  chassis.wait_drive();

  chassis.set_turn_pid(-45, 75);
  chassis.wait_drive();

  chassis.set_drive_pid(20, 50);
  chassis.wait_drive();

  chassis.set_turn_pid(90, 75);
  chassis.wait_drive();

  //Spin second roller

  chassis.set_drive_pid(-12, 50);
  chassis.wait_drive();

  Roller_Auto(180);
  pros::delay(500);

  //Aim at far goal

  chassis.set_drive_pid(12, 75);
  chassis.wait_drive();

  chassis.set_turn_pid(0, 75);
  chassis.wait_drive();

  //Fire at goal

  pros::delay(250);
  Intake_Auto(-600);
  Actuate_Auto(true);
  indexer.move_velocity(0);
  hopperActuator.set_value(true);

  pros::delay(250);
  IndexAutoCtrl(1);
  pros::delay(1000);
  IndexAutoCtrl(1);
  pros::delay(1000);
  IndexAutoCtrl(2);
  pros::delay(1000);
  hopperActuator.set_value(false);

  //Go for triple stack on line

  Intake_Auto(600);

  chassis.set_drive_pid(-8, 75);
  chassis.wait_drive();

  chassis.set_turn_pid(45, 75);
  chassis.wait_drive();

  chassis.set_drive_pid(15, 75);
  chassis.wait_drive();

  chassis.set_drive_pid(15, 30);
  chassis.wait_drive();

  //Aim at goal and fire

  newFlywheelVelocity(68);

  chassis.set_drive_pid(-8, 50);
  chassis.wait_drive();

  chassis.set_turn_pid(98, 75);
  chassis.wait_drive();

  pros::delay(250);
  Intake_Auto(-600);
  Actuate_Auto(true);
  indexer.move_velocity(0);
  hopperActuator.set_value(true);

 pros::delay(250);
  IndexAutoCtrl(1);
  pros::delay(1000);
  IndexAutoCtrl(1);
  pros::delay(1000);
  IndexAutoCtrl(2);
  pros::delay(250);
  hopperActuator.set_value(false);

  //Pick up next triple stack
  
  newFlywheelVelocity(60);

  Intake_Auto(600);

  chassis.set_turn_pid(80, 50);
  chassis.wait_drive();

  chassis.set_drive_pid(17, 75);
  chassis.wait_drive();

  chassis.set_drive_pid(17, 30);
  chassis.wait_drive();

  //Aim at goal and fire

  chassis.set_turn_pid(106, 75);
  chassis.wait_drive();

  pros::delay(250);
  Intake_Auto(-600);
  Actuate_Auto(true);
  indexer.move_velocity(0);
  hopperActuator.set_value(true);

  pros::delay(250);
  IndexAutoCtrl(3);
  pros::delay(250);
  hopperActuator.set_value(false);

  //Go for 3 line

  newFlywheelVelocity(68);

  Intake_Auto(600);

  chassis.set_drive_pid(-4, 30);
  chassis.wait_drive();

  chassis.set_turn_pid(45, 75);
  chassis.wait_drive();

  chassis.set_drive_pid(86, 50);
  chassis.wait_drive();

  //Aim at goal and fire

  chassis.set_turn_pid(178, 75);
  chassis.wait_drive();

  pros::delay(250);
  Intake_Auto(-600);
  Actuate_Auto(true);
  indexer.move_velocity(0);
  hopperActuator.set_value(true);

  pros::delay(250);
  IndexAutoCtrl(1);
  pros::delay(1000);
  IndexAutoCtrl(1);
  pros::delay(1000);
  IndexAutoCtrl(2);
  pros::delay(250);
  hopperActuator.set_value(false);

  //Go for next triple stack

  chassis.set_turn_pid(225, 75);
  chassis.wait_drive();

  chassis.set_drive_pid(6, 50);
  chassis.wait_drive();

  Intake_Auto(600);

  chassis.set_turn_pid(-45, 75);
  chassis.wait_drive();

  chassis.set_drive_pid(12, 75);
  chassis.wait_drive();

  chassis.set_drive_pid(18, 30);
  chassis.wait_drive();

  pros::delay(250);

  //Aim at goal and fire

  chassis.set_turn_pid(-80, 75);
  chassis.wait_drive();

   pros::delay(250);
  Intake_Auto(-600);
  Actuate_Auto(true);
  indexer.move_velocity(0);
  hopperActuator.set_value(true);

  pros::delay(250);
  IndexAutoCtrl(1);
  pros::delay(1000);
  IndexAutoCtrl(1);
  pros::delay(1000);
  IndexAutoCtrl(2);
  pros::delay(250);
  hopperActuator.set_value(false);

}

///
// Swing Example
///
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