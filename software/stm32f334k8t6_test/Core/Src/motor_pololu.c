#include "motor_pololu.h"

void motor_pololu_init(MotorPololu *motor_pololu, BizonPin *in1_pin, BizonPin *in2_pin,	uint32_t *fill_pwm) {
	motor_pololu->in1_pin = in1_pin;
	motor_pololu->in2_pin = in2_pin;
	motor_pololu->fill_pwm = fill_pwm;
}
void motor_pololu_set_speed(MotorPololu *motor_pololu, float fill){
	if (fill>= 0.0) {
		motor_pololu_go_forward(motor_pololu);
	} else {
		motor_pololu_go_backward(motor_pololu);
		fill *= -1;
	}
	uint8_t cos = fill * 100;
	*motor_pololu->fill_pwm = cos ;
}
void motor_pololu_go_forward(MotorPololu *motor_pololu) {
	bizon_pin_set_high(motor_pololu->in1_pin);
	bizon_pin_set_low(motor_pololu->in2_pin);
}
void motor_pololu_go_backward(MotorPololu *motor_pololu) {
	bizon_pin_set_high(motor_pololu->in2_pin);
	bizon_pin_set_low(motor_pololu->in1_pin);
}
void motor_pololu_soft_stop(MotorPololu *motor_pololu) {
	bizon_pin_set_low(motor_pololu->in1_pin);
	bizon_pin_set_low(motor_pololu->in2_pin);
}

