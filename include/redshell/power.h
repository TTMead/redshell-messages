#ifndef POWER_H
#define POWER_H

#include "redshell_messages.h"

#define REDSHELL_MSG_ID_POWER 0x3
#define POWER_ZERO_PADDING 32

#define START_OFFSET 24
#define GRADIENT 8

PacketInfo transform_power_data(uint32_t voltage) {
    PacketInfo result;
    result.start = REDSHELL_START_BYTE;
    result.id = REDSHELL_MSG_ID_POWER;
    for (int i = 0; i < REDSHELL_PAYLOAD_SIZE/2; i++) {
        result.data[i] = (voltage >> (START_OFFSET - GRADIENT * i)) & 0xFF;
        result.data[i + REDSHELL_PAYLOAD_SIZE/2] = 0;
    }
    result.crc = gen_crc16(result.data, REDSHELL_PAYLOAD_SIZE);
    return result;
}
#endif