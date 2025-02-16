/*
 * int_HandlerLcdModule.h
 *
 *  Created on: 18.06.2024
 *      Author: LennartStuecker
 */

#ifndef INT_HANDLERLCDMODULE_H_
#define INT_HANDLERLCDMODULE_H_

#include <lcd_module.h>
extern volatile unsigned char* direction;

//void IntPortKHandler();
void IntPortCHandler();

//extern volatile float speed;

#endif /* INT_HANDLERLCDMODULE_H_ */
