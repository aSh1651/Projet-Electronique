#ifndef INC_SBUS_H_
#define INC_SBUS_H_

#include <stdint.h>
#include "main.h"

extern UART_HandleTypeDef huart3;

extern uint8_t sbus_buffer[25];
extern uint16_t sbus_channels[16];

typedef struct
{
	uint16_t channels[16];
	uint8_t frame_lost;
	uint8_t failsafe;
} SbusFrame;

void loop_sbus(void);
void decode_sbus(uint8_t *buffer, SbusFrame *sbus);

#endif

