/*
Copyright (c) 2018, NVIDIA CORPORATION. All rights reserved.

NVIDIA CORPORATION and its licensors retain all intellectual property
and proprietary rights in and to this software, related documentation
and any modifications thereto. Any use, reproduction, disclosure or
distribution of this software and related documentation without an express
license agreement from NVIDIA CORPORATION is strictly prohibited.
*/
#pragma once

#include <map>
#include <string>

#include "engine/core/byte.hpp"
#include "engine/core/logger.hpp"
#include "genesis/components/actuators/dynamixel/Registers.hpp"
#include "genesis/components/components/misc/bulk_operation_dxl/groupBulk.hpp"

using namespace isaac;
namespace dynamixel {
class PacketHandler;
class PortHandler;
}  // namespace dynamixel

namespace genesis {
namespace dynamixel {

enum DynamixelMode {
    // Position control
    kPosition = 0,
    // Velocity control
    kVelocity = 1,
    // Invalid
    kInvalid = -1
};

// A class that connects to a dynamixel port and allows servos actuation
class Dynamixel {
   public:
    // Creates a Serial Bus handler for a particular kind of dynamixel
    Dynamixel(const std::string& port_name, Baudrate baudarte, Model model);
    // Writes a value to a particular address
    bool writeRegister(uint8_t servo, const RegisterKey& key, int value);
    // Reads a value to a particular address
    int readRegister(uint8_t servo, const RegisterKey& key);
    // Sets the control mode
    bool setControlMode(uint8_t servo, DynamixelMode mode);
    // Converts a dynamixel joint position to the corresponding angle in radians.
    double getTicksToAngle(int ticks) const;
    // Inverse of TicksToAngle
    int getAngleToTicks(double angle) const;
    // Converts a dynamixel joint speed to the corresponding angular speed in radians per second.
    int getAngularSpeedToTicks(double angular_speed) const;
    // Inverse of TicksToSpeed
    double getTicksToAngularSpeed(int ticks) const;
    // Returns hardware status byte
    byte getStatus() const;
    // Scans for available servo on the bus
    void scan() const;

    /**
     * @brief 
     * MachaniRobotics 
     * 1. Bulk Read 
     * 2. Bulk Write
     */
    void bulkReadRegister(std::vector<genesis::GroupBulk>);


   private:
    // Register map that will be populated depending on the servo model
    std::map<RegisterKey, ServoRegister> map_;
    // Dynamixel API pointers to handle communication to the bus
    ::dynamixel::PacketHandler* packet_handler_;
    ::dynamixel::PortHandler* port_handler_;
    // Model of the dynamixel
    Model model_;
    // Dynamixel status
    byte status_ = kStatusOk;
};

}  // namespace dynamixel
}  // namespace genesis
