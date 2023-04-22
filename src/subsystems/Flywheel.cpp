#include "helpers/HullMovingAverage.hpp"
#include "subsystems/Flywheel.hpp"
#include "helpers/Maths.hpp"
#include "api.h"
using namespace pros;

Flywheel::Flywheel(Motor* motor) :speedValues(10), accelerationValues(40), motorSpeedHistory(10)
{
    this->flywheelMotor = motor;
    this->targetSpeed = 0;
    this->previousVelocity = 0;
    this->kV = 3.0;
    this->kA = 3.0;
    this->integral = 0;
    this->kP = 1;
    this->kI = 0;
    this->kD = 0;
    this->previousError = 0;
}




/**
  _   _ __  __    _       ____            _             _   
 | | | |  \/  |  / \     / ___|___  _ __ | |_ _ __ ___ | |_ 
 | |_| | |\/| | / _ \   | |   / _ \| '_ \| __| '__/ _ \| (_)
 |  _  | |  | |/ ___ \  | |__| (_) | | | | |_| | | (_) | |_ 
 |_| |_|_|  |_/_/   \_\  \____\___/|_| |_|\__|_|  \___/|_(_)
                                                            
*/ 
// void Flywheel::hmacontrolTick()
// {
//     // smoothed velocity and smoothed acceleration
//     double newVelocity = abs(this->flywheelMotor->get_actual_velocity());
//     motorSpeedHistory.append(newVelocity);
//     this->speedValues.input(newVelocity);
//     double velocity = this->getVelocity();
//     double velocityError = this->targetSpeed - velocity;

//     double newAcceleration = (this->previousVelocity-velocity);
//     this->accelerationValues.input(newAcceleration);
//     double acceleration = this->getAcceleration();
//     double accelerationError = 0 - acceleration;

//     double speed = clamp(this->targetSpeed - 5 + this->kV*velocityError + this->kA*accelerationError, 100, 0);
//     this->flywheelMotor->move_voltage(120*speed);
//     this->previousVelocity = velocity;
// }


// void Flywheel::hmacontrolTick()
// {
//     double currentSpeed = getMotorVelocity();
//     motorSpeedHistory.append(currentSpeed);
//     double derivative = currentSpeed - previousVelocity;

//     if ((targetSpeed - currentSpeed) > 5) 
//     {
//         recoupSpeed = true;
//         speedValues.fill(targetSpeed);
//         integral = 0;
//         lastError = 0;
//     }
//     if (recoupSpeed)  {  flywheelMotor->move_voltage(12000);  }


//     if (!recoupSpeed)
//     {
//         speedValues.input(currentSpeed);
//         double smoothedSpeed = speedValues.value();

//         double error = targetSpeed - speedValues.value();
//         if (abs(error) > 1) { integral = integral + error*0.05; }
//         double speed = clamp( (targetSpeed*0.835 + 7.43) + 1.0*integral, 100 ,0);

//         flywheelMotor->move_voltage(120*speed);
//     }


//     if ((currentSpeed + derivative) >= targetSpeed)  {  recoupSpeed = false;  }

//     previousVelocity = currentSpeed;
// }



void Flywheel::hmacontrolTick()
{
    double currentSpeed = getMotorVelocity();
    motorSpeedHistory.append(currentSpeed);
    double derivative = currentSpeed - previousVelocity;

    if ((targetSpeed - currentSpeed) > 5) 
    {
        recoupSpeed = true;
        speedValues.fill(targetSpeed);
        motorSpeedHistory.clear();
        integral = 0;
        previousError = 0;
    }
    if (recoupSpeed)  {  flywheelMotor->move_voltage(12000);  }


    if (!recoupSpeed)
    {
        speedValues.input(currentSpeed);
        double smoothedSpeed = speedValues.value();

        double error = targetSpeed - smoothedSpeed;
        if (abs(error) > 0.5) { integral = integral + error*0.1; }

        double speed = clamp( (targetSpeed*0.835 + 7.43) + 1.0*integral, 100 ,0);

        flywheelMotor->move_voltage(120*speed);
    }


    if ((currentSpeed + derivative) >= targetSpeed)  {  recoupSpeed = false;  }

    previousVelocity = currentSpeed;
}










/**
  ____                      ____                      
 | __ )  __ _ _ __   __ _  | __ )  __ _ _ __   __ _ _ 
 |  _ \ / _` | '_ \ / _` | |  _ \ / _` | '_ \ / _` (_)
 | |_) | (_| | | | | (_| | | |_) | (_| | | | | (_| |_ 
 |____/ \__,_|_| |_|\__, | |____/ \__,_|_| |_|\__, (_)
                    |___/                     |___/   
*/
void Flywheel::bangbangTick()
{
    if (this->getMotorVelocity() < this->targetSpeed)   { this->flywheelMotor->move_voltage(120*80); }
    else   { this->flywheelMotor->move_voltage(120*50); }
}





void Flywheel::setTarget(double speed) { this->targetSpeed = speed; }
void Flywheel::setTargetRPM(double RPM) { this->targetSpeed = RPM/36; }
double Flywheel::getTarget() { return this->targetSpeed; }
double Flywheel::getTargetRPM() { return this->targetSpeed*36; }

int Flywheel::getTemperature() { return this->flywheelMotor->get_temperature(); }
double Flywheel::getVelocity() { return this->speedValues.value(); }
double Flywheel::getAcceleration() { return this->accelerationValues.value(); }
void Flywheel::resetHMA() { this->speedValues.clear(); this->accelerationValues.clear(); }
double Flywheel::getMotorVelocity() { return this->flywheelMotor->get_actual_velocity(); }

void Flywheel::printSpeedValues()
{
    for (int i = 0; i < motorSpeedHistory.size; i++)
    {  std::cout << motorSpeedHistory.data[i] << "\t" << targetSpeed << std::endl;}
}

bool Flywheel::isReady(int errorSumSize, int errorSumAcceptable)
{
    return  (
            motorSpeedHistory.sumError(targetSpeed, errorSumSize) < errorSumAcceptable
            );
}


double Flywheel::findCorrectedPower(double target)
{
    return 0.0;
}