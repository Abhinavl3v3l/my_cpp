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

#include "libs/nlohmann/json.hpp"

void nameAssertion(std::vector<std::string> &namess, std::map<std::pair<int, std::string>, float> &init_map,
                   std::map<std::pair<int, std::string>, std::string> &name_map);
template <typename T>
bool compare(std::vector<T> v1, std::vector<T> v2);

int main(int argc, char const *argv[])
{
    // auto start = std::chrono::steady_clock::now();
    std::vector<int> id = {1, 2, 3};
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

    // //Map < KEY, POS >
    // std::transform(std::begin(joint_name),
    //                 std::end(joint_name),
    //                 std::begin(value),
    //                 std::inserter(init_map, std::begin(init_map)),
    //                [](std::pair<int,std::string> pair,  float value) { return std::make_pair(pair, value); }
    //                );

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

    /**
     * @brief
     * 1. Based on name  search for key
     * 2. Get key and search value
     * 3. Insert value for home
     */

    // if(compare(names,namess)) {
    //     nameAssertion(namess, init_map, name_map);
    // }else{
    //     std::cout << " NOT SAME" ;
    // }

    // auto end = std::chrono::steady_clock::now();
    // std::chrono::duration<double> elapsed_seconds = end-start;
    // std::cout << "\n \n Elapsed time: " << std::chrono::duration <double, std::milli> (elapsed_seconds).count() << "s\n";

    return 0;
}
template <typename T>
bool compare(std::vector<T> v1, std::vector<T> v2)
{
    std::vector<std::string> V1 = v1;
    std::vector<std::string> V2 = v2;

    std::sort(V1.begin(), V1.end());
    std::sort(V2.begin(), V2.end());
    return V1 == V2;
}
void nameAssertion(std::vector<std::string> &namess, std::map<std::pair<int, std::string>, float> &init_map,
                   std::map<std::pair<int, std::string>, std::string> &name_map)
{

    // Find init in InitMap, using NameMap keys
    //  init : Key :: Key : Name_config  == Name_entity
    // NameEntity is searched in NameConfig map, get key of this map
    for (std::vector<std::string>::iterator n = namess.begin(); n != namess.end(); n++)
    {
        std::cout << "\n Searching Name :" << *n << "\n";
        for (auto &nm : name_map)
        {
            if (nm.second == *n)
            {
                const auto &init_itr = init_map.find(nm.first);
                if (init_itr != init_map.end())
                {
                    std::cout << "\n"
                              << *n << " : Init_Map Value Search : " << init_itr->second << " : " << std::distance(namess.begin(), n);
                }
            }
        }
    }
}
