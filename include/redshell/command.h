#ifndef COMMAND_H
#define COMMAND_H

#include "redshell_messages.h"

#define REDSHELL_MSG_ID_COMMAND 0x2

PacketInfo msg_command_encode(int32_t speed_left_pct, int32_t speed_right_pct) {
    PacketInfo result;
    result.start = REDSHELL_START_BYTE;
    result.id = REDSHELL_MSG_ID_COMMAND;
    
    const int speed_size_bytes = 4;
    const int byte_size = 8;
    for (int i = 0; i < speed_size_bytes; i++) {
        result.data[i] = (speed_left_pct >> (byte_size * i)) & 0xFF;
        result.data[i + speed_size_bytes] = (speed_right_pct >> (byte_size * i)) & 0xFF;
    }

    result.crc = gen_crc16(result.data, REDSHELL_PAYLOAD_SIZE);

    return result;
}

void msg_command_decode(PacketInfo packet, int32_t* speed_left_pct, int32_t* speed_right_pct) {
    *speed_left_pct = packet.data[0] | (packet.data[1] << 8) | (packet.data[2] << 16) | (packet.data[3] << 24);
    *speed_right_pct = packet.data[4] | (packet.data[5] << 8) | (packet.data[6] << 16) | (packet.data[7] << 24);
}

#endif