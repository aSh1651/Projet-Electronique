/*
 * sbus.c
 *
 *  Created on: May 4, 2026
 *      Author: asmab
 */
#include "sbus.h"

void decode_sbus(uint8_t *sbus_buffer, uint16_t *sbus_channels) {
    // Vérification du Header (0x0F) et du Footer (0x00)

    if (sbus_buffer[0] != 0x0F) return;

    // Décodage des 11 bits par canal via décalage de bits
    sbus_channels[0]  = ((sbus_buffer[1]      | sbus_buffer[2]  << 8) & 0x07FF);
    sbus_channels[1]  = ((sbus_buffer[2] >> 3 | sbus_buffer[3]  << 5) & 0x07FF);
    sbus_channels[2]  = ((sbus_buffer[3] >> 6 | sbus_buffer[4]  << 2 | sbus_buffer[5]  << 10) & 0x07FF);
    sbus_channels[3]  = ((sbus_buffer[5] >> 1 | sbus_buffer[6]  << 7) & 0x07FF);
    sbus_channels[4]  = ((sbus_buffer[6] >> 4 | sbus_buffer[7]  << 4) & 0x07FF);
    sbus_channels[5]  = ((sbus_buffer[7] >> 7 | sbus_buffer[8]  << 1 | sbus_buffer[9]  << 9) & 0x07FF);
    sbus_channels[6]  = ((sbus_buffer[9] >> 2 | sbus_buffer[10] << 6) & 0x07FF);
    sbus_channels[7]  = ((sbus_buffer[10] >> 5 | sbus_buffer[11] << 3) & 0x07FF);
    sbus_channels[8]  = ((sbus_buffer[12]     | sbus_buffer[13] << 8) & 0x07FF);
    sbus_channels[9]  = ((sbus_buffer[13] >> 3 | sbus_buffer[14] << 5) & 0x07FF);
    sbus_channels[10] = ((sbus_buffer[14] >> 6 | sbus_buffer[15] << 2 | sbus_buffer[16] << 10) & 0x07FF);
    sbus_channels[11] = ((sbus_buffer[16] >> 1 | sbus_buffer[17] << 7) & 0x07FF);
    sbus_channels[12] = ((sbus_buffer[17] >> 4 | sbus_buffer[18] << 4) & 0x07FF);
    sbus_channels[13] = ((sbus_buffer[18] >> 7 | sbus_buffer[19] << 1 | sbus_buffer[20] << 9) & 0x07FF);
    sbus_channels[14] = ((sbus_buffer[20] >> 2 | sbus_buffer[21] << 6) & 0x07FF);
    sbus_channels[15] = ((sbus_buffer[21] >> 5 | sbus_buffer[22] << 3) & 0x07FF);
//    // Byte 23 contient les drapeaux (Failsafe et Frame Lost)
//    sbus->frame_lost = (buffer[23] & 0x04);
//    sbus->failsafe   = (buffer[23] & 0x08);

}


