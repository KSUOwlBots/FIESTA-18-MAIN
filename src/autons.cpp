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

// START OF DISCO AUTOS

void Frenzy_Rush_Mid()
{
  // Setup
  pros::delay(300);
  pros::Task IndexerTask(FlywheelAutoCtrl);
  newFlywheelVelocity(89);
  Actuate_Auto(true);
  Tongue.set_value(true);

  // Drive towards and aim at goal
  chassis.set_drive_pid(8, 75, true);
  chassis.wait_drive();
  chassis.set_turn_pid(-12, 35);
  chassis.wait_drive();
  pros::delay(1000);

  // Shoot 2 preloads
  IndexAutoCtrl(1);
  pros::delay(650);
  IndexAutoCtrl(1);
  pros::delay(500);
  
  // Collect 1st 3-stack
  Intake_Auto(600);
  Actuate_Auto(false);
  pros::delay(1000);
  chassis.set_drive_pid(-6, 30);
  chassis.wait_drive();
  chassis.set_drive_pid(6, 30);
  chassis.wait_drive();
  pros::delay(1000);
  Intake_Auto(-600);
  Actuate_Auto(true);
  pros::delay(250);

  // Shoot 3 shots
  pros::delay(150);
  IndexAutoCtrl(1);
  pros::delay(850);
  IndexAutoCtrl(1);
  pros::delay(650);
  IndexAutoCtrl(1);
  pros::delay(250);

  // Return to starting position (a little farther back)
  chassis.set_turn_pid(12, 35);
  chassis.wait_drive();
  chassis.set_drive_pid(-19, 75, true);
  chassis.wait_drive();

  // Turn to 2nd 3-stack
  chassis.set_turn_pid(45, 35);
  chassis.wait_drive();
  Intake_Auto(600);
  Actuate_Auto(true);

  // Drive towards 2nd 3-stack
  chassis.set_drive_pid(26, 75);
  chassis.wait_drive();
  pros::delay(250);
  newFlywheelVelocity(90);

  // Get 2nd 3-stack
  Intake_Auto(600);
  Actuate_Auto(false);
  pros::delay(1000);
  chassis.set_drive_pid(-6, 30);
  chassis.wait_drive();
  chassis.set_drive_pid(6, 30);
  chassis.wait_drive();
  pros::delay(1000);
  Intake_Auto(-600);
  Actuate_Auto(true);
  pros::delay(250);

  //Drive forwards a bit again
  chassis.set_drive_pid(4, 20);
  chassis.wait_drive();
  newFlywheelVelocity(88);

  // Turn to goal and get in shooting position
  chassis.set_turn_pid(-22, 35);
  chassis.wait_drive();
 // chassis.set_drive_pid(5, 75);
  //chassis.wait_drive();
  pros::delay(250);

  // Shoot 3 shots
  IndexAutoCtrl(1);
  pros::delay(850);
  IndexAutoCtrl(1);
  pros::delay(850);
  IndexAutoCtrl(1);
  pros::delay(250);

  // Get single disc
  Actuate_Auto(false);
  Intake_Auto(600);
  chassis.set_drive_pid(10, 30);
  chassis.wait_drive();
  pros::delay(1000);
  chassis.set_drive_pid(-10, 30);
  chassis.wait_drive();
  newFlywheelVelocity(87);
  pros::delay(1000);

  // Shoot 1 shot and 1 reserve shot
  IndexAutoCtrl(1);
  pros::delay(650);
  IndexAutoCtrl(1);

  pros::delay(250);
  Intake_Auto(0);

  //Go to roller and spin

  chassis.set_drive_pid(2, 30);
  chassis.wait_drive();

  chassis.set_turn_pid(-135, 75);
  chassis.wait_drive();

  chassis.set_drive_pid(24, 75);
  chassis.wait_drive();

  chassis.set_turn_pid(-180, 75);
  chassis.wait_drive();

  chassis.set_drive_pid(12, 30);
  chassis.wait_drive();

  Roller_Auto(90);
  pros::delay(500);

  //Go under opponent high goal and wait

  newFlywheelVelocity(110);

  chassis.set_drive_pid(-6, 30);
  chassis.wait_drive();

  Intake_Auto(600);

  chassis.set_turn_pid(90, 75);
  chassis.wait_drive();

  chassis.set_drive_pid(86, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_turn_pid(-40, 75);
  chassis.wait_drive();

  chassis.set_drive_pid(26, 35);
  chassis.wait_drive();

  chassis.set_turn_pid(-47, 30);
  chassis.wait_drive();

  Intake_Auto(-600);
  Actuate_Auto(true);

  pros::delay(300);
  IndexAutoCtrl(1);
  pros::delay(1200);
  IndexAutoCtrl(1);
  pros::delay(1200);
  IndexAutoCtrl(1);
  pros::delay(250);

  newFlywheelVelocity(0);

    
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
  int matchloads = 0;

  pros::Task IndexerTask(FlywheelAutoCtrl);
  newFlywheelVelocity(75);
  Tongue.set_value(true);

  chassis.set_turn_pid(-12, 30);
  pros::delay(1000);

  //Fire preloads
  IndexAutoCtrl(1);
  pros::delay(500);
  IndexAutoCtrl(1);
  pros::delay(500);

  //Run Matchloads w/ 1 extra shot
  while (matchloads < 8)
  {
    IndexAutoCtrl(1);
    pros::delay(500);
    matchloads++;
  }
  matchloads = 0;

  //Drive and Turn to Triple stack
  chassis.set_drive_pid(14, 75);
  chassis.wait_drive();

  chassis.set_turn_pid(-135, 75);
  chassis.wait_drive();

  Intake_Auto(600);
  Actuate_Auto(true);

  chassis.set_drive_pid(24, 75);
  chassis.wait_drive();

  //Pick up triple stack
  newFlywheelVelocity(78);
  Intake_Auto(600);
  Actuate_Auto(false);
  pros::delay(1000);
  chassis.set_drive_pid(-6, 30);
  chassis.wait_drive();
  chassis.set_drive_pid(6, 30);
  chassis.wait_drive();
  pros::delay(1000);

  //Turn to goal and fire
  chassis.set_turn_pid(10, 75);
  chassis.wait_drive();

  chassis.set_drive_pid(2, 30);
  chassis.wait_drive();
  Intake_Auto(-600);
  Actuate_Auto(true);
  pros::delay(250);

  //Fire 3 shots in goal
  IndexAutoCtrl(1);
  pros::delay(500);
  IndexAutoCtrl(1);
  pros::delay(500);
  IndexAutoCtrl(1);
  pros::delay(150);

  //Go for 3 line

  newFlywheelVelocity(80);

  chassis.set_drive_pid(-13, 50);
  chassis.wait_drive();

  chassis.set_turn_pid(-45, 75);
  chassis.wait_drive();

  Intake_Auto(600);
  Actuate_Auto(false);

  chassis.set_drive_pid(68, 50);
  chassis.wait_drive();

  pros::delay(500);

  //Turn to goal and fire

  chassis.set_turn_pid(75, 75);
  chassis.wait_drive();

  Intake_Auto(0);

  pros::delay(250);
  IndexAutoCtrl(1);
  pros::delay(500);
  IndexAutoCtrl(1);
  pros::delay(500);
  IndexAutoCtrl(1);
  pros::delay(150);

  //Go to roller 1

  chassis.set_turn_pid(-47, 75);
  chassis.wait_drive();

  chassis.set_drive_pid(31, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_turn_pid(0, 75);
  chassis.wait_drive();

  chassis.set_drive_pid(6, 30);
  chassis.wait_drive();

  Roller_Auto(180);
  pros::delay(500);

  //Get triple stack

  chassis.set_drive_pid(-6, 75);
  chassis.wait_drive();

  Actuate_Auto(true);

  chassis.set_turn_pid(180, 75);
  chassis.wait_drive();

  chassis.set_drive_pid(12, 75);
  chassis.wait_drive();

  Intake_Auto(600);
  Actuate_Auto(false);
  pros::delay(1000);
  chassis.set_drive_pid(-6, 30);
  chassis.wait_drive();
  chassis.set_drive_pid(6, 30);
  chassis.wait_drive();
  pros::delay(1000);

  //Go for roller 2
  
  chassis.set_drive_pid(10, 75);
  chassis.wait_drive();

  chassis.set_turn_pid(270, 75);
  chassis.wait_drive();

  Intake_Auto(0);

  chassis.set_drive_pid(30, 75);
  chassis.wait_drive();

  Roller_Auto(180);
  pros::delay(500);

  //Go to matchload

  newFlywheelVelocity(75);

  chassis.set_drive_pid(-4, 30);
  chassis.wait_drive();

  Intake_Auto(600);

  chassis.set_turn_pid(-171, 75);
  chassis.wait_drive();

  chassis.set_drive_pid(38, 50);
  chassis.wait_drive();

  chassis.set_turn_pid(-192, 30);
  chassis.wait_drive();

  Intake_Auto(0);

  chassis.set_drive_pid(-1, 30);
  chassis.wait_drive();


  //Matchload 10 discs w/ 1 reserve

   while (matchloads < 11)
  {
    IndexAutoCtrl(1);
    pros::delay(500);
    matchloads++;
  }
  matchloads = 0;

  //go to endgame launch pos

  chassis.set_turn_pid(-165, 75);
  chassis.wait_drive();

  chassis.set_drive_pid(-52, 100, true);
  chassis.wait_drive();

  chassis.set_turn_pid(-225, 75);
  chassis.wait_drive();

  pros::delay(100);

  Endgame_fire_Auto(true);
  

}

///
// Wait Until and Changing Max Speed
///
void wait_until_change_speed() {
  // wait_until will wait until the robot gets to a desired position

  // When the robot gets to 6 inches, the robot will travel the remaining
  // distance at a max speed of 40
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_until(6);
  chassis.set_max_speed(40); // After driving 6 inches at DRIVE_SPEED, the robot
                             // will go the remaining distance at 40 speed
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  // When the robot gets to -6 inches, the robot will travel the remaining
  // distance at a max speed of 40
  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_until(-6);
  chassis.set_max_speed(40); // After driving 6 inches at DRIVE_SPEED, the robot
                             // will go the remaining distance at 40 speed
  chassis.wait_drive();
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