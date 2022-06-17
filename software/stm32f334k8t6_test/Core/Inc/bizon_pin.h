/*
 * bizon_pin.h
 *
 *  Created on: Jun 16, 2022
 *      Author: deli
 */

#ifndef INC_BIZON_PIN_H_
#define INC_BIZON_PIN_H_

#include <stdint.h>
#include "stm32f3xx_hal.h"
typedef struct {
	GPIO_TypeDef* port;
	uint32_t pin;
}BizonPin;

void bizon_pin_init(BizonPin *bizon_pin, GPIO_TypeDef* port, uint32_t pin);
void bizon_pin_set_high(BizonPin *bizon_pin);
void bizon_pin_set_low(BizonPin *bizon_pin);
void bizon_pin_toggle(BizonPin *bizon_pin);



#endif /* INC_BIZON_PIN_H_ */
