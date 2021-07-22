#include <iostream>
#include <nlohmann/json.hpp>

#include "frontend.hpp"
#include "backend.hpp"

int main()
{

	//std::string folder = "traduction";
	//if (!check_folder_exists(folder)) {
	//	create_folder(folder);
	//}

	//std::filesystem::current_path(folder);
	std::ofstream o("trad.json");
	

	text_data text;
	text.text_ID = "id_test01";
	text.text = "this is the text for the trad";
	text.comment = "petit test ?";
	text.language = 0;
	text.text_eval = std::array<uint16_t, 5>{ 25,0,35,84,125 };


	nlohmann::json test;
	test["id"] = text.text_ID;
	test["text"] = text.text;
	test["comment"] = text.comment;
	test["language"] = text.language;
	test["evaluation"] = text.text_eval;

	o << std::setw(4) << test << std::endl;

	return 0;
}
