#ifndef Launcher_h
#define Launcher_h

#include "helpers/HullMovingAverage.hpp"
#include "subsystems/Flywheel.hpp"
#include "api.h"
using namespace pros;



void launcherController(void *);

class Launcher {
public:
    Launcher(Motor& rightMotor, Motor& leftMotor);

    Flywheel rightFlywheel;
    Flywheel leftFlywheel;

    void setRange(bool range);
    void toggleRange();

    double getTemperature();
    bool isReady();
    bool closeRange;

    void setTarget(double rightTarget, double leftTarget);
    void setTarget(double target);

    void shootDisc();
    void shoot(int discs);
};

#endif