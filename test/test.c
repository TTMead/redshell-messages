#include <stdio.h>

#include "redshell/command.h"
#include "redshell/encoder.h"
#include "redshell/imu.h"
#include "redshell/power.h"


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

void test_serialization()
{
    PacketInfo imu_packet = msg_imu_encode(1, 5, 127);

    uint8_t serialized_message[REDSHELL_MESSAGE_SIZE];
    serialize(imu_packet, serialized_message);

    printf("[PASSED] Serialization.\n");
}

void test_deserialization()
{
    PacketInfo imu_send_packet = msg_imu_encode(1, 5, 127);

    // Serialize the imu packet
    uint8_t serialized_message[REDSHELL_MESSAGE_SIZE];
    serialize(imu_send_packet, serialized_message);

    // Create a receive packet filled with junk data
    PacketInfo imu_receive_packet;
    imu_receive_packet.data[0] = 9;
    imu_receive_packet.data[1] = 100;
    imu_receive_packet.data[2] = 42;
    imu_receive_packet.data[3] = 75;

    // Override the receive packet with the deserialized message
    deserialize(&imu_receive_packet, serialized_message);

    int data_equal = 1;
    for (int i = 0; i < REDSHELL_PAYLOAD_SIZE; i++)
    {
        data_equal = data_equal && (imu_send_packet.data[i] == imu_receive_packet.data[i]);
    }

    if (data_equal)
    {
        printf("[PASSED] Deserialization.\n");
    }
    else
    {
        printf("[FAILED] Deserialization.\n");
    }
}

int main()
{
    printf("\n ==== Starting Unit Tests ====\n");
    test_command_coding();
    test_encoder_coding();
    test_imu_coding();
    test_serialization();
    test_deserialization();
    printf(" ==== Tests Complete ====\n\n");
}