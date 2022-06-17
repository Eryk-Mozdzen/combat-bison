/**
 * @file ssl482.c
 * @author Kornel Koszela, Kacper Chmielewski, Eryk Możdżeń
 * @date 2021-06-26
 * */

#include "ssl482.h"

/**
 * @brief functions to internal usage
 */
static float __SSL482_GetProcessedThrottle(uint16_t);
static float __SSL482_GetProcessedSteering(uint16_t);
static SW1_State_EnumTypeDef __SSL482_GetProcessedAUX1(uint16_t);
static SW3_State_EnumTypeDef __SSL482_GetProcessedAUX2(uint16_t);
static uint8_t __SSL482_GetFrameCheckum(uint8_t *);

/**
 * @brief Initialization of RC struct.
 * @details Must be call at the begin of the program.
 * @param rc pointer to target board
 * @param huart pointer to UART HAL handle, that will be in use
 * */
void SSL482_Init(SSL482_StructTypeDef *rc, UART_HandleTypeDef *huart) {
	rc->huart = huart;
	rc->dataTimestamp = 0;
	rc->status = 0;

	rc->steering = 0;
	rc->throttle = 0;
	rc->aux1 = SSL482_SW1_UNKNOW;
	rc->aux2 = SSL482_SW3_UNKNOW;

	// start DMA receiver
	HAL_UART_Receive_DMA(rc->huart, rc->bufferRead, SSL482_BUFFER_READ_LEN);
}

/**
 * @brief ReadBuffer full callback.
 * @details Made for call in HAL_UART_RxCpltCallback() interrupt callback.
 * @param rc pointer to target receiver
 * */
void SSL482_OnRecive(SSL482_StructTypeDef *rc) {
	rc->status = SSL482_OK;

	uint8_t loop = SSL482_BUFFER_READ_LEN - SSL482_BUFFER_FRAME_LEN;
	uint8_t index = 0;

	// search for valid frame in read buffer
	memcpy(rc->bufferFrame, rc->bufferRead, SSL482_BUFFER_FRAME_LEN);

	while(!__SSL482_GetFrameCheckum(rc->bufferFrame) && loop--) {
		index++;
		memcpy(rc->bufferFrame, rc->bufferRead + index, SSL482_BUFFER_FRAME_LEN);
	}

	// restart DMA receiver
	HAL_UART_Receive_DMA(rc->huart, rc->bufferRead, SSL482_BUFFER_READ_LEN);

	// can't find any valid frame (transmission error)
	if(loop==0) {
		rc->status = SSL482_TRANSMISSION_ERROR;
		return;
	}

	// read raw data from frame and save time
	rc->dataRaw[0] = (rc->bufferFrame[1] << 8) + rc->bufferFrame[2];
	rc->dataRaw[1] = (rc->bufferFrame[3] << 8) + rc->bufferFrame[4];
	rc->dataRaw[2] = (rc->bufferFrame[5] << 8) + rc->bufferFrame[6];
	rc->dataRaw[3] = (rc->bufferFrame[7] << 8) + rc->bufferFrame[8];
	rc->dataTimestamp = HAL_GetTick();

	// format data to useful form
	rc->steering = __SSL482_GetProcessedSteering(rc->dataRaw[0]);
	rc->throttle = __SSL482_GetProcessedThrottle(rc->dataRaw[1]);
	rc->aux1 = __SSL482_GetProcessedAUX1(rc->dataRaw[2]);
	rc->aux2 = __SSL482_GetProcessedAUX2(rc->dataRaw[3]);
}

/**
 * @brief Get connection status.
 * @note This function should be called periodically for up-to-date status field.
 * @param rc pointer to target receiver
 * @return status byte, each bit corresponds to other issue
 * */
SSL482Error_EnumTypeDef SSL482_GetStatus(SSL482_StructTypeDef *rc) {

	if((HAL_GetTick() - rc->dataTimestamp)>SSL482_MESSAGE_TIMEOUT)
		rc->status = SSL482_TRANSMISSION_TIMEOUT;
	else if(rc->status>0)
		rc->status = SSL482_TRANSMISSION_ERROR;
	else if(rc->dataRaw[0]>SSL482_STEERING_CUTOFF || rc->dataRaw[1]>SSL482_THROTTLE_CUTOFF)
		rc->status = SSL482_VALUE_OUT_OF_RANGE;

	return rc->status;
}

/**
 * @brief Format throttle value to usable form.
 * @detail inactive zone around neutral value is considered
 * @param throttleRaw raw steering value
 * @return floating point value from range [-1; 1]
 * */
float __SSL482_GetProcessedThrottle(uint16_t throttleRaw) {
	if(throttleRaw==0 || throttleRaw>SSL482_THROTTLE_CUTOFF)
		return 0;

	float raw = (float)throttleRaw - SSL482_THROTTLE_NEUTRAL_VALUE;
	float result = 0;

	if(raw>SSL482_THROTTLE_NEUTRAL_RADIUS)
		result = (raw - SSL482_THROTTLE_NEUTRAL_RADIUS)/(SSL482_THROTTLE_MAX_VALUE - SSL482_THROTTLE_NEUTRAL_VALUE - SSL482_THROTTLE_NEUTRAL_RADIUS);
	else if(raw<-SSL482_THROTTLE_NEUTRAL_RADIUS)
		result = -(raw + SSL482_THROTTLE_NEUTRAL_RADIUS)/(SSL482_THROTTLE_MIN_VALUE - SSL482_THROTTLE_NEUTRAL_VALUE + SSL482_THROTTLE_NEUTRAL_RADIUS);

	return fminf(fmaxf(result, -1), 1);
}

/**
 * @brief Format steering value to usable form.
 * @detail inactive zone around neutral value is considered
 * @param steeringRaw raw steering value
 * @return floating point value from range [-1; 1]
 * */
float __SSL482_GetProcessedSteering(uint16_t steeringRaw) {
	if(steeringRaw==0 || steeringRaw>SSL482_STEERING_CUTOFF)
		return 0;

	float raw = (float)steeringRaw - SSL482_STEERING_NEUTRAL_VALUE;
	float result = 0;

	if(raw>SSL482_STEERING_NEUTRAL_RADIUS)
		result =  (raw - SSL482_STEERING_NEUTRAL_RADIUS)/(SSL482_STEERING_MAX_VALUE - SSL482_STEERING_NEUTRAL_VALUE - SSL482_STEERING_NEUTRAL_RADIUS);
	else if(raw<-SSL482_STEERING_NEUTRAL_RADIUS)
		result =  -(raw + SSL482_STEERING_NEUTRAL_RADIUS)/(SSL482_STEERING_MIN_VALUE - SSL482_STEERING_NEUTRAL_VALUE + SSL482_STEERING_NEUTRAL_RADIUS);

	return fminf(fmaxf(result, -1), 1);
}

/**
 * @brief Format AUX1 value to usable form.
 * @param aux1Raw raw AUX1 value
 * @return AUX1 state
 * */
SW1_State_EnumTypeDef __SSL482_GetProcessedAUX1(uint16_t aux1Raw) {
	switch(aux1Raw) {
		case SSL482_SW1_PRESSED:
		case SSL482_SW1_RELESSED:
			return aux1Raw;
	}

	return SSL482_SW1_UNKNOW;
}

/**
 * @brief Format AUX2 value to usable form.
 * @param aux2Raw raw AUX2 value
 * @return AUX2 state
 * */
SW3_State_EnumTypeDef __SSL482_GetProcessedAUX2(uint16_t aux2Raw) {
	switch(aux2Raw) {
		case SSL482_SW3_POSITION_1:
		case SSL482_SW3_POSITION_2:
		case SSL482_SW3_POSITION_3:
			return aux2Raw;
	}

	return SSL482_SW3_UNKNOW;
}

/**
 * @brief Check if frame is valid.
 * @param buffer RC frame
 * @return 1 if frame is valid, 0 if not
 * */
uint8_t __SSL482_GetFrameCheckum(uint8_t* buffer) {
	uint8_t controlSum = 0;

	for(uint8_t i=0; i<9; i++)
		controlSum +=buffer[i];

	return (controlSum==buffer[9]);
}
