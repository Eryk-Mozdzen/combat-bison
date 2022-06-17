/**
 * @file ssl482.h
 * @author Kornel Koszela, Kacper Chmielewski, Eryk Możdżeń
 * @date 2021-06-26
 * */

#ifndef INC_SSL482_H_
#define INC_SSL482_H_

#include "stm32f3xx_hal.h"

#include <string.h>
#include <stdint.h>
#include <math.h>

/**
 * @brief constants
 * */
#define SSL482_BUFFER_READ_LEN					20
#define SSL482_BUFFER_FRAME_LEN					10

#define SSL482_MESSAGE_TIMEOUT					200

#define SSL482_STEERING_NEUTRAL_RADIUS			50
#define SSL482_STEERING_MIN_VALUE				356
#define SSL482_STEERING_NEUTRAL_VALUE			1028
#define SSL482_STEERING_MAX_VALUE				1689
#define SSL482_STEERING_CUTOFF					1750

#define SSL482_THROTTLE_NEUTRAL_RADIUS			50
#define SSL482_THROTTLE_MIN_VALUE				261
#define SSL482_THROTTLE_NEUTRAL_VALUE			749
#define SSL482_THROTTLE_MAX_VALUE				1577
#define SSL482_THROTTLE_CUTOFF					1650

/**
 * @brief Enumerator of error codes
 * */
typedef enum {
	SSL482_OK,
	SSL482_TRANSMISSION_ERROR,
	SSL482_TRANSMISSION_TIMEOUT,
	SSL482_VALUE_OUT_OF_RANGE
} SSL482Error_EnumTypeDef;

/**
 * @brief Enumerators for switches on remote
 * */
typedef enum {
	SSL482_SW1_UNKNOW = 0,
	SSL482_SW1_PRESSED = 343,
	SSL482_SW1_RELESSED = 1023
} SW1_State_EnumTypeDef;

typedef enum {
	SSL482_SW3_UNKNOW = 0,
	SSL482_SW3_POSITION_1 = 1703,
	SSL482_SW3_POSITION_2 = 1023,
	SSL482_SW3_POSITION_3 = 343
} SW3_State_EnumTypeDef;

/**
 * @brief Struct to manage RC receiver and manage frame data.
 * */
typedef struct {
	UART_HandleTypeDef *huart;						/**< UART HAL handle */
	uint8_t bufferRead[SSL482_BUFFER_READ_LEN];		/**< buffer to read end of previous frame, all current frame and begin of next frame */
	uint8_t bufferFrame[SSL482_BUFFER_FRAME_LEN];	/**< buffer to store frame content */
	uint16_t dataRaw[4];							/**< all raw data values (steering, throttle, AUX1, AUX2) */
	uint32_t dataTimestamp;							/**< time when last message has received */

	SSL482Error_EnumTypeDef status;					/**< receiver status */

	float steering;								/**< correct steering value (wheel position) in range [-1; 1] */
	float throttle;								/**< correct throttle value (trigger position) in range [-1; 1] */
	SW1_State_EnumTypeDef aux1;					/**< correct AUX1 state (SW1 button) */
	SW3_State_EnumTypeDef aux2;					/**< correct AUX2 state (SW3 switch) */
} SSL482_StructTypeDef;

void SSL482_Init(SSL482_StructTypeDef *, UART_HandleTypeDef *);
void SSL482_OnRecive(SSL482_StructTypeDef *);

SSL482Error_EnumTypeDef SSL482_GetStatus(SSL482_StructTypeDef *);

#endif
