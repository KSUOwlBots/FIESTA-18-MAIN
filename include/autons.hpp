#pragma once
#include "Intakes.hpp"
#include "main.h"
#include "pros/rtos.h"
#include "pros/rtos.hpp"
#include "EZ-Template/drive/drive.hpp"

extern Drive chassis;

void Disco_Auto_Left();
void Fiesta_Roller_Complex();
void turn_example();
void drive_and_turn();
void wait_until_change_speed();
void swing_example();
void combining_movements();
void interfered_example();

void default_constants();
void one_mogo_constants();
void two_mogo_constants();
void exit_condition_defaults();
void modified_exit_condition();