#include <iostream>
#include <nlohmann/json.hpp>

#include "frontend.hpp"
#include <chrono>



//todo generate string ID for each string stored
//todo stringify and parse json to save data
int main()
{
	for (int i = 0; i < 100; i++) {
		std::cout << time_stamp() << std::endl;
	}
}
