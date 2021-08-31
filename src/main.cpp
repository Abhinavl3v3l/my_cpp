#include <iostream>
#include <vector>
#include <string>
#include <typeinfo>
#include <numeric>
#include <algorithm>
#include <typeinfo>
#include <bits/stdc++.h>



int main(int argc, char const *argv[])
{	
	std::vector<std::string> key = {"a","b","c"};
	std::vector<float> value = {1,2,3};
	std::map<std::string,float> new_map;
	for(auto k:key){
		std::cout  << k << " " << "\n";
	}

	std::transform(std::begin(key), std::end(key)
             , std::begin(value)
             , std::inserter(new_map, std::begin(new_map))
             , [] (std::string key, float value) { return std::make_pair(key, value); });

	std::map::iterator mi;
	for()
	return 0;
}