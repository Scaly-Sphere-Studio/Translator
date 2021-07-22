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
	std::vector<nlohmann::json> j_vec;
	std::vector<text_data> t_data;
	//std::filesystem::current_path(folder);
	std::ifstream ifs("trad.json");
	nlohmann::json j;
	
	unsigned int djks = 0;
	ifs >> j;
	j_vec.emplace_back(j);


	std::cout << "SIZE : " << j_vec.size() << std::endl;
	text_data t;
	for (size_t i = 0; i < j_vec.size(); i++) {
		text_data::from_json(t, j_vec[i]);
		t_data.emplace_back(t);
	}
	for (size_t i = 0; i < j_vec.size(); i++) {
		std::cout << SSS::toString(j_vec[i]) << std::endl;
		std::cout << t_data[i].print_data() << std::endl;
	}
	

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
