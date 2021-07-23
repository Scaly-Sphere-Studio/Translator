#pragma once

#include <iostream>
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
	friend std::ostream &operator<<(std::ostream& output, const Evaluation& eval) {
		output << "["
			<< eval.at(0) << "," 
			<< eval.at(1) << "," 
			<< eval.at(2) << "," 
			<< eval.at(3) << "," 
			<< eval.at(4) << "]";
		return output;
	}

	//METHOD FOR DATA COMPARISON
	float average() const;
	uint32_t count() const;

	
};


struct User_data {
	std::string user_ID;
	std::array<unsigned int, 3> languages;
	Evaluation user_eval;
	uint32_t trad_qty;
};

struct Text_data {
public :
	std::string text_ID;
	std::string text;
	std::string comment;
	Evaluation text_eval;

	friend std::ostream& operator<<(std::ostream& output, const Text_data& txt) {
		output << "[ID]:" << txt.text_ID <<
			", [TEXT]:" << txt.text;
		return output;
	}
	//CONVERSION
	static nlohmann::json to_json(const Text_data& data_src);
	static Text_data from_json(const nlohmann::json& file_src);
	
	//LOG
	std::string print_data();
};

struct Traduction_data {
	std::string trad_ID;
	uint32_t language = 0;
	bool mother_file = 0;
	float trad_evaluation = 0.0f;
	std::vector<Text_data> text_data;

	friend std::ostream& operator<<(std::ostream& output, const Traduction_data& trad) {
		output << "[TRAD_ID]:" << trad.trad_ID <<
			", [LANGUAGE]:" << trad.language;
		if (trad.mother_file) {
			output << ", [MOTHER_FILE]" << std::endl;
		}

		for (Text_data txt : trad.text_data) {
			output << txt << std::endl;
		}
		return output;
	}

	nlohmann::json parse_traduction_data_to_json();
};
