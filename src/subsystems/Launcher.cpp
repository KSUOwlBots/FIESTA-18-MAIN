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
                launcherSubsystem.setTarget(0); 
                Tongue.set_value(false);
                launcherSubsystem.closeRange = !launcherSubsystem.closeRange;
            }
        }

        pros::delay(20);  
    }
}




void Launcher::setTarget(double rightTarget, double leftTarget) { this->rightFlywheel.setTarget(rightTarget); this->leftFlywheel.setTarget(leftTarget); }
void Launcher::setTarget(double target) { this->setTarget(0.5*target, target); }

bool Launcher::isReady(int errorSumSize, int errorSumAcceptable) { return (leftFlywheel.isReady(errorSumSize, errorSumAcceptable) && rightFlywheel.isReady(errorSumSize, errorSumAcceptable)); }

void Launcher::shootDisc(int errorSumSize, int errorSumAcceptable)
{
    while (!this->isReady(errorSumSize, errorSumAcceptable)) { pros::delay(20); }
    IndexOneDisc();
}


void Launcher::shoot(int discs, int errorSumSize, int errorSumAcceptable)
{
    for (int i = 0; i < discs; i++)
    {
        shootDisc(errorSumSize, errorSumAcceptable);
        if (i != discs-1)  {  pros::delay(100);  }
    }
}


void Launcher::shootEmpty(int errorSumSize, int errorSumAcceptable)
{
    std::cout << "\n\nShooting all discs! " << hopperSubsystem.discs() << " discs to shoot!" << std::endl;
    bool print = true;
    while(hopperSubsystem.discs() != 0)
    {
        if (print) {  std::cout << "+- Waiting to be ready to fire..." << std::endl;  print = false;  }
        if (this->isReady(errorSumSize, errorSumAcceptable))
        {
            std::cout << "+- Ready! Shooting 1 disc!" << std::endl;
            IndexOneDisc();
            if (hopperSubsystem.discs() > 1) { pros::delay(100); }
            print = true;
        }
        else { pros::delay(20); }
    }
    std::cout << "Done shooting all discs!" << std::endl;
}