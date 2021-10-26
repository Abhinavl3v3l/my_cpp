/*
Copyright (c) 2018, NVIDIA CORPORATION. All rights reserved.

NVIDIA CORPORATION and its licensors retain all intellectual property
and proprietary rights in and to this software, related documentation
and any modifications thereto. Any use, reproduction, disclosure or
distribution of this software and related documentation without an express
license agreement from NVIDIA CORPORATION is strictly prohibited.
*/
#include "Dynamixel.hpp"

#include <string>
#include <vector>

#include "dynamixel_sdk.h"
#include "engine/core/logger.hpp"
#include "genesis/components/actuators/dynamixel/Registers.hpp"

namespace genesis {
namespace dynamixel {

namespace {
// TODO(cdelaunay) Fixed profile values - should be variable
constexpr int kDynamixelMaxSpeed = 100;
constexpr int kDynamixelProfileSpeed = 100;
constexpr int kDynamixelProfileAcceleration = 100;
constexpr int kMaxNumberDynamixelOnBus = 253;

// Checks for the two error status reported by the dynamixel library
bool Success(::dynamixel::PacketHandler* handler, int dxl_comm_result, uint8_t dxl_error) {
    if (dxl_comm_result != COMM_SUCCESS) {
        // LOG_DEBUG("1");
        // LOG_ERROR("Dynamixel error (%d): %s", dxl_comm_result,
        //           handler->getRxPacketError(dxl_comm_result));
        return false;
    }

    if (dxl_error != 0) {
        // LOG_DEBUG("2");
        // LOG_ERROR("Dynamixel error (%d): %s", dxl_error, handler->getRxPacketError(dxl_error));
        return false;
    }
    return true;
}
}  // namespace

Dynamixel::Dynamixel(const std::string& port_name, Baudrate baudrate, Model model) {
    model_ = model;
    const float protocol = GetProtocol(model);
    packet_handler_ = ::dynamixel::PacketHandler::getPacketHandler(protocol);
    // LOG_DEBUG("PacketHandler's Protocol Version %f", packet_handler_->getProtocolVersion());
    port_handler_ = ::dynamixel::PortHandler::getPortHandler(port_name.c_str());
    ::dynamixel::dynamixel::GroupBulkRead groupBulkRead(port_handler_, packet_handler_);
    if (!port_handler_->openPort()) {
        LOG_ERROR("Cannot open port %s: %s [errno %d]", port_name.c_str(), strerror(errno), errno);
        return;
    }
    map_ = InitRegisters(model);
    if (baudrate == Baudrate::kInvalid) {
        LOG_ERROR("Invalid baudrate! Setting default to 57600");
        baudrate = Baudrate::k57600;
    }
    const int baudrate_int = GetBaudrateValue(baudrate);
    if (!port_handler_->setBaudRate(baudrate_int)) {
        // LOG_ERROR("Failed to set the baud rate to %d", baudrate_int);
    } else {
        // LOG_DEBUG("BAUDRATE set to  %d", baudrate_int);
    }
}

void Dynamixel::scan() const {
    uint8_t dxl_error;
    uint16_t dxl_model_num;
    for (int id = 1; id < kMaxNumberDynamixelOnBus; id++) {
        if (packet_handler_->ping(port_handler_, id, &dxl_model_num, &dxl_error) == COMM_SUCCESS) {
            // LOG_INFO(" [ID:%.3d] Model No : %.5d", id, dxl_model_num);
        }
    }
}

double Dynamixel::getTicksToAngle(int ticks) const {
    return TicksToAngle(model_, ticks);
}

int Dynamixel::getAngleToTicks(double angle) const {
    return AngleToTicks(model_, angle);
}

double Dynamixel::getTicksToAngularSpeed(int ticks) const {
    auto search = map_.find(RegisterKey::MOVING_SPEED);
    ASSERT(search != map_.end(), "Servo doesn't support MOVING_SPEED");
    return TicksToAngularSpeed(model_, ticks);
}

int Dynamixel::getAngularSpeedToTicks(double angular_speed) const {
    auto search = map_.find(RegisterKey::MOVING_SPEED);
    ASSERT(search != map_.end(), "Servo doesn't support MOVING_SPEED");
    int ticks = AngularSpeedToTicks(model_, angular_speed);
    return ticks;
}

bool Dynamixel::setControlMode(uint8_t servo, DynamixelMode control_mode) {
    bool success = false;
    // Data in the EEPROM Area can only be written to if Torque Enable(64) is cleared to ‘0’(Off)
    success = writeRegister(servo, RegisterKey::TORQUE_ENABLE, 0);
    if (control_mode == DynamixelMode::kPosition) {
        // LOG_DEBUG("Switching PanTiltDriver control mode to: POSITION");
        // set position control mode
        success = writeRegister(servo, RegisterKey::OPERATING_MODE, 3);
        // max speed for internal PID
        success &=
            writeRegister(servo, RegisterKey::VELOCITY_VALUE_OF_PROFILE, kDynamixelProfileSpeed);
    } else if (control_mode == kVelocity) {
        // LOG_DEBUG("Switching PanTiltDriver control mode to: SPEED");
        success = writeRegister(servo, RegisterKey::OPERATING_MODE, 1);
        // max acceleration for internal PID
        success &= writeRegister(servo, RegisterKey::ACCELERATION_VALUE_OF_PROFILE,
                                 kDynamixelProfileAcceleration);
    } else {
        // LOG_WARNING("Control mode %d is not implemented", control_mode);
        return false;
    }
    // Data in the EEPROM Area can only be written to if Torque Enable(64) is cleared to ‘0’(Off)
    success &= writeRegister(servo, RegisterKey::TORQUE_ENABLE, 1);
    return success;
}

bool Dynamixel::writeRegister(uint8_t servo, const RegisterKey& key, int value) {
    int dxl_comm_result = COMM_SUCCESS;
    auto search = map_.find(key);
    if (search == map_.end()) {
        return false;
    }

    const ServoRegister servo_register = search->second;
    switch (servo_register.size) {
        case 1:
            // LOG_DEBUG("VALUE COMING %d FROM DRIVER IS %i", servo, value);
            // dxl_comm_result = packet_handler_->write1ByteTxRx(
            //                   port_handler_, servo, servo_register.address, value, &status_);

            dxl_comm_result = packet_handler_->write1ByteTxOnly(port_handler_, servo,
                                                                servo_register.address, value);

            break;
        case 2:
            // LOG_DEBUG("FOR SERVO %d VALUE COMING FROM DRIVER IS %i", servo, value);
            // dxl_comm_result = packet_handler_->write2ByteTxRx(
            //                   port_handler_, servo, servo_register.address, value, &status_);

            dxl_comm_result = packet_handler_->write2ByteTxOnly(port_handler_, servo,
                                                                servo_register.address, value);
            break;
        case 4:
            // LOG_DEBUG("FOR SERVO %d VALUE COMING FROM DRIVER IS %i", servo, value);
            dxl_comm_result = packet_handler_->write4ByteTxRx(
                port_handler_, servo, servo_register.address, value, &status_);
            // dxl_comm_result = packet_handler_->write4ByteTxOnly(
            //                   port_handler_, servo, servo_register.address, value);
            break;
        default:
            // LOG_ERROR("Invalid size %d", servo_register.size);
            return false;
    }
    if (!Success(packet_handler_, dxl_comm_result, status_)) {
        // LOG_DEBUG("Error while writing register %d", key);
        return false;
    }

    return true;
}

int Dynamixel::readRegister(uint8_t servo, const RegisterKey& key) {
    int dxl_comm_result = COMM_SUCCESS;
    int res = 0;
    auto search = map_.find(key);
    if (search == map_.end()) {
        return 0;
    }
    const ServoRegister servo_register = search->second;
    switch (servo_register.size) {
        case 1:
            uint8_t value8;
            dxl_comm_result = packet_handler_->read1ByteTxRx(
                port_handler_, servo, servo_register.address, &value8, &status_);
            // dxl_comm_result = packet_handler_->read1ByteRx(
            //                   port_handler_, servo, servo_register.address, &value8, &status_);
            res = value8;
            break;
        case 2:
            uint16_t value16;
            dxl_comm_result = packet_handler_->read2ByteTxRx(
                port_handler_, servo, servo_register.address, &value16, &status_);
            res = value16;
            break;
        case 4:
            uint32_t value32;
            dxl_comm_result = packet_handler_->read4ByteTxRx(
                port_handler_, servo, servo_register.address, &value32, &status_);
            res = value32;
            break;
        default:
            LOG_ERROR("Invalid size %d", servo_register.size);
            return 0;
    }
    if (!Success(packet_handler_, dxl_comm_result, status_)) {
        // LOG_ERROR("Error while reading register %d", key);
        // LOG_DEBUG("Error while reading register %d", key);
        return 0;
    }
    return res;
}

void bulkReadRegister(std::vector<GroupBulk> groupRead) {
    for (auto& servo : groupRead) {
        int dxl_comm_result = COMM_SUCCESS;
        int res = 0;
        auto search = map_.find(servo._rkey);
        if (search == map_.end()) {
            return 0;
        }
        const ServoRegister servo_register = search->second;
    }
}

byte Dynamixel::getStatus() const {
    return status_;
}

}  // namespace dynamixel
}  // namespace genesis
