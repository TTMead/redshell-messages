#ifndef IMU_H
#define IMU_H

#include "redshell_messages.h"

#define REDSHELL_MSG_ID_IMU 0x0

PacketInfo msg_imu_encode(uint16_t x, uint16_t y, uint16_t z) {
    PacketInfo result;
    result.start = REDSHELL_START_BYTE;
    result.id = REDSHELL_MSG_ID_IMU;
    result.data[0] = (x >> REDSHELL_PAYLOAD_SIZE) & 0xFF;
    result.data[1] = (x & 0xFF);
    result.data[2] = (y >> REDSHELL_PAYLOAD_SIZE) & 0xFF;
    result.data[3] = (y & 0xFF);
    result.data[4] = (z >> REDSHELL_PAYLOAD_SIZE) & 0xFF;
    result.data[5] = (z & 0xFF);
    result.data[6] = 0;
    result.data[7] = 0;
    result.crc = gen_crc16(result.data, REDSHELL_PAYLOAD_SIZE);  // Compute CRC16 checksum for data integrity
    return result;
}

void msg_imu_decode(PacketInfo packet, uint16_t* x, uint16_t* y, uint16_t* z) {
    *x = packet.data[1] | (packet.data[0] << REDSHELL_PAYLOAD_SIZE);
    *y = packet.data[3] | (packet.data[2] << REDSHELL_PAYLOAD_SIZE);
    *z = packet.data[5] | (packet.data[4] << REDSHELL_PAYLOAD_SIZE);
}

#endif
