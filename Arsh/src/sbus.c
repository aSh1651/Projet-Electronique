#include "sbus.h"

//const
void decode_sbus(uint8_t *buffer, SbusFrame *sbus) {
    // Vérification du Header (0x0F) et du Footer (0x00)
    if (buffer[0] != 0x0F || buffer[24] != 0x00) return;

    // Décodage des 11 bits par canal via décalage de bits
    sbus->channels[0]  = ((buffer[1]    | buffer[2] << 8)                          & 0x07FF);
    sbus->channels[1]  = ((buffer[2] >> 3 | buffer[3] << 5)                          & 0x07FF);
    sbus->channels[2]  = ((buffer[3] >> 6 | buffer[4] << 2 | buffer[5] << 10)       & 0x07FF);
    sbus->channels[3]  = ((buffer[5] >> 1 | buffer[6] << 7)                          & 0x07FF);
    sbus->channels[4]  = ((buffer[6] >> 4 | buffer[7] << 4)                          & 0x07FF);
    sbus->channels[5]  = ((buffer[7] >> 7 | buffer[8] << 1 | buffer[9] << 9)        & 0x07FF);
    sbus->channels[6]  = ((buffer[9] >> 2 | buffer[10] << 6)                         & 0x07FF);
    sbus->channels[7]  = ((buffer[10] >> 5 | buffer[11] << 3)                        & 0x07FF);
    sbus->channels[8]  = ((buffer[12]   | buffer[13] << 8)                         & 0x07FF);
    sbus->channels[9]  = ((buffer[13] >> 3 | buffer[14] << 5)                        & 0x07FF);
    sbus->channels[10] = ((buffer[14] >> 6 | buffer[15] << 2 | buffer[16] << 10)      & 0x07FF);
    sbus->channels[11] = ((buffer[16] >> 1 | buffer[17] << 7)                        & 0x07FF);
    sbus->channels[12] = ((buffer[17] >> 4 | buffer[18] << 4)                        & 0x07FF);
    sbus->channels[13] = ((buffer[18] >> 7 | buffer[19] << 1 | buffer[20] << 9)      & 0x07FF);
    sbus->channels[14] = ((buffer[20] >> 2 | buffer[21] << 6)                        & 0x07FF);
    sbus->channels[15] = ((buffer[21] >> 5 | buffer[22] << 3)                        & 0x07FF);

    // Byte 23 contient les drapeaux (Failsafe et Frame Lost)
    sbus->frame_lost = (buffer[23] & 0x04);
    sbus->failsafe   = (buffer[23] & 0x08);
}
