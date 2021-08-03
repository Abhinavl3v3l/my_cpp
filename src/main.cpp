#include <iostream>
// #include "libs/helloworld.hpp"
// #include "libs/enum_test.hpp"
#include "libs/MaestroDevice.hpp"
unsigned int microsecond = 1000000;

#include<unistd.h>
using namespace pololu;

void init_h(MaestroDevice device){
  std::cout << "Init" <<std::endl;
  unsigned short inits = 1456 * 4;
  device.setTargetOnChannel(11, inits);
  device.setTargetOnChannel(12, inits);
  device.setTargetOnChannel(13, inits);
  device.setTargetOnChannel(14, inits);
  device.setTargetOnChannel(15, inits);
  device.setTargetOnChannel(16, inits);
  return;
}

int main(int argc, char const *argv[])
{
  std::cout << "***CODE ***" << std::endl;
  DeviceOptions config18_left;
  DeviceOptions config18_right;

  MaestroDevice device18_left;
  MaestroDevice device18_right;
  config18_left = DeviceOptions(DeviceOptions::Type::MINI_24, DeviceOptions::Protocol::POLOLU, "/dev/serial/by-id/usb-Pololu_Corporation_Pololu_Mini_Maestro_18-Channel_USB_Servo_Controller_00230614-if00", 12);
  config18_right = DeviceOptions(DeviceOptions::Type::MINI_18, DeviceOptions::Protocol::POLOLU, "/dev/serial/by-id/usb-Pololu_Corporation_Pololu_Mini_Maestro_18-Channel_USB_Servo_Controller_00230622-if00", 12);
  device18_left = MaestroDevice(config18_left);
  device18_right = MaestroDevice(config18_right);

  device18_left.connect();
  device18_right.connect();
  // unsigned short vals = 1800;

  unsigned short inits = 1456 * 4;
  // for(unsigned short j = 4000 ;j < 8000; j+= 500){
    
  //   device18_left.setTargetOnChannel(11, j);
  //    usleep(1 * microsecond); //sleep for 2 sec
  //     }//11
  device18_left.setTargetOnChannel(11, inits);
  // device18_left.setTargetOnChannel(12, inits); //12
  // device18_left.setTargetOnChannel(13, inits); //13
  // device18_left.setTargetOnChannel(14, inits); //14
  // device18_left.setTargetOnChannel(15, inits); //15
  // device18_left.setTargetOnChannel(16, inits); //16



  // device18_right.setTargetOnChannel(11, inits); //11
  //  for(unsigned short i = 4000 ;i < 8000; i= i + 500){
    
  device18_right.setTargetOnChannel(11, inits);
  //    usleep(1 * microsecond); //sleep for 2 sec
  //     }//11
  // device18_right.setTargetOnChannel(12, inits); //12
  // device18_right.setTargetOnChannel(13, inits); //13
  // device18_right.setTargetOnChannel(14, inits); //14
  // device18_right.setTargetOnChannel(15, inits); //15
  // device18_right.setTargetOnChannel(16, inits); //16

  // init_h(device18_left);
  // init_h(device18_right);

  u_short position = 0;
  device18_left.getPositionOnChannel(11,position);
  std::cout << "POSITION LEFT" << position << "\n"; 
  device18_right.getPositionOnChannel(11,position);
  std::cout << "POSITION RIGHT" << position << "\n";
  



  device18_left.disconnect();
  device18_right.disconnect();
  return 0;
}
