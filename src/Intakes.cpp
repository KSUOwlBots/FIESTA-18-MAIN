#include "Intakes.hpp"
#include "api.h"
#include "main.h"
#include "pros/misc.h"

void Intake_Control(void *)
{
  while (true)
  {
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1))
    {
      intake1.move_velocity(-600);
      intake2.move_velocity(600);
    }
    
    else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2))
    {
      intake1.move_velocity(600);
      intake2.move_velocity(-600);
    }
    
    else 
    {
      intake1.move_velocity(0);
      intake2.move_velocity(0);
    }

    pros::delay(20);
  }   
}

void Roller_Control(void *){
  while (true)
  {
    if ((master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)))
    {
      roller.move_velocity(-100);
    }
    else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)){
      roller.move_velocity(100);
    }
    else {
      roller.move_velocity(0);
    }
  pros::delay(20);

  }
}
void Intake_Auto(int x) {
    intake1.move_velocity(-x);
    intake2.move_velocity(x);
}
