#include <iostream>
#include <nlohmann/json.hpp>

#include "frontend.hpp"

int main()
{

	std::string folder = "traduction";
	if (!check_folder_exists(folder)) {
		create_folder(folder);
	}

	std::filesystem::current_path(folder);
	std::ofstream("trad.json");


	return 0;
}
