#pragma once

#include "api.h"
#include "main.h"

void power(double percentage);
double getVelocity();
int getTemperature();
void flywheelControlledSpeed(double target);
void FlywheelOPCTRL();