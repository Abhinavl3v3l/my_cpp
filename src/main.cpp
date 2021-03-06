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
{ // SAVE
	for (auto &it : v)
	{
		it = it + 1;
	}
}

void fun2(std::vector<int> &v)
{ // SAVE
	for (auto &it : v)
	{
		it = it - 1;
	}
}

int main(int argc, char const *argv[])
{
	auto start = std::chrono::steady_clock::now();

	std::vector<int> a ={0 ,2 ,2, 2, 4, 5 ,6 ,6 ,7, 6 };
	std::vector<int> b = {0 ,0, 1, 2, 3, 5, 5 ,6, 8, 9};
	std::vector<int> res;

	for (size_t i =0;i< a.size();i++)
	{
		std::cout << a[i] <<" " <<b[i]<< " ";
	}
	
	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	std::cout << "\n \n Elapsed time: " << std::chrono::duration<double>(elapsed_seconds).count() << "s\n";

	return 0;
}
