#include <stdio.h>

#include "command.h"
#include "encoder.h"
#include "imu.h"
#include "power.h"


void test_command_coding()
{
    uint32_t send_motor_left = 30;
    uint32_t send_motor_right = 137;
    PacketInfo command_packet = msg_command_encode(send_motor_left, send_motor_right);

    uint32_t receive_motor_left;
    uint32_t receive_motor_right;
    msg_command_decode(command_packet, &receive_motor_left, &receive_motor_right);

    if ((send_motor_left == receive_motor_left) && (send_motor_right == receive_motor_right))
    {
        printf("[PASSED] Command encoding/decoding.\n");
    }
    else
    {
        printf("[FAILED] Command encoding/decoding.\n");
    }
}

void test_encoder_coding()
{
    uint32_t send_motor_left = 30;
    uint32_t send_motor_right = 137;
    PacketInfo command_packet = msg_encoder_encode(send_motor_left, send_motor_right);

    uint32_t receive_motor_left;
    uint32_t receive_motor_right;
    msg_encoder_decode(command_packet, &receive_motor_left, &receive_motor_right);

    if ((send_motor_left == receive_motor_left) && (send_motor_right == receive_motor_right))
    {
        printf("[PASSED] Encoder encoding/decoding.\n");
    }
    else
    {
        printf("[FAILED] Encoder encoding/decoding.\n");
    }
}

void test_imu_coding()
{
    uint16_t send_x = 1;
    uint16_t send_y = 3;
    uint16_t send_z = 22;
    PacketInfo imu_packet = msg_imu_encode(send_x, send_y, send_z);

    uint16_t receive_x;
    uint16_t receive_y;
    uint16_t receive_z;
    msg_imu_decode(imu_packet, &receive_x, &receive_y, &receive_z);

    if ((send_x == receive_x) && (send_x == receive_x) && (send_x == receive_x))
    {
        printf("[PASSED] IMU encoding/decoding.\n");
    }
    else
    {
        printf("[FAILED] IMU encoding/decoding.\n");
    }
}

int main()
{
    printf("\nStarting Tests ...\n");
    test_command_coding();
    test_encoder_coding();
    test_imu_coding();
    printf("End\n");
}