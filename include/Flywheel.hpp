#pragma once

#include "api.h"
#include "main.h"
#include "HMA.hpp"

void power(double percentage);
double getVelocity();
int getTemperature();
void flywheelControlledSpeed(double target);
void FlywheelOPCTRL();