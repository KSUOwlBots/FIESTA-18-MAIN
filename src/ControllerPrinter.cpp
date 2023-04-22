#include "ControllerPrinter.hpp"
#include "EZ-Template/util.hpp"
#include "api.h"
#include "main.h"
#include "pros/misc.h"
#include "subsystems/Launcher.hpp"
#include "subsystems/Hopper.hpp"

void PrintInfo(void *)
{
  while (true)
  {
    master.print(0, 0, "%d / %d / %d ", (int) launcherSubsystem.leftFlywheel.speedValues.value(), 
                                        (int) launcherSubsystem.leftFlywheel.targetSpeed,
                                        (int) launcherSubsystem.leftFlywheel.isReady(10, 10));
    
    pros::delay(50);
    master.print(1, 0, "%d   ", (int) launcherSubsystem.leftFlywheel.getTemperature());
    
    pros::delay(50);
    master.print(2, 0, "%d ", (int) hopperSubsystem.discs());

    pros::delay(250);
  }
}