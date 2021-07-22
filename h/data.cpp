#include "data.hpp"


Evaluation::Evaluation()
{
	fill(0);
}

Evaluation::Evaluation(const std::array<uint16_t, 5>& init_array)
{
	*this = init_array;
}

float Evaluation::average() const
{
	float count = 0, mean = 0;
	for (float i = 0; i < 5; i++) {
		count += this->at(i);
		mean += (i+1) * this->at(i);
	}

	return mean / count;
}

uint32_t  Evaluation::count() const
{
	uint32_t count = 0;
	for (float i = 0; i < 5; i++) {
		count += this->at(i);
	}

	return count;
}

void text_data::to_json(nlohmann::json& file_dst, const text_data& data_src)
{
	file_dst = nlohmann::json{
		{"id", data_src.text_ID},
		{"text", data_src.text},
		{"comment", data_src.comment},
		{"language", data_src.language},
		{"evaluation", data_src.text_eval}
	};
}

void text_data::from_json(text_data& data_dst, const nlohmann::json& file_src)
{
	file_src.at("id").get_to(data_dst.text_ID);
	file_src.at("text").get_to(data_dst.text);
	file_src.at("comment").get_to(data_dst.comment);
	file_src.at("language").get_to(data_dst.language);
	file_src.at("evaluation")
		.get_to(static_cast<std::array<uint16_t, 5>&>(data_dst.text_eval));
}

std::string text_data::print_data()
{
	std::string tmp_string;
	tmp_string += "ID : " + text_ID;
	tmp_string += "; text : " + text;
	tmp_string += "; comment : " + comment;
	tmp_string += "; langue : " + SSS::toString(language);
	tmp_string += "; Evaluation : [";
	for (size_t i = 0; i < 5; i++) {
		tmp_string += SSS::toString(text_eval[i]) + ",";
	}
	tmp_string += "]";

	return tmp_string;
}
