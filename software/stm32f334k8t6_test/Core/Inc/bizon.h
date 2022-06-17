/*
 * bizon.h
 *
 *  Created on: Jun 16, 2022
 *      Author: deli
 */


#ifndef INC_BIZON_H_
#define INC_BIZON_H_

#include "motor_pololu.h"
#include "stm32f3xx_hal.h"
#include "main.h"


typedef struct {
	BizonPin mb1;
	BizonPin mb2;
	BizonPin ma1;
	BizonPin ma2;
	MotorPololu motor_left;
	MotorPololu motor_right;
	uint32_t *esc_speed;
	float max_speed;
}Bizon;

void bizon_init(Bizon *bizon, float max_speed);
void bizon_drive(Bizon *bizon, float forward, float rotation);
void bizon_set_max_speed(Bizon *bizon, float max_speed);
void bizon_set_esc_speed(Bizon *bizon, float esc_speed);


#endif /* INC_BIZON_H_ */
