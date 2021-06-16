#include <iostream>
#include <nlohmann/json.hpp>

#include "frontend.hpp"

int main()
{

	std::string folder = "traduction";
	if (!check_folder_exists(folder)) {
		create_folder(folder);
	}

	return 0;
}
