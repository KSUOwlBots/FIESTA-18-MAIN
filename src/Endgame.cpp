#include "Endgame.hpp"
#include "EZ-Template\auton_selector.hpp"
#include "api.h"
#include "main.h"
#include "pros/misc.h"
#include "pros/rtos.hpp"


void Endgame_Fire(void *)
{
  double startTime, skillsTime, matchTime, deployTime, driveTime;
  bool wasDisabled = true;
  if(wasDisabled){
    startTime = pros::millis();
  }
  //set how long the run will be
  //change this number
  matchTime = 75;
  skillsTime = 60;
  
  //call auton selector page
  if(ez::as::auton_selector.current_auton_page == 0){
    driveTime = matchTime;
  }
  if(ez::as::auton_selector.current_auton_page == 1){
    driveTime = skillsTime;
  }
  //do math to set the time for deploy unlock
  deployTime = driveTime*1000 - 10000;

  while (true)
  {
    
    if(pros::millis() - startTime >= deployTime){
      //if u wanna test the timer uncomment the next line
      //master.print(2,0,"valueTest");
      //eg code here

      int presses = 0;
      if (master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT) && presses == 1)
      {
        Endgame.set_value(true);
      }
      else {
        Endgame.set_value(false);
        SageWall.set_value(false);
      }

      if (master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT))
      {
        SageWall.set_value(true);
        pros::delay(250);
        presses++;
      }

      pros::delay(20);
    }
  }
}

void Endgame_fire_Auto(bool x)
{
  if (x)
  {
    Endgame.set_value(true);
  }
  else {
    Endgame.set_value(false);
  }
}