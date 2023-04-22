#include "helpers/Maths.hpp"
#include "Ports.hpp"
#include "subsystems/Hopper.hpp"
#include "api.h"
#include "main.h"

void hopperController(void *)
{
    while(true)
    {
        hopperSubsystem.distanceValues.append(HopperDistance.get());

        pros::delay(20);
    }
}


Hopper::Hopper(int distanceValueSize) :distanceValues(distanceValueSize)
{

}

int Hopper::discs()
{
    if (distanceValues.sumError(distanceValues.top(), 5) > 15) { return -1; }
    else
    {
        if (inBetween(distanceValues.top(), 95, 110)) { return 0; }
        if (inBetween(distanceValues.top(), 80, 90)) { return 1; }
        if (inBetween(distanceValues.top(), 55, 70)) { return 2; }
        if (inBetween(distanceValues.top(), 30, 50)) { return 3; }
    }
    return -1;
}