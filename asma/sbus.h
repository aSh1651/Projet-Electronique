/*
 * sbus.h
 *
 *  Created on: Apr 13, 2026
 *      Author: asmab
 */

#ifndef INC_SBUS_H_
#define INC_SBUS_H_

#include "main.h"
#include <stdint.h>

extern uint16_t channels[16];

void decode_sbus(uint8_t *buf);
uint8_t read_sbus_frame(UART_HandleTypeDef *huart, uint8_t *buf);

#endif /* INC_SBUS_H_ */

