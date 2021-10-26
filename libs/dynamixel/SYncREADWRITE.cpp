// #pragma once
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <typeinfo>
#include <numeric>
#include <algorithm>
#include <typeinfo>
#include <bits/stdc++.h>
#include <functional>
#include <math.h>
#include <map>
#include <chrono>
#include <fcntl.h>
#include <termios.h>
#include "dynamixel_sdk.h"
#define STDIN_FILENO 0

#define BAUDRATE 1000000
#define DEVICENAME "/dev/serial/by-id/usb-FTDI_USB__-__Serial_Converter_FT2MZZ48-if00-port0"

#define PROTOCOL_VERSION 1.0

// Control table address XM430
#define ADDR_MX_TORQUE_ENABLE 64
#define ADDR_MX_GOAL_POSITION 116
#define ADDR_MX_PRESENT_POSITION 132

// Data Byte Length
#define LEN_MX_GOAL_POSITION 4
#define LEN_MX_PRESENT_POSITION 4

#define DXL_LOBYTE(w) ((uint8_t)(((uint64_t)(w)) & 0xff))
#define DXL_HIBYTE(w) ((uint8_t)((((uint64_t)(w)) >> 8) & 0xff))

#include "libs/nlohmann/json.hpp"

void nameAssertion(std::vector<std::string> &namess, std::map<std::pair<int, std::string>, float> &init_map,
                   std::map<std::pair<int, std::string>, std::string> &name_map);
template <typename T>
bool compare(std::vector<T> v1, std::vector<T> v2);
int getch()
{
#if defined(__linux__) || defined(__APPLE__)
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
#elif defined(_WIN32) || defined(_WIN64)
    return _getch();
#endif
}

