/*
 * sbus.c
 *
 *  Created on: Apr 13, 2026
 *      Author: asmab
 */

#include "sbus.h"

uint16_t channels[16];

void decode_sbus(uint8_t *buf)
{
    channels[0]  = ((buf[1]      | buf[2] << 8)                         & 0x07FF);
    channels[1]  = ((buf[2] >> 3 | buf[3] << 5)                         & 0x07FF);
    channels[2]  = ((buf[3] >> 6 | buf[4] << 2 | buf[5] << 10)         & 0x07FF);
    channels[3]  = ((buf[5] >> 1 | buf[6] << 7)                         & 0x07FF);
    channels[4]  = ((buf[6] >> 4 | buf[7] << 4)                         & 0x07FF);
    channels[5]  = ((buf[7] >> 7 | buf[8] << 1 | buf[9] << 9)          & 0x07FF);
    channels[6]  = ((buf[9] >> 2 | buf[10] << 6)                        & 0x07FF);
    channels[7]  = ((buf[10] >> 5 | buf[11] << 3)                       & 0x07FF);
    channels[8]  = ((buf[12]     | buf[13] << 8)                        & 0x07FF);
    channels[9]  = ((buf[13] >> 3 | buf[14] << 5)                       & 0x07FF);
    channels[10] = ((buf[14] >> 6 | buf[15] << 2 | buf[16] << 10)      & 0x07FF);
    channels[11] = ((buf[16] >> 1 | buf[17] << 7)                       & 0x07FF);
    channels[12] = ((buf[17] >> 4 | buf[18] << 4)                       & 0x07FF);
    channels[13] = ((buf[18] >> 7 | buf[19] << 1 | buf[20] << 9)       & 0x07FF);
    channels[14] = ((buf[20] >> 2 | buf[21] << 6)                       & 0x07FF);
    channels[15] = ((buf[21] >> 5 | buf[22] << 3)                       & 0x07FF);
}

uint8_t read_sbus_frame(UART_HandleTypeDef *huart, uint8_t *buf)
{
    HAL_StatusTypeDef status = HAL_UART_Receive(huart, buf, 25, 6.5);

    if (status != HAL_OK)
    {
        printf("TIMEOUT\r\n");
        return 0;
    }

    printf("RECUS: ");
    for (int i = 0; i < 25; i++)
    {
        printf("%02X ", buf[i]);
    }
    printf("\r\n");

    if (buf[0] == 0x0F)
    {
        printf("HEADER OK\r\n");
        decode_sbus(buf);
        return 1;
    }

    printf("HEADER PAS BON: %02X\r\n", buf[0]);
    return 0;
}
code
