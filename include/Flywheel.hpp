#pragma once

#include "api.h"
#include "main.h"
#include "HMA.hpp"

void power(double percentage);
double getFlywheelVelocity();
double getFlywheelTarget();
int getTemperature();
void flywheelControlledSpeed(double target);
void FlywheelOPCTRL();
void FlywheelAutoCtrl(void *);
double getFlywheelVelocityCheap();
void newFlywheelVelocity(double target);