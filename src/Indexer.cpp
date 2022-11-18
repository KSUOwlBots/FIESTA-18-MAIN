#include "Indexer.hpp"
#include "api.h"
#include "main.h"
#include "pros/misc.h"

const int indexerRiseTime = 400;
const int indexerFallTime = 100;

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
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN))
        {
            IndexCount(1);
        }

        pros::delay(ez::util::DELAY_TIME);
    }
}