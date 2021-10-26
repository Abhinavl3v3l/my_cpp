
#pragma once

#include <iostream>
#include <string>
namespace genesis {
namespace pololu {
enum class Type {
    INVALID = -1,
    MICRO_6 = 0,
    MINI_12 = 1,
    MINI_18 = 2,
    MINI_24 = 3,
};
enum class Protocol { INVALID = -1, COMPACT = 0, POLOLU = 1, MINI_SSC = 2 };

class MaestroConfig {
   public:
    MaestroConfig(Type type,
                  Protocol protocol,
                  std::string device_file,
                  unsigned char device_number)
        : type_(type),
          protocol_(protocol),
          device_file_(device_file),
          device_number_(device_number){};

    MaestroConfig()
        : type_(Type::MINI_12),
          protocol_(Protocol::POLOLU),
          device_file_("/dev/ttyACM0"),
          device_number_(0x0C){};

    virtual ~MaestroConfig(){};
    // Returns type of pololu board
    Type getType() { return type_; }
    // Returns the pololu board assigned. For more info https://www.pololu.com/docs/0J40/5.c
    Protocol getProtocol() { return protocol_; }
    // Usb device port used
    std::string getDeviceFile() { return device_file_; }
    // Returns device number, default and in most cases 12.
    unsigned char getDeviceNumber() { return device_number_; }

   private:
    Type type_;
    Protocol protocol_;
    std::string device_file_;
    unsigned char device_number_;
};

}  // namespace pololu
}  // namespace genesis
