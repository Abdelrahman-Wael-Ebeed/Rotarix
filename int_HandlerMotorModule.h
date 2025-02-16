/*
 * int_HandlerMotorModule.h
 *
 *  Created on: 18.06.2024
 *      Author: LennartStuecker
 */

#ifndef INT_HANDLERMOTORMODULE_H_
#define INT_HANDLERMOTORMODULE_H_

#include <motor_module.h>
#include <stdint.h>

void IntPortLHandler();
extern volatile unsigned short speed;


#endif /* INT_HANDLERMOTORMODULE_H_ */
