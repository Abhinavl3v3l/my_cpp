#include <iostream>
#include <vector>
#include <iterator>
// #include "libs/helloworld.hpp"
// #include "libs/enum_test.hpp"
// #include "libs/MaestroDevice.hpp"
// unsigned int microsecond = 1000000;

#include<unistd.h>

int main(int argc, char const *argv[])
{

std::vector<std::string> links;
for (int i = 0;i< 13;i++) {links.push_back(std::to_string(i));}



std::cout << links(0);

  return 0;
}
