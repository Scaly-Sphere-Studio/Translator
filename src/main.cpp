#include <iostream>
#include <nlohmann/json.hpp>

#include "frontend.hpp"
#include "backend.hpp"



void parse_traduction_json(const Traduction_data& src_trad_data, const std::vector<Text_data>& src_txt_data, const std::string& file_path) 
{
	nlohmann::json dst;
	

};


int main()
{
	//Check if the folder traduction exist and create/update the file in it
	//std::string folder = "traduction";
	//if (!check_folder_exists(folder)) {
	//	create_folder(folder);
	//}
	//std::filesystem::current_path(folder);
	
	Traduction_data test_trad;
	std::vector<nlohmann::json> j_vec;
	std::vector<Text_data> t_data;

	
	std::ifstream ifs("trad.json");
	nlohmann::json j;

	ifs >> j;
	std::cout << j << std::endl;

	std::vector<nlohmann::json> parsed;
	j.at("data").get_to(parsed);

	for (nlohmann::json json : parsed) {
		std::cout << json << std::endl;
	}
	//Create an array of data
	parse_traduction_json(test_trad, t_data, "trad.json");


	/*text_data text;
	text.text_ID = "id_test01";
	text.text = "this is the text for the trad";
	text.comment = "petit test ?";
	text.language = 0;
	text.text_eval = std::array<uint16_t, 5>{ 25,0,35,84,125 };
	
	nlohmann::json test;
	test["text"] = text.text;
	test["id"] = text.text_ID;
	test["comment"] = text.comment;
	test["language"] = text.language;
	test["evaluation"] = text.text_eval;
	o << std::setw(4) << test << std::endl;*/

	return 0;
}
