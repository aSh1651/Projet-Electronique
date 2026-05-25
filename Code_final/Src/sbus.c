/*
 * sbus.c
 */

#include "sbus.h"
#include <stdio.h>

uint8_t sbus_buffer[25];
uint16_t sbus_channels[16];

void loop_sbus(void)
{

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



}

void decode_sbus(uint8_t *buffer, SbusFrame *sbus)
{
	if(buffer[0] != 0x0F)
	{
		return;
	}

	sbus->channels[0]  = ((buffer[1]      | buffer[2]  << 8) & 0x07FF);
	sbus->channels[1]  = ((buffer[2] >> 3 | buffer[3]  << 5) & 0x07FF);
	sbus->channels[2]  = ((buffer[3] >> 6 | buffer[4]  << 2 | buffer[5]  << 10) & 0x07FF);
	sbus->channels[3]  = ((buffer[5] >> 1 | buffer[6]  << 7) & 0x07FF);
	sbus->channels[4]  = ((buffer[6] >> 4 | buffer[7]  << 4) & 0x07FF);
	sbus->channels[5]  = ((buffer[7] >> 7 | buffer[8]  << 1 | buffer[9]  << 9) & 0x07FF);
	sbus->channels[6]  = ((buffer[9] >> 2 | buffer[10] << 6) & 0x07FF);
	sbus->channels[7]  = ((buffer[10] >> 5 | buffer[11] << 3) & 0x07FF);
	sbus->channels[8]  = ((buffer[12]     | buffer[13] << 8) & 0x07FF);
	sbus->channels[9]  = ((buffer[13] >> 3 | buffer[14] << 5) & 0x07FF);
	sbus->channels[10] = ((buffer[14] >> 6 | buffer[15] << 2 | buffer[16] << 10) & 0x07FF);
	sbus->channels[11] = ((buffer[16] >> 1 | buffer[17] << 7) & 0x07FF);
	sbus->channels[12] = ((buffer[17] >> 4 | buffer[18] << 4) & 0x07FF);
	sbus->channels[13] = ((buffer[18] >> 7 | buffer[19] << 1 | buffer[20] << 9) & 0x07FF);
	sbus->channels[14] = ((buffer[20] >> 2 | buffer[21] << 6) & 0x07FF);
	sbus->channels[15] = ((buffer[21] >> 5 | buffer[22] << 3) & 0x07FF);

	sbus->frame_lost = buffer[23] & 0x04;
	sbus->failsafe   = buffer[23] & 0x08;
}

