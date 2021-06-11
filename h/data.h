#pragma once
#include <array>

struct text_data {
public :
	std::string text;
	std::string user;
	std::string comment;
	unsigned int language = 0;
	std::array<unsigned int, 5> evaluation{ 0 };
};
