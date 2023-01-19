#include "Indexer.hpp"
#include "api.h"
#include "main.h"
#include "pros/misc.h"

const int indexerRiseTime = 200;
const int indexerFallTime = 125;
bool HopperDetectionLoopBreak = false;
bool brakeState = false;

void IndexCount(int count)
{
    for (int i = 0; i < count; i++)
    {
        IndexerActuator.set_value(true);
        pros::delay(indexerFallTime);
        IndexerActuator.set_value(false);
        pros::delay(indexerRiseTime);
    }
}

void IndexOPCTRL(void *)
{
    while(true)
    {
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
        {
            IndexCount(1);           
        }

        pros::delay(ez::util::DELAY_TIME);
    }
}

void IndexAutoCtrl(int x) { IndexCount(x); }