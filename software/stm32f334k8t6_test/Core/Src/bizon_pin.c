/*
 * bizon_pin.c
 *
 *  Created on: Jun 16, 2022
 *      Author: deli
 */



#include "bizon_pin.h"

bizon_pin_init(BizonPin *bizon_pin, GPIO_TypeDef* port, uint32_t pin){
	bizon_pin->pin = pin;
	bizon_pin->port = port;
}

void bizon_pin_set_high(BizonPin *bizon_pin){
	HAL_GPIO_WritePin(bizon_pin->port, bizon_pin->pin, GPIO_PIN_SET);
}
void bizon_pin_set_low(BizonPin *bizon_pin){
	HAL_GPIO_WritePin(bizon_pin->port, bizon_pin->pin, GPIO_PIN_RESET);
}
void bizon_pin_toggle(BizonPin *bizon_pin){
	HAL_GPIO_TogglePin(bizon_pin->port, bizon_pin->pin);
}
