#include "Endgame.hpp"
#include "api.h"
#include "main.h"
#include "pros/misc.h"

void Endgame_Fire(void *)
{
  while (true)
  {
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT))
    {
      Endgame.set_value(true);
    }
    else {
      Endgame.set_value(false);
    }

    pros::delay(20);
  }
}

void Endgame_fire_Auto(int x)
{
  if (x == 1)
  {
    Endgame.set_value(true);
  }
  else {
    Endgame.set_value(false);
  }
}