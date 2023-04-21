#ifndef Flywheel_h
#define Flywheel_h

#include "helpers/HullMovingAverage.hpp"
#include "api.h"
using namespace pros;

class Flywheel {
public:
    Motor* flywheelMotor;
    double targetSpeed;
    HullMovingAverage speedValues;
    HullMovingAverage accelerationValues;
    QuickQueue motorSpeedHistory;

    Flywheel(Motor* motor);

    void bangbangTick();
    void hmacontrolTick();

    void setTarget(double speed);
    void setTargetRPM(double RPM);
    double getTarget();
    double getTargetRPM();

    int getTemperature();
    double getVelocity();
    double getAcceleration();
    void resetHMA();
    double getMotorVelocity();

    void printSpeedValues();
    bool isReady();

    double findCorrectedPower(double target);
    double integral;

private:
    double previousVelocity;
    double kV;
    double kA;
    double kP;
    double kI;
    double kD;
    double previousError;
    bool recoupSpeed;
};

#endif