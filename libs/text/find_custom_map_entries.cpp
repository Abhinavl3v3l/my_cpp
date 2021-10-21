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

#include "libs/nlohmann/json.hpp"


int main(int argc, char const *argv[]) {
    std::vector<std::string> key = {"a", "b", "c"};
    std::vector<std::string> keyss = {"d", "e", "f"};
    std::vector<std::pair<std::string,std::string>> key_pairsss;

    std::vector<float> value = {1, 2, 30};
    std::vector<float> zero(value.size(),0);
    std::vector<float> ten(value.size(),10);
    
    
    std::map<std::pair<std::string,std::string>, float> new_map;
    
    for (auto k: key) {
        std::cout << k << " " << "\n";
    }

    //Make  Pair of Keys
    std::transform(std::begin(key), std::end(key), std::begin(keyss), std::inserter(key_pairsss, std::begin(key_pairsss)),
                   [](std::string key, std::string keyss) { return std::make_pair(key, keyss); });

    //make map of pair as key and value
    std::transform(std::begin(key_pairsss), std::end(key_pairsss), std::begin(value), std::inserter(new_map, std::begin(new_map)),
                   [](std::pair<std::string,std::string> pair,  float value) { return std::make_pair(pair, value); });


    for (auto mi: new_map) {
        std::cout <<"{ "<< mi.first.first <<", "<<mi.first.second<<" }"<< " : " << mi.second << '\n';
    }


    const auto& f = new_map.find(std::make_pair("c","f"));
    if(f!= new_map.end()){
    std::cout << f->second ;
    }
    else {
        std::cout << "Not Found" ;
    }


    
    return 0;
}