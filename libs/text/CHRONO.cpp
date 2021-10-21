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


int main(int argc, char const *argv[]) {
    auto start = std::chrono::steady_clock::now();
    std::vector<std::string> key = {"a", "b", "c"};
    std::vector<std::string> keyss = {"d", "e", "f"};
    std::vector<std::pair<std::string,std::string>> key_pairsss;

    std::vector<float> value = {1, 2, 3};
    std::vector<float> value2 = {1, 2, 3};

    std::vector<std::string> names = {"one", "two", "three"};

    
    
    std::map<std::pair<std::string,std::string>, float> new_map;
    std::map<std::pair<std::string,std::string>, std::string> new_map2;
    
    for (auto k: key) {
        std::cout << k << " " << "\n";
    }

    //Make  Pair of Keys
    std::transform(std::begin(key), std::end(key), std::begin(keyss), std::inserter(key_pairsss, std::begin(key_pairsss)),
                   [](std::string key, std::string keyss) { return std::make_pair(key, keyss); });

    //make map of pair as key and value
    std::transform(std::begin(key_pairsss), std::end(key_pairsss), std::begin(value), std::inserter(new_map, std::begin(new_map)),
                   [](std::pair<std::string,std::string> pair,  float value) { return std::make_pair(pair, value); });

    std::transform(std::begin(key_pairsss), std::end(key_pairsss), std::begin(names), std::inserter(new_map2, std::begin(new_map2)),
                   [](std::pair<std::string,std::string> pair,  std::string value) { return std::make_pair(pair, value); });


    for (auto mi: new_map) {
        std::cout <<"{ "<< mi.first.first <<", "<<mi.first.second<<" }"<< " : " << mi.second << '\n';
    }

    std::cout << "\n";

    for (auto mi: new_map2) {
        std::cout <<"{ "<< mi.first.first <<", "<<mi.first.second<<" }"<< " : " << mi.second << '\n';
    }

    // const auto& it = new_map2::iterator; 


/**
 * @brief 
 * 1. Search if name in vector
 * 2. Get key based on Value of string 
 * 3. Search another map based on this key Value
 * 4. CRoss match incoming value 
 */
     
    //  for(auto it = )
    // const auto& m1 = new_map.find(std::make_pair("c","f"));
    // const auto& m2 = new_map2.find(std::make_pair("c", "f"));
    // if(m1!= new_map.end() && m2 != new_map2.end() && new_map2.size() == new_map.size()){
    //     if(m1->second == m2->second){
    //     std::cout <<  << m1->second << " == " << m2->second <<'\n';
        
    //     std::cout << "FOUND"; 
    //     }
    // }
    // else {
    //     std::cout << "Not Found OR Size Mismatch" ;
    // }



    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "elapsed time: " << std::chrono::duration <double, std::milli> (elapsed_seconds).count() << "s\n";
    return 0;
}