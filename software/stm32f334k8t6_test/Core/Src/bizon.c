#include "bizon.h"

void bizon_init(Bizon *bizon, float max_speed) {
	bizon_set_max_speed(bizon, max_speed);

	bizon_pin_init(&bizon->mb1, U3_IN1_GPIO_Port, U3_IN1_Pin);
	bizon_pin_init(&bizon->mb2, U3_IN2_GPIO_Port, U3_IN2_Pin);
	motor_pololu_init(&bizon->motor_left, &bizon->mb1, &bizon->mb2, &TIM3->CCR1);

	bizon_pin_init(&bizon->ma1, U1_IN1_GPIO_Port, U1_IN1_Pin);
	bizon_pin_init(&bizon->ma2, U1_IN2_GPIO_Port, U1_IN2_Pin);
	motor_pololu_init(&bizon->motor_right ,&bizon->ma1, &bizon->ma2, &TIM3->CCR2);
	bizon->esc_speed = &TIM2->CCR1;
}

void bizon_drive(Bizon *bizon, float forward, float rotation) {
	float left = (forward + rotation) * bizon->max_speed;
	float right = (forward - rotation) * bizon->max_speed;
	motor_pololu_set_speed(&bizon->motor_left, left);
	motor_pololu_set_speed(&bizon->motor_right, right);
}

void bizon_set_max_speed(Bizon *bizon, float max_speed) {
	bizon->max_speed = max_speed;
}

void bizon_set_esc_speed(Bizon *bizon, float esc_speed) {
	*bizon->esc_speed = 1000+ esc_speed * 1000;
//	TIM2->CCR1 = 2000;

}
