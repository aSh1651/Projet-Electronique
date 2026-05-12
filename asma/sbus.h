#include <stdint.h>
#include "main.h"
#ifndef INC_SBUS_H_
#define INC_SBUS_H_
typedef struct {
    uint16_t channels[16];
    uint8_t frame_lost;
    uint8_t failsafe;
} SbusFrame;

void decode_sbus();
//void print_channels();

#endif /* INC_SBUS_H_ */
