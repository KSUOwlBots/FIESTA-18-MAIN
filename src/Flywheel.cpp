#include "Flywheel.hpp"
#include "api.h"
#include "main.h"
#include "pros/misc.h"
#include <queue>

bool flywheel = false;

#define smoothSize 5
double speeds[smoothSize];
double kP = 4;
double kI = 1;
double kD = 0;
double integral = 0;
double previousError = 0;
double error = 0;
double speed = 0;

double mean(double val1, double val2) { return ((val1 + val2) / 2); }

double clamp(double val, double max, double min) {
  return (std::max(std::min(val, max), min));
}

void power(double percentage)
{
    FlywheelMotor1.move_voltage(-120*percentage);
    FlywheelMotor2.move_voltage(120*percentage);
}

int getTemperature()
{
    return FlywheelMotor1.get_temperature();
}

double getVelocity()
{
    // return abs(FlywheelMotor1.get_actual_velocity());
    return (speeds[0]+speeds[1]+speeds[2]+speeds[3]+speeds[4])/5;
}

void flywheelControlledSpeed(double target)
{
    error = target - getVelocity();

    for (int i = 0; i < smoothSize-1; i++) {
      speeds[i] = speeds[i + 1];
    }
    speeds[smoothSize-1] = mean(abs(FlywheelMotor1.get_actual_velocity()),
                              abs(FlywheelMotor2.get_actual_velocity()));

    integral = clamp(integral + error, 10, -10);
    if (abs(error) > 20) {
      integral = 0;
    }

    speed = clamp(kP*error + target + kI*integral, 100, 0);
    power(speed);
    std::cout << (int)getVelocity() << "\t" << (int)error << "\t" << (int)integral <<"\t"<< (int)speed << endl;
}

void FlywheelOPCTRL()
{
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP))
    {
        flywheel = !flywheel;
        previousError = 0;
        integral = 0;
        for (int i = 0; i < smoothSize; i++) {
          speeds[i] = 0;
        }
        std::cout << endl << endl << "new power:" << endl << endl;
    }

    if (flywheel)
    {
        flywheelControlledSpeed(95);
    }
    
    else
    {
        power(0);
    }
}