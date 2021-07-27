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
	
	return 0;
}