int main(int argc, char const *argv[])
{
    auto start = std::chrono::steady_clock::now();
    /*std::vector<int> id = {1, 2, 3};
    std::vector<std::string> hardware = {"pololu24", "pololu12", "dynamixel"};
    std::vector<std::pair<int, std::string>> joint_name;

    std::vector<float> value = {1000, 2000, 3000};

    std::vector<std::string> names = {"NeckGimbal", "LipUpperRight", "Eyes"};
    std::vector<std::string> namess = {"LipUpperRight", "Eyes", "NeckGimbal"};

    std::map<std::string, int> name_id;
    std::map<std::string, std::pair<int, std::string>> name_key;
    std::map<std::pair<int, std::string>, float> init_map;
    std::map<std::pair<int, std::string>, std::string> name_map;

    //  KEY PAIR
    std::transform(std::begin(id),
                   std::end(id),
                   std::begin(hardware),
                   std::inserter(joint_name,
                                 std::begin(joint_name)),
                   [](int id, std::string hardware)
                   { return std::make_pair(id, hardware); });

    //Map < KEY, POS >
    std::transform(std::begin(joint_name),
                    std::end(joint_name),
                    std::begin(value),
                    std::inserter(init_map, std::begin(init_map)),
                   [](std::pair<int,std::string> pair,  float value) { return std::make_pair(pair, value); }
                   );

    // //MAP  <KEY, NAMES>
    std::transform(std::begin(joint_name),
                   std::end(joint_name),
                   std::begin(names),
                   std::inserter(name_map, std::begin(name_map)),
                   [](std::pair<int, std::string> pair, std::string value)
                   {
                       return std::make_pair(pair, value);
                   });
    std::transform(
        std::begin(names),
        std::end(names),
        std::begin(joint_name),
        std::inserter(name_key, std::begin(name_key)),
        [](std::string name, std::pair<int, std::string> key)
        {
            return make_pair(name, key);
        });

    for (auto it : name_key)
    {
        std::cout << "{" << it.first << " : (" << it.second.first << ", " << it.second.second << ")}" << '\n';
    }

    const auto& itr = name_key.find("NeckGimbal");
    std::cout << itr->second.first <<" || "  << itr->second.second<<  '\n';
    const auto& itr2 = name_map.find(itr->second);
    std::cout << "NAME : "<< itr2->second <<  '\n';


    const auto& itr3 = init_map.find(itr->second);
    std::cout << "POSITION : "<< itr3->second <<  '\n';*/

    dynamixel::PortHandler *portHandler = dynamixel::PortHandler::getPortHandler(DEVICENAME);
    dynamixel::PacketHandler *packetHandler = dynamixel::PacketHandler::getPacketHandler(PROTOCOL_VERSION);
    dynamixel::GroupSyncWrite groupSyncWrite(portHandler, packetHandler, ADDR_MX_GOAL_POSITION, LEN_MX_GOAL_POSITION);
    dynamixel::GroupBulkRead groupBulkRead(portHandler, packetHandler);

    // Open port
    if (portHandler->openPort())
    {
        printf("Succeeded to open the port!\n");
    }
    else
    {
        printf("Failed to open the port!\n");
        printf("Press any key to terminate...\n");
        getch();
        return 0;
    }

    // Set port baudrate
    if (portHandler->setBaudRate(BAUDRATE))
    {
        printf("Succeeded to change the baudrate!\n");
    }
    else
    {
        printf("Failed to change the baudrate!\n");
        printf("Press any key to terminate...\n");
        getch();
        return 0;
    }
    int dxl_comm_result = -1001;
    uint8_t dxl_error = 0;

    // Enbale Dynamixels
    dxl_comm_result = packetHandler->write1ByteTxRx(
        portHandler,
        0, // ID
        ADDR_MX_TORQUE_ENABLE,
        1, // TORQUE ENABLE 1
        &dxl_error);

    if (dxl_comm_result != 0)
    {
        printf("%s\n", packetHandler->getTxRxResult(dxl_comm_result));
    }
    else if (dxl_error != 0)
    {
        printf("%s\n", packetHandler->getRxPacketError(dxl_error));
    }
    else
    {
        printf("Dynamixel has been successfully connected \n");
    }

    dxl_comm_result = packetHandler->write1ByteTxRx(
        portHandler,
        1, // ID
        ADDR_MX_TORQUE_ENABLE,
        1, // TORQUE ENABLE 1
        &dxl_error);
    if (dxl_comm_result != 0)
    {
        printf("%s\n", packetHandler->getTxRxResult(dxl_comm_result));
    }
    else if (dxl_error != 0)
    {
        printf("%s\n", packetHandler->getRxPacketError(dxl_error));
    }
    else
    {
        printf("Dynamixel has been successfully connected \n");
    }

    auto start_async = std::chrono::steady_clock::now();
    // Write Dynamixel
    dxl_comm_result = packetHandler->write4ByteTxOnly(
        portHandler,
        0,
        ADDR_MX_GOAL_POSITION,
        2500);

    dxl_comm_result = packetHandler->write4ByteTxOnly(
        portHandler,
        1,
        ADDR_MX_GOAL_POSITION,
        2500);
    auto end_async = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds_async = end_async - start_async;
    std::cout << "\n \n Elapsed time: " << std::chrono::duration<double, std::milli>(elapsed_seconds_async).count() << "s\n";

    if (dxl_comm_result != 0)
    {
        printf("%s\n", packetHandler->getTxRxResult(dxl_comm_result));
    }
    else if (dxl_error != 0)
    {
        printf("%s\n", packetHandler->getRxPacketError(dxl_error));
    }
    // 4 bytes data
    int data = 4000;
    bool dxl_addparam_result = false;

    uint8_t param_goal_position[4] = {DXL_LOBYTE(DXL_LOWORD(data)), DXL_HIBYTE(DXL_LOWORD(data)), DXL_LOBYTE(DXL_HIWORD(data)), DXL_HIBYTE(DXL_HIWORD(data))};
    dxl_addparam_result = groupSyncWrite.addParam(0, param_goal_position);
    if (dxl_addparam_result != true)
    {
        // fprintf(stderr, "[ID:%03d] groupSyncWrite addparam failed", 0);
        return 0;
    }

    dxl_addparam_result = groupSyncWrite.addParam(1, param_goal_position);
    if (dxl_addparam_result != true)
    {
        // fprintf(stderr, "[ID:%03d] groupSyncWrite addparam failed", 1);
        return 0;
    }

    // Syncwrite goal position
    auto start_sync = std::chrono::steady_clock::now();
    dxl_comm_result = groupSyncWrite.txPacket();
    if (dxl_comm_result != COMM_SUCCESS)
        printf("%s\n", packetHandler->getTxRxResult(dxl_comm_result));

    // Clear syncwrite parameter storage
    auto end_sync = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds_sync = end_sync - start_sync;
    std::cout << "\n \n Sync Elapsed time WRITE: " << std::chrono::duration<double, std::milli>(elapsed_seconds_sync).count() << "s\n";

    groupSyncWrite.clearParam();

    /**
     * @brief
     *  READ
     */

    auto start_async_read = std::chrono::steady_clock::now();
    int read_data = 0;
    uint32_t data_read_1 = 0;
    uint32_t data_read_2 = 0;
    // uint8_t error = 0;

    read_data = packetHandler->read4ByteTxRx(portHandler, 0, ADDR_MX_PRESENT_POSITION, &data_read_1);
    // std::cout << "\n ID 0, Present Position : " << data_read_1 << '\n';

    read_data = packetHandler->read4ByteTxRx(portHandler, 1, ADDR_MX_PRESENT_POSITION, &data_read_2);
    if (read_data)
    {
    }

    // std::cout << "\n ID 1, Present Position : " << data_read_2 << '\n';
    auto end_async_read = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds_async_read = end_async_read - start_async_read;
    std::cout << "\n \n READ Elapsed time: " << std::chrono::duration<double>(elapsed_seconds_async_read).count() << "s\n";

    auto start_bulk_read = std::chrono::steady_clock::now();
    
    // AFTER AN OBJECT IS CREATED 

    // ADD PARAMETER using  <ID< ADDRESS, LENGTH_OF_ADDRESS>
    dxl_addparam_result = groupBulkRead.addParam(0, ADDR_MX_PRESENT_POSITION, LEN_MX_PRESENT_POSITION);
    if (dxl_addparam_result != true)
    {
        fprintf(stderr, "[ID:%03d] grouBulkRead addparam failed", 0);
        return 0;
    }

    // Add parameter storage for Dynamixel#2 present moving value
    dxl_addparam_result = groupBulkRead.addParam(1, ADDR_MX_PRESENT_POSITION, LEN_MX_PRESENT_POSITION);
    if (dxl_addparam_result != true)
    {
        fprintf(stderr, "[ID:%03d] grouBulkRead addparam failed", 1);
        return 0;
    }

    //AFTER ADDDING PARAMETER READ DATA
    dxl_comm_result = groupBulkRead.txRxPacket();
      if (dxl_comm_result != COMM_SUCCESS)
      {
        printf("%s\n", packetHandler->getTxRxResult(dxl_comm_result));
      }
      else if (groupBulkRead.getError(0, &dxl_error))
      {
        printf("[ID:%03d] %s\n", 0, packetHandler->getRxPacketError(dxl_error));
      }
      else if (groupBulkRead.getError(1, &dxl_error))
      {
        printf("[ID:%03d] %s\n", 1, packetHandler->getRxPacketError(dxl_error));
      }

    // Check if AVAILABLE FIRST and then READ
    // Get Dynamixel#1 present position value
    int dxl1_present_position = groupBulkRead.getData(0, ADDR_MX_PRESENT_POSITION, LEN_MX_PRESENT_POSITION);

      // Get Dynamixel#2 moving status value
    int dxl2_present_position = groupBulkRead.getData(1, ADDR_MX_PRESENT_POSITION, LEN_MX_PRESENT_POSITION);


    //SAVE DATA AND PRINT.
    if(1==0)
    printf("[ID:%03d] Present Position : %d \t [ID:%03d] Is Moving : %d\n", 0, dxl1_present_position, 1, dxl2_present_position);

    auto end_bulk_read = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds_bulk_read = end_bulk_read - start_bulk_read;
    std::cout << "\n \n Elapsed  BULK Read time: " << std::chrono::duration<double>(elapsed_seconds_bulk_read).count() << "s\n";

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "\n \n Elapsed time: " << std::chrono::duration<double>(elapsed_seconds).count() << "s\n";

    return 0;
}
