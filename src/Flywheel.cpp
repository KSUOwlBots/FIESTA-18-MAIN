#include "Flywheel.hpp"
#include "api.h"
#include "main.h"
#include "pros/misc.h"
#include "QuickQueue.hpp"
#include "HMA.hpp"

bool flywheel = false;

double kV = 1.0;
double kA = 1.0;
double previousVelocity = 0;

HMA speeds(21);
HMA accels(21);

double mean(double val1, double val2) { return ((val1 + val2) / 2); }

double median(double arrOG[], int size)
{
    double arr[size];
    for (int i = 0; i < size; i++) { arr[i] = arrOG[i]; }
    std::sort(arr, arr + size);
    if (size % 2 != 0)
        return (double)arr[size / 2];
    return (double)(arr[(size - 1) / 2] + arr[size / 2]) / 2.0;
}

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
    return speeds.value();
}

double getAccel()
{
    return accels.value();
}

void flywheelControlledSpeed(double target)
{
    double newVelocity = mean(abs(FlywheelMotor1.get_actual_velocity()), abs(FlywheelMotor2.get_actual_velocity()));
    speeds.input(newVelocity);
    double velocity = getVelocity();
    double velocityError = target - velocity;


    double newAcceleration = (previousVelocity-velocity);
    accels.input(newAcceleration);
    double acceleration = getAccel();
    double accelerationError = 0 - acceleration;


    double speed = clamp(target + kV*velocityError + kA*accelerationError, 100, 0);
    power(speed);
    std::cout << velocity << "," << acceleration << "," << speed << endl;
    previousVEL = velocity;
}

void FlywheelOPCTRL()
{
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP))
    {
        flywheel = !flywheel;
        previousVEL = 0;
        speeds.clear();
        accels.clear();
        std::cout << endl << endl << "new power:" << endl << endl;
    }

    if (flywheel)
    {
        flywheelControlledSpeed(90);
    }
    
    else
    {
        power(0);
    }
}