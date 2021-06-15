#include <iostream>
#include <nlohmann/json.hpp>

#include "frontend.hpp"

#include <Windows.h>
//#include <libloaderapi.h>



//todo generate string ID for each text data stored
//todo stringify and parse json to save data
int main()
{
	//char fileName[MAX_PATH];

	//GetModuleFileNameA(NULL, fileName, MAX_PATH);

	std::filesystem::path current_path = std::filesystem::current_path();

	std::fstream fs;
	fs.open("trad.json", std::fstream::in | std::fstream::out | std::fstream::trunc);
	/*fs << fileName << std::endl;*/

	std::filesystem::current_path(current_path.string() + "\\h");
	std::cout << "present path : " << std::filesystem::current_path() << std::endl;




	/*std::filesystem::current_path(path);
	std::cout << "present path : " << std::filesystem::current_path() << std::endl;*/
	fs.close();

	return 0;
}
