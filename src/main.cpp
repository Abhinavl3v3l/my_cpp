#include <iostream>
// #include "libs/helloworld.hpp"
// #include "libs/enum_test.hpp"


// #define PKT_HEADER0 0
// #define PKT_HEADER1 1
// #define PKT_ID 2
// #define PKT_LENGTH 3
// #define PKT_INSTRUCTION 4
// #define PKT_ERROR 4
// #define PKT_PARAMETER0 5


// /*Instruction for dxl protocol*/
// #define INST_PING               1
// #define INST_READ               2
// #define INST_WRITE              3
// #define INST_REG_WRITE          4
// #define INST_ACTION             5



template <typename T>
void foo(T i)
{
    std::cout << " __func__  " << __func__ << std::endl;
    std::cout << "__FUNCTION__   " << __FUNCTION__ << std::endl;
    std::cout << "__PRETTY_FUNCTION__  " << __PRETTY_FUNCTION__ << std::endl << std::endl;
}
int main(int argc, char const *argv[])
{
    // Working o;
    std::cout << "*** STARTS HERE ***"
              << "\n\n\n";

    // uint16_t address = 30;
    // uint16_t length = 1;
    // unsigned int val = 2048;
    // uint8_t data[1] = {val}
    // uint8_t *txpacket = (uint8_t *)malloc(length + 7);

    // txpacket[PKT_ID] = 3;
    // txpacket[PKT_LENGTH] = length + 3;
    // txpacket[PKT_INSTRUCTION] = 3;
    // txpacket[PKT_PARAMETER0] = (uint8_t)address;

    // for (uint16_t s = 0; s < length; s++){
    //     std::cout << "" << std::endl;
    //     txpacket[PKT_PARAMETER0 + 1 + s] = data[s];
    // }

    // std::cout  << "TxPacket Contents" <<std::endl;
    // for (uint8_t i = 0; i < length + 7; i++)
    // {
    //     std::cout << txpacket[i];
    // }
    // uint8_t val = 2000;
    // uint8_t data[1] = {val};
    // std::cout  << "Val  2000" << data[1] <<std::endl;
    // std::cout << __PRETTY_FUNCTION__ <std::endl;
    foo<int>(10);
    foo<float>(3.14);
    return 0;
}
