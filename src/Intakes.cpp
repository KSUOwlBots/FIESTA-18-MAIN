#include "Intakes.hpp"
#include "api.h"
#include "main.h"
#include "pros/misc.h"

void Intake_Control(void *)
{
  bool think = false;
  while (true)
  {
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1) && think == false)
    {
      intake1.move_velocity(-600);
      intake2.move_velocity(600);
    }
    
    else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2))
    {
      intake1.move_velocity(600);
      intake2.move_velocity(-600);
    }
    
    else if (Hopper.get() <= 90)
    {
      think =true;
      intake1.move_velocity(0);
      intake2.move_velocity(0);
    }
    else
    {
      think = false;
      intake1.move_velocity(0);
      intake2.move_velocity(0);
    }

    pros::delay(20);
  }   
}

void Intake_Actuate(void *)
{
  while(true)
  {
    if ((master.get_digital(pros::E_CONTROLLER_DIGITAL_UP)))
    {
      IntakeActuator.set_value(true);
    }
    else
    {
      IntakeActuator.set_value(false);
    }

    pros::delay(20);
  }
}

void Intake_Auto(int x) {
    intake1.move_velocity(-x);
    intake2.move_velocity(x);
    if(x >= 0){
      indexer.move_velocity(x);
    }
}

void Actuate_Auto(bool active)
{
  IntakeActuator.set_value(active);
}

void Roller_Auto(int x)
{
  if (x == 90)
  {
    intake1.move_relative(400, 600);
    intake2.move_relative(-400, 600);
  }
  else if (x == 180)
  {
    intake1.move_relative(-600, 600);
    intake2.move_relative(600, 600);
  }
}