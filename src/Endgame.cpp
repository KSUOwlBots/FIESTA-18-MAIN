#include "Endgame.hpp"
#include "EZ-Template\auton_selector.hpp"
#include "api.h"
#include "main.h"
#include "pros/misc.h"
#include "pros/rtos.hpp"


bool lockDrive = false;

void Endgame_Fire(void *)
{
  double startTime, skillsTime, matchTime, deployTime, driveTime;
  bool wasDisabled = true;
  bool failsafe = false;
  //needs to be outside the while loop cuz otherwise it keeps resetting to 0
  int presses = 0;

  if(wasDisabled){
    startTime = pros::millis();
  }
  //set how long the run will be
  //change this number
  matchTime = 75;
  skillsTime = 60;
  
  //call auton selector page
  if(ez::as::auton_selector.current_auton_page == 0){//first page, add statements here based on what pages are called during match
    driveTime = matchTime;
  }
  if(ez::as::auton_selector.current_auton_page == 1){//second page, skills is skills u should only have one dont be bad
    driveTime = skillsTime;
  }
  //do math to set the time for deploy unlock
  deployTime = driveTime*1000 - 10000;

  while (true)
  {
    
    // if((pros::millis() - startTime >= deployTime)||(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)&&master.get_digital(pros::E_CONTROLLER_DIGITAL_R2))){
    //   //if u wanna test the timer uncomment the next line
    //   //master.print(2,0,"valueTest");
    //   failsafe = true
    //   }
      
      //if(failsafe = true){
        //eg code here
      if (master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT))
      {
        Endgame_Chassis.set_value(true);
      }
      else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT))
      {
        Endgame_Lift.set_value(true);
      }
      else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN))
      {
        SageWall.set_value(true);
        lockDrive = true;
        // chassis.set_active_brake(.8);

        // chassis.imu.tare_yaw();
        // chassis.reset_drive_sensor();
      
      }
      else {
        Endgame_Chassis.set_value(false);
        Endgame_Lift.set_value(false);
        SageWall.set_value(false);
      }

      if (lockDrive)
      {
        
        // double rotation = ez::util::clip_num(chassis.imu.get_yaw()*2, 45, -45);
        // double rightError = ez::util::clip_num(chassis.right_sensor(), 45, -45);
        // double leftError = ez::util::clip_num(chassis.left_sensor(), 45, -45);
        // double forBackError = -((rightError+leftError)/2);
        // chassis.set_tank(-rotation + forBackError, rotation + forBackError);
      }

      pros::delay(20);
  }
}

void Endgame_fire_Auto(bool x)
{
  if (x)
  {
    Endgame_Chassis.set_value(true);
  }
  else {
    Endgame_Chassis.set_value(false);
  }
}