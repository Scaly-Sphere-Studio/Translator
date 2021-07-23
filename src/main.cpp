#include <iostream>
#include <nlohmann/json.hpp>

#include "frontend.hpp"
#include "backend.hpp"



void parse_traduction_data_to_json(const Traduction_data& src_trad_data, const std::vector<Text_data>& src_txt_data, const std::string& file_path) 
{


};


Text_data rng_data() {
	Text_data rng;
	rng.text_ID = time_stamp();
	rng.text = time_stamp();
	rng.comment = time_stamp();
	rng.text_eval = std::array<uint16_t, 5> {0, 1, 2, 3, 4};
	
	return rng;
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
	test_trad.language = 0;
	test_trad.mother_file = 1;
	test_trad.trad_ID = time_stamp();

	for (size_t i = 0; i < 100; i++) {
		test_trad.text_data.emplace_back(rng_data());
	}
	//
	////Create an array of data
	//export_data_json("trad.json", test_trad.parse_traduction_data_to_json());


	std::cout << test_trad;

	return 0;
}
