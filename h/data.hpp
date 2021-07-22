#pragma once

#include <array>
#include <string>
#include <stdint.h>

#include <SSS/commons.hpp>
#include <nlohmann/json.hpp>



class Evaluation : public std::array<uint16_t, 5>
{
public :
	Evaluation();
	Evaluation(const std::array<uint16_t, 5>& init_array);

	//OPERATOR OVERLOAD
	Evaluation operator=(std::array<uint16_t, 5> assign_array) {
		for (rsize_t i = 0; i < 5; i++) {
			at(i) = assign_array[i];
		}
		return *this;
	}
	Evaluation operator=(std::vector<uint16_t> assign_array) {
		for (rsize_t i = 0; i < 5; i++) {
			at(i) = assign_array[i];
		}
		return *this;
	}

	//METHOD FOR DATA COMPARISON
	float average() const;
	uint32_t count() const;

	
};


struct traduction_data {
	std::string trad_ID;
	uint32_t language;
	bool mother_file = 0;
};


struct user_data {
	std::string user_ID;
	std::array<unsigned int, 3> languages;
	Evaluation user_eval;
	uint32_t trad_qty;
};

struct text_data {
public :
	std::string text_ID;
	std::string text;
	std::string comment;
	uint32_t language = 0;
	Evaluation text_eval;

	//CONVERSION
	static void to_json(nlohmann::json& file_dst, const text_data& data_src);
	static void from_json(text_data& data_dst, const nlohmann::json& file_src);
	
	//LOG
	std::string print_data();
};
