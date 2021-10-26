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
#include "libs/nlohmann/json.hpp"
// #include "dynamixel.hpp"

class BulkOperation
{
public:
private:
	unsigned int id;
};

void fun(std::vector<int> &v)
{//SAVE
	for (auto& it: v)
	{
		it = it +1;
	}
}

void fun2(std::vector<int> &v)
{//SAVE
	for (auto& it: v)
	{
		it = it -1;
	}
}

int main(int argc, char const *argv[])
{
	auto start = std::chrono::steady_clock::now();

	std::vector<int> servo_id = {0, 1, 2, 3, 4, 5, 6, 7};

	// dynamixel bulk read
	/**
	 * 	1. A function that expects list of objects containing info
	 *  	as what id, register and size of register to read.
	 * 	2. Dynamixel Driver should loop through objects and get
	 * 		necessary properties to add param
	 * 	3. Then read from dynamixel
	 * 	4. Save the read data to the object
	 *
	 */
	for (auto &it : servo_id)
	{
		std::cout << " " << it ;
	}
	fun(servo_id); // INSTEAD OF PASSING IT VIA REF LET LOOP in line 30 and 38 be looped by ref :)
	std::cout << "\n" ;
	for (auto &it : servo_id)
	{
		std::cout << " " << it ;
	}
	fun2(servo_id); 
	std::cout << "\n" ;

	for (auto &it : servo_id)
	{
		std::cout << " " << it ;
	}
	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	std::cout << "\n \n Elapsed time: " << std::chrono::duration<double>(elapsed_seconds).count() << "s\n";

	return 0;
}
