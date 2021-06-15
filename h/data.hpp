#pragma once

#include <array>
#include <string>


struct traduction_data {
	std::string trad_ID;
	unsigned int language;
	bool mother_file = 0;
};


struct user_data {
	std::string user_ID;
	std::array<unsigned int, 3> languages;
	std::array<unsigned int, 5> evaluation{ 0 };
	unsigned int trad_qty;
};

struct text_data {
	std::string text_ID;
	std::string text;
	std::string comment;
	unsigned int language = 0;
	std::array<unsigned int, 5> evaluation{ 0 };
};
