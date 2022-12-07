#include "Flywheel.hpp"
#include "api.h"
#include "main.h"
#include "pros/misc.h"
#include <queue>

bool flywheel = false;

#define smoothSize 21
#define integralSmoothing 2
double speeds[smoothSize];
double accels[smoothSize];
double kP = 1.0;
double kI = (1.0/integralSmoothing);
double integral = 0;
double speed = 0;
double previousVEL = 0;
double velocity = 0;
double acceleration = 0;
double currentVelocity = 0;
double velocityError = 0;
double accelerationError = 0;
double kV = 1.0;
double kA = 1.0;

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
    double sum = 0;
    for (int i = 0; i < smoothSize; i++)
    { sum += speeds[i]; }
    return sum/smoothSize;

    // return median(speeds, smoothSize);
}

double getAccel()
{
    double sum = 0;
    for (int i = 0; i < smoothSize; i++)
    { sum += accels[i]; }
    return sum / smoothSize;

    // return median(accels, smoothSize);
}

void flywheelControlledSpeed(double target)
{
  for (int i = 0; i < smoothSize-1; i++) { speeds[i] = speeds[i + 1]; }
  speeds[smoothSize-1] = mean(abs(FlywheelMotor1.get_actual_velocity()), abs(FlywheelMotor2.get_actual_velocity()));
  velocity = getVelocity();
  velocityError = target - velocity;


  for (int i = 0; i < smoothSize-1; i++) { accels[i] = accels[i + 1]; }
  accels[smoothSize-1] = (previousVEL-velocity);
  acceleration = getAccel();
  accelerationError = 0 - acceleration;


  speed = clamp(target + kV*velocityError + kA*accelerationError, 100, 0);
  power(speed);
  std::cout << velocity << "," << acceleration << "," << speed << endl;
  previousVEL = velocity;
}

void FlywheelOPCTRL()
{
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP))
    {
        flywheel = !flywheel;
        velocity = 0;
        acceleration = 0;
        previousVEL = 0;
        currentVelocity = 0;
        for (int i = 0; i < smoothSize; i++) {
          speeds[i] = 0;
          accels[i] = 0;
        }
        std::cout << endl << endl << "new power:" << endl << endl;
    }

    if (flywheel)
    {
        flywheelControlledSpeed(90);
        // for (int i = 0; i < smoothSize - 1; i++) {
        //   speeds[i] = speeds[i + 1];
        // }
        // speeds[smoothSize - 1] =
        //     mean(abs(FlywheelMotor1.get_actual_velocity()),
        //          abs(FlywheelMotor2.get_actual_velocity()));
        // double velo = getVelocity();

        // for (int i = 0; i < smoothSize - 1; i++) {
        //   accels[i] = accels[i + 1];
        // }
        // accels[smoothSize - 1] = (previousVEL-velo);
        // double accel = getAccel();

        // std::cout << velo << "," << accel << endl;
        // previousVEL = getVelocity();
    }
    
    else
    {
        power(0);
    }
}