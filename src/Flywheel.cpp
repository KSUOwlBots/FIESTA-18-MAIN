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
double integral = 0;
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

void flywheelControlledSpeed(double targetRPM)
{
  // The error of the system is equal to the difference in velocity
  error = (targetRPM/36) - getVelocity();

  // Smooth the inputs across the 5 most recent values
  // This reduces noise in the data
  for (int i = 0; i < smoothSize-1; i++) { speeds[i] = speeds[i + 1]; }
  speeds[smoothSize-1] = mean(abs(FlywheelMotor1.get_actual_velocity()), abs(FlywheelMotor2.get_actual_velocity()));

  // The integral increases/decreases by 1 over time
  // This compensates for the error value not getting the motor powers to what we want
  // Clamp the integral to 10 -> -10 to ensure it doesn't grow too powerful
  // Reset the integral if the error is over 20
  integral = clamp(integral+ez::util::sgn(error), 10, -10);
  if (abs(error) > 20) { integral = 0; }

  // Speed is equal to error + target + integral
  // target gets us ~88% there
  // Error gets us 9% more
  // Integral gets the remaining 3%
  speed = clamp(kP*error + (targetRPM/36) + kI*integral, 100, 0);
  power(speed);
  std::cout << (int)(getVelocity()*36) << "\t" << (int)error << "\t" << (int)integral <<"\t"<< (int)speed << endl;
}

void FlywheelOPCTRL()
{
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP))
    {
        flywheel = !flywheel;
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