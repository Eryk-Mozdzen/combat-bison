/*
 * motor_pololu.hpp
 *
 *  Created on: Jun 16, 2022
 *      Author: deli
 */

#ifndef INC_MOTOR_POLOLU_H_
#define INC_MOTOR_POLOLU_H_



#include <stdint.h>
#include "stm32f3xx_hal.h"
#include "bizon_pin.h"

typedef struct {
	BizonPin *in1_pin;
	BizonPin *in2_pin;
	uint32_t *fill_pwm;
}MotorPololu;


void motor_pololu_init(MotorPololu *motor_pololu, BizonPin *in1_pin, BizonPin *in2_pin, 	uint32_t *fill_pwm);
void motor_pololu_set_speed(MotorPololu *motor_pololu, float fill);
void motor_pololu_go_forward(MotorPololu *motor_pololu);
void motor_pololu_go_backward(MotorPololu *motor_pololu);
void motor_pololu_soft_stop(MotorPololu *motor_pololu);


#endif /* INC_MOTOR_POLOLU_H_ */
