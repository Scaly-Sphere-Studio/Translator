#pragma once

#include <array>
#include <string>
#include <stdint.h>

class Evaluation : std::array<uint16_t, 5>
{
public :
	Evaluation();
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
	std::string text_ID;
	std::string text;
	std::string comment;
	uint32_t language = 0;
	Evaluation text_eval;
};
