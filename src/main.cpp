#include "main.h"
#include "helpers/HullMovingAverage.hpp"
#include "ControllerPrinter.hpp"
#include "EZ-Template/util.hpp"
#include "Endgame.hpp"
#include "Indexer.hpp"
#include "Intakes.hpp"
#include "autons.hpp"
#include "pros/adi.hpp"
#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/motors.hpp"
#include "pros/rtos.h"
#include "pros/rtos.hpp"


// For instalattion, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/



Launcher launcherSubsystem(FlywheelMotor1, FlywheelMotor2);


Drive chassis(
    // Left Chassis Ports (negative port will reverse it!)
    //   the first port is the sensored port (when trackers are not used!)
    {-8, -7, -6, -9}

    // Right Chassis Ports (negative port will reverse it!)
    //   the first port is the sensored port (when trackers are not used!)
    ,
    {1, 2, 3, 4}

    // IMU Port
    ,
    10

    // Wheel Diameter (Remember, 4" wheels are actually 4.125!)
    //    (or tracking wheel diameter)
    ,
    2.75

    // Cartridge RPM
    //   (or tick per rotation if using tracking wheels)
    ,
    600

    // External Gear Ratio (MUST BE DECIMAL)
    //    (or gear ratio of tracking wheel)
    // eg. if your drive is 84:36 where the 36t is powered, your RATIO would
    // be 2.333. eg. if your drive is 36:60 where the 60t is powered, your RATIO
    // would be 0.6.
    ,
    1.1

    // Uncomment if using tracking wheels
    /*
    // Left Tracking Wheel Ports (negative port will reverse it!)
    // ,{1, 2} // 3 wire encoder
    // ,8 // Rotation sensor

    // Right Tracking Wheel Ports (negative port will reverse it!)
    // ,{-3, -4} // 3 wire encoder
    // ,-9 // Rotation sensor
    */

    // Uncomment if tracking wheels are plugged into a 3 wire expander
    // 3 Wire Port Expander Smart Port
    // ,1
);




/**
  ___       _ _   _       _ _         
 |_ _|_ __ (_) |_(_) __ _| (_)_______ 
  | || '_ \| | __| |/ _` | | |_  / _ \
  | || | | | | |_| | (_| | | |/ /  __/
 |___|_| |_|_|\__|_|\__,_|_|_/___\___|
                                      
*/
void initialize()
{
  // ez::print_ez_template();
  pros::delay(500); // Wait for legacy ports configure.


  // Configure your chassis controls
  chassis.toggle_modify_curve_with_controller(false);
  chassis.set_active_brake(0.05); // Sets the active brake kP. We recommend 0.1.
  chassis.set_curve_default(3, 3);
  default_constants();
  exit_condition_defaults();


  ez::as::auton_selector.add_autons({
    Auton("You know exactly what the fuck goin on", Frenzy_Rush_Mid),
    Auton("Cope Seethe", Default)
  });
  chassis.initialize();
  ez::as::initialize();

  Task launcherSubsystem(launcherController);
}






/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  chassis.reset_pid_targets();               // Resets PID targets to 0
  chassis.reset_gyro();                      // Reset gyro position to 0
  chassis.reset_drive_sensor();              // Reset drive sensors to 0
  chassis.set_drive_brake(MOTOR_BRAKE_HOLD); // Set motors to hold.  This helps
                                             // autonomous consistency.
 //ez::as::auton_selector.call_selected_auton();
 Frenzy_Rush_Mid();
 //Default();
//  pros::Task IndexerTask(FlywheelAutoCtrl);
//   newFlywheelVelocity(65);
//   pros::delay(2000);
//    IndexAutoCtrl(1);

 
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

bool antiRot = false;

void opcontrol()
{
  launcherSubsystem.setTarget(70);

  chassis.set_drive_brake(MOTOR_BRAKE_COAST);

  pros::Task IndexerTask(IndexOPCTRL);
  pros::Task ControllerPrintTask(PrintInfo);
  pros::Task IntakeControlTask(Intake_Control);
  pros::Task IntakeActuation(Intake_Actuate);
  pros::Task Endgame(Endgame_Fire);

  master.clear();

  bool driveStick = true;


  while (true)
  {
    chassis.arcade_standard(ez::SINGLE);
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) { launcherSubsystem.setTarget(launcherSubsystem.leftFlywheel.getTarget() + 1); }
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) { launcherSubsystem.setTarget(launcherSubsystem.leftFlywheel.getTarget() - 1); }

    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_A))
    {
      std::cout
      // << FlywheelMotor1.get_actual_velocity() 
      // << " "
      << FlywheelMotor2.get_actual_velocity()
      << " "
      // << launcherSubsystem.rightFlywheel.getVelocity()
      // << " "
      << launcherSubsystem.leftFlywheel.getVelocity()
      << " "
      << launcherSubsystem.leftFlywheel.flywheelMotor->get_current_draw()
      << std::endl;
    }

    pros::delay(ez::util::DELAY_TIME);
  }
}




















/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() { }





/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() { }