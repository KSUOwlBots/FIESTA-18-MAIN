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


#define slowSpeed 73
#define highSpeed 100

bool flywheel = false;

double kV = 3.0;
double kA = 3.0;
double previousVelocity = 0;

double currentTargetVelocity = slowSpeed;

//30, 40
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

//Show temps
int getTemperature()
{
    return FlywheelMotor1.get_temperature();
}

//Show flywheel vel
double getFlywheelVelocity()
{
    return speeds.value();
}

//Show flywheel vel in bang bang
double getFlywheelVelocityCheap()
{
    // return pros::c::motor_get_actual_velocity(11);
    return mean(abs(FlywheelMotor1.get_actual_velocity()), abs(FlywheelMotor2.get_actual_velocity()));
}

//Get flywheel target when running
double getFlywheelTarget()
{
    return currentTargetVelocity;
}

//Get accel value
double getAccel()
{
    return accels.value();
}

//Changes flywheel vel if new input
void newFlywheelVelocity(double target)
{
    currentTargetVelocity = target;
}

//Long range control loop for consistent shots
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

//Close range bang bang control loop for fast recovery
void flywheelControlledSpeedCheap(double target)
{
    if (getFlywheelVelocityCheap() < target)
    { power(100); }
    else
    { power(slowSpeed); }
}

//How flywheel is controlled in driver
void FlywheelOPCTRL()
{
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A))
    {
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
            Tongue.set_value(false);
        }
        else
        {
            currentTargetVelocity = highSpeed;
            Tongue.set_value(true);
        }
    }

    else if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT))
    {
        currentTargetVelocity = slowSpeed;
        Tongue.set_value(true);
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

//Auto control function for programming
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