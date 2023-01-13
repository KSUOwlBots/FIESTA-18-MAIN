#include "Flywheel.hpp"
#include "api.h"
#include "main.h"
#include "pros/misc.h"
#include "HMA.hpp"

#define slowSpeed 72

bool flywheel = false;

double kV = 2.0;
double kA = 3.0;
double previousVelocity = 0;

double currentTargetVelocity = slowSpeed;

HMA speeds(30);
HMA accels(40);

double integral = 0;

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

double getFlywheelVelocity()
{
    return speeds.value();
}
double getFlywheelTarget()
{
    return currentTargetVelocity;
}

double getAccel()
{
    return accels.value();
}

void flywheelControlledSpeed_OLD(double targetRPM) {
    double currentVelocity = (getFlywheelVelocity() * 36);

    // The error of the system is equal to the difference in velocity
    double error = (targetRPM*36) - currentVelocity;

    // Smooth the inputs across the 5 most recent values
    // This reduces noise in the data
    speeds.input(mean(abs(FlywheelMotor1.get_actual_velocity()),
                      abs(FlywheelMotor2.get_actual_velocity())));

        // The integral increases/decreases by 1 over time
        // This compensates for the error value not getting the motor powers to
        // what we want Clamp the integral to ensure it doesn't grow too
        // powerful Reset the integral if the error is over 20
    integral = clamp(integral + ez::util::sgn(error), 10, -10);
    if (abs(error) > 200) {
        integral = 0;
    }

    // Speed is equal to error + target + integral
    // target gets us ~88% there
    // Error gets us 9% more
    // Integral gets the remaining 3%
    double speed = clamp(1.0 * error + 0.5 * integral, 100, 0);
    power(speed);
    std::cout << currentVelocity << "," << error << "," << speed << endl;
}

void flywheelControlledSpeed(double target)
{
    double newVelocity = mean(abs(FlywheelMotor1.get_actual_velocity()), abs(FlywheelMotor2.get_actual_velocity()));
    speeds.input(newVelocity);
    double velocity = getFlywheelVelocity();
    double velocityError = target - velocity;


    double newAcceleration = (previousVelocity-velocity);
    accels.input(newAcceleration);
    double acceleration = getAccel();
    double accelerationError = 0 - acceleration;


    double speed = clamp(target - 5 + kV*velocityError + kA*accelerationError, 100, 0);
    power(speed);
    std::cout << velocity << "," << acceleration << "," << speed << endl;
    previousVelocity = velocity;
}

void FlywheelOPCTRL()
{
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A))
    {
        flywheel = !flywheel;
        previousVelocity = 0;
        speeds.clear();
        accels.clear();
        std::cout << endl << endl << "new power:" << endl << endl;
    }

    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2))
    {
        if (currentTargetVelocity == 90) { currentTargetVelocity = slowSpeed; }
        else { currentTargetVelocity = 90; }
    }

    if (flywheel)
    {
        flywheelControlledSpeed(currentTargetVelocity);
    }
    
    else
    {
        power(0);
    }
}

void FlywheelAutoCtrl(double target)
{
    previousVelocity = 0;
    flywheelControlledSpeed(target);
}