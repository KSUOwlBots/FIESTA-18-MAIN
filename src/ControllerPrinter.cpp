#include "ControllerPrinter.hpp"
#include "EZ-Template/util.hpp"
#include "Flywheel.hpp"
#include "api.h"
#include "main.h"
#include "pros/misc.h"

char* SpeedLine()
{
    char* toReturn = new char[13];

    int currentVelocity = ez::util::clip_num(getFlywheelVelocity(), 102, 89);

    int i = 0;

    for (; i < (currentVelocity-89); i++)
    {
        toReturn[i] = '#';
    }

    for (; i < (110 - 89); i++) {
        toReturn[i] = ' ';
    }

    return toReturn;
}

void PrintInfo(void *)
{
  while (true)
  {
    // if (getFlywheelTarget() > 80)
    // {  master.print(0, 0, "RPM: %d / %d  ", ((int)launcherSubsystem.leftFlywheel.getMotorVelocity()), ((int)getFlywheelTarget()));  }
    // else
    // {  master.print(0, 0, "RPM: %d / %d  ", ((int)getFlywheelVelocityCheap()), ((int)getFlywheelTarget()));}

    master.print(0, 0, "%d / %d", (int) launcherSubsystem.leftFlywheel.speedValues.value(), (int) launcherSubsystem.leftFlywheel.targetSpeed);
    
    pros::delay(50);
    master.print(1, 0, "%d  ", (int) launcherSubsystem.leftFlywheel.getTemperature());
    pros::delay(250);
  }
}