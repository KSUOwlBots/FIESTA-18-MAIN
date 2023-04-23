#include "helpers/Maths.hpp"
#include "Ports.hpp"
#include "subsystems/Hopper.hpp"
#include "api.h"
#include "main.h"
#include "Intakes.hpp"

void hopperController(void *)
{
    while(true)
    {
        hopperSubsystem.distanceValues.append(HopperDistance.get());
        if (hopperSubsystem.distanceValues.sumError(hopperSubsystem.distanceValues.top(), 15) <= 20) 
        {
            if (inBetween(hopperSubsystem.distanceValues.mean(), 95, 110)) { hopperSubsystem.mostRecentValue = 0; }
            if (inBetween(hopperSubsystem.distanceValues.mean(), 71, 94)) { hopperSubsystem.mostRecentValue = 1; }
            if (inBetween(hopperSubsystem.distanceValues.mean(), 55, 70)) { hopperSubsystem.mostRecentValue = 2; }
            if (inBetween(hopperSubsystem.distanceValues.mean(), 30, 54)) { hopperSubsystem.mostRecentValue = 3; }
        }

        if (pros::competition::is_autonomous() && intake1.get_actual_velocity() > 25 && hopperSubsystem.discs() == 3)
        {
            Intake_Auto(-600);
        }

        pros::delay(20);
    }
}


Hopper::Hopper(int distanceValueSize) :distanceValues(distanceValueSize)
{
    this->mostRecentValue = 0;
}

int Hopper::discs()
{
    return mostRecentValue;
}