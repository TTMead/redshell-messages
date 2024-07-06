#ifndef ENCODER_H
#define ENCODER_H

#include "redshell_messages.h"

#define REDSHELL_MSG_ID_ENCODER 0x1

PacketInfo msg_encoder_encode(int32_t speed_motor_left_rpm, int32_t speed_motor_right_rpm) {
    PacketInfo result;
    result.start = REDSHELL_START_BYTE;
    result.id = REDSHELL_MSG_ID_ENCODER;

    const int speed_size_bytes = 4;
    const int byte_size = 8;
    for (int i = 0; i < speed_size_bytes; i++) {
        result.data[i] = (speed_motor_left_rpm >> (byte_size * i)) & 0xFF;
        result.data[i + speed_size_bytes] = (speed_motor_right_rpm >> (byte_size * i)) & 0xFF;
    }
    
    result.crc = gen_crc16(result.data, REDSHELL_PAYLOAD_SIZE);
    return result;
}

void msg_encoder_decode(PacketInfo packet, int32_t* speed_motor_left_rpm, int32_t* speed_motor_right_rpm) {
    *speed_motor_left_rpm = packet.data[0] | (packet.data[1] << 8) | (packet.data[2] << 16) | (packet.data[3] << 24);
    *speed_motor_right_rpm = packet.data[4] | (packet.data[5] << 8) | (packet.data[6] << 16) | (packet.data[7] << 24);
}

#endif