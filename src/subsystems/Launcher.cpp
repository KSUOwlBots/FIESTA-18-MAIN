#include "subsystems/Launcher.hpp"
#include "Ports.hpp"
#include "main.h"
#include "Indexer.hpp"

Launcher::Launcher(Motor& rightMotor, Motor& leftMotor) :rightFlywheel(&rightMotor), leftFlywheel(&leftMotor)
{
    this->closeRange = false;
}

void launcherController(void *)
{
    while (true)
    {
        launcherSubsystem.rightFlywheel.hmacontrolTick();
        launcherSubsystem.leftFlywheel.hmacontrolTick();

        if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2))
        {
            if (!launcherSubsystem.closeRange) 
            {
                launcherSubsystem.setTarget(38, 38); 
                Tongue.set_value(true);
                launcherSubsystem.closeRange = !launcherSubsystem.closeRange;
            }
            else
            {
                launcherSubsystem.setTarget(60); 
                Tongue.set_value(false);
                launcherSubsystem.closeRange = !launcherSubsystem.closeRange;
            }
        }

        pros::delay(20);  
    }
}




void Launcher::setTarget(double rightTarget, double leftTarget) { this->rightFlywheel.setTarget(rightTarget); this->leftFlywheel.setTarget(leftTarget); }
void Launcher::setTarget(double target) { this->setTarget(0.5*target, target); }

bool Launcher::isReady() { return (leftFlywheel.isReady() && rightFlywheel.isReady()); }

void Launcher::shootDisc()
{
    while (!this->isReady()) { pros::delay(20); }
    IndexAutoCtrl(1);
    std::cout << "\n\n\n\n\n" << std::endl;
    leftFlywheel.printSpeedValues();
}


void Launcher::shoot(int discs)
{
    for (int i = 0; i < discs; i++)
    {
        shootDisc();
        pros::delay(100);
    }
}
