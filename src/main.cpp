#include <iostream>
#include <nlohmann/json.hpp>

#include "frontend.hpp"



//todo generate string ID for each text data stored
//todo stringify and parse json to save data
int main()
{
	std::fstream fs;
	fs.open("trad.json", std::fstream::in | std::fstream::out | std::fstream::app);
	fs << "petit test pour le json appendising" << std::endl;
	fs.close();
}
