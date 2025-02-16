/*
 * motor_module.h
 *
 *  Created on: 18.06.2024
 *      Author: LennartStuecker
 */

#ifndef MOTOR_MODULE_H_
#define MOTOR_MODULE_H_

#include "inc/tm4c1294ncpdt.h"
#include <stdio.h>
#include <stdint.h>
#include <math.h>

//#define CLOCKWISE 1
//#define ANTICLOCKWISE 0
#define ENCODERFACTOR 16

void calculateSpeed(float cycleTime);
void configTimer2A();
void configPortL();
void configPortC();
//void configPortK();
//void configPortE();

#endif /* MOTOR_MODULE_H_ */
