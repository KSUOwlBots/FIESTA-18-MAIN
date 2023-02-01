#include "Endgame.hpp"
#include "api.h"
#include "main.h"
#include "pros/misc.h"
#include "pros/rtos.hpp"

void Endgame_Fire(void *)
{
  double startTime, driveTime, deployTime;
  bool wasDisabled = true;
  if(wasDisabled){
    startTime = pros::millis();
  }
  //set how long the driver run will be
  //change this number
  driveTime = 60;
  //do math for time
  deployTime = driveTime*1000 - 10000;
  while (true)
  {
    if(pros::millis() - startTime == deployTime){

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