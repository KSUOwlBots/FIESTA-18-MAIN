#include "Indexer.hpp"
#include "api.h"
#include "main.h"
#include "pros/misc.h"

const int indexerRiseTime = 200;
const int indexerFallTime = 125;
bool HopperDetectionLoopBreak = false;
bool brakeState = false;



void IndexCount(int count, int moveDistance = 300)
{
    indexer.tare_position();
    indexer.move_relative(-moveDistance*count, 75);
    while (indexer.get_position() > (-moveDistance*count)+5) { pros::delay(20); }
}

void IndexOPCTRL(void *)
{
    while(true)
    {
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2))
        {
            indexer.move_velocity(-75);           
        }
        else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
            hopperActuator.set_value(false);
            indexer.move_velocity(600);
        }
        else {
            indexer.move_velocity(0);
            hopperActuator.set_value(true);
        }

        pros::delay(ez::util::DELAY_TIME);
    }
}

void IndexAutoCtrl(int x) { 
    
    IndexCount(x); 
    
}



// void IndexCount(int count)
// {
//     for (int i = 0; i < count; i++)
//     {
//         IndexerActuator.set_value(true);
//         pros::delay(indexerFallTime);
//         IndexerActuator.set_value(false);
//         pros::delay(indexerRiseTime);
//     }
// }

// void IndexOPCTRL(void *)
// {
//     while(true)
//     {
//         if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
//         {
//             IndexCount(1);           
//         }

//         pros::delay(ez::util::DELAY_TIME);
//     }
// }

// void IndexAutoCtrl(int x) { 
//     IndexCount(x); 

// }