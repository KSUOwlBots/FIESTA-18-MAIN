#include "Flywheel.hpp"
#include "api.h"
#include "Ports.hpp"
#include "main.h"
#include "pros/misc.h"
#include "HMA.hpp"


/*

I should eventually make a new version of flywheel code where its the same 
velocity control for both close and far ranges, but with a smaller moving 
average for the closer ranges to reduce rise times when shooting close range.

I should also make a single cohesive big settings file so that settings for 
the robot can be changed without directly going into the code to do anything.

I should also also make different indexing speeds for the different distances
when firing to make it easier. Not sure if it would be very helpful, but
sure why not go ahead and add it as well. :shrug:

*/


#define slowSpeed 70
#define highSpeed 90

bool flywheel = false;

double kV = 3.0;
double kA = 3.0;
double previousVelocity = 0;

double currentTargetVelocity = slowSpeed;

//30, 40
HMA speeds(30);
HMA accels(40);

double integral = 0;

// Returns the mean of two values
double mean(double val1, double val2) { return ((val1 + val2) / 2); }

// Returns the median of a list of values
double median(double arrOG[], int size)
{
    double arr[size];
    for (int i = 0; i < size; i++) { arr[i] = arrOG[i]; }
    std::sort(arr, arr + size);
    if (size % 2 != 0)
        return (double)arr[size / 2];
    return (double)(arr[(size - 1) / 2] + arr[size / 2]) / 2.0;
}

// Limits val; min -> val -> max
double clamp(double val, double max, double min) {
  return (std::max(std::min(val, max), min));
}

// Powers the flywheel using voltage (-100 -> 100)
void power(double percentage)
{
    FlywheelMotor1.move_voltage(-120*percentage);
    FlywheelMotor2.move_voltage(120*percentage);
}

// Gets the temperature in C of the flywheel motors
int getTemperature()
{ return mean(FlywheelMotor1.get_temperature(), FlywheelMotor2.get_temperature()); }

// Gets the flywheel velocity as calculated by the advanced moving averages
double getFlywheelVelocity()
{ return speeds.value(); }

// Gets the flywheel velocity as the average of the two flywheel motors
double getFlywheelVelocityCheap()
{ return mean(abs(FlywheelMotor1.get_actual_velocity()), abs(FlywheelMotor2.get_actual_velocity())); }

// Gets the acceleration values of the flywheel using moving averages
double getAccel()
{ return accels.value(); }

// Gets the target velocity of the flywheel
double getFlywheelTarget()
{ return currentTargetVelocity; }

// Changes the target flywheel velocity
void newFlywheelVelocity(double target)
{ currentTargetVelocity = target; }

// The advanced flywheel velocity control
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
    std::cout << target << "\t" << velocity << "\t" << getFlywheelVelocityCheap() << "\t" << acceleration << "\t" << speed << std::endl;
    previousVelocity = velocity;
}

// The bang-bang flywheel velocity control
void flywheelControlledSpeedCheap(double target)
{
    if (getFlywheelVelocityCheap() < target)
    { power(100); }
    else
    { power(slowSpeed); }
}


void FlywheelOPCTRL()
{
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A))
    {
        // new press, 
        flywheel = !flywheel;
        previousVelocity = 0;
        speeds.clear();
        accels.clear();
    }

    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2))
    {
        if (currentTargetVelocity == highSpeed) 
        {
            currentTargetVelocity = slowSpeed;
            toggleTongue(true);
        }
        else
        {
            currentTargetVelocity = highSpeed;
            toggleTongue(false);
        }
    }

    else if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT))
    {
        currentTargetVelocity = slowSpeed;
        toggleTongue(false);
    }

    if (flywheel && currentTargetVelocity == highSpeed)
    {
        flywheelControlledSpeed(currentTargetVelocity);
    }
    if (flywheel && currentTargetVelocity == slowSpeed)
    {
        flywheelControlledSpeedCheap(currentTargetVelocity);
    }
    
    if (!flywheel)
    {
        power(0);
    }
}

void FlywheelAutoCtrl(void *)
{
    previousVelocity = 0;
    speeds.clear();
    accels.clear();
    while(true)
    {
        flywheelControlledSpeed(currentTargetVelocity);
        pros::delay(10);
    }
}