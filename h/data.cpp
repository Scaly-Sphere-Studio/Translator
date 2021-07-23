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

nlohmann::json Text_data::to_json(const Text_data& data_src)
{
	nlohmann::json tmp;
	tmp = nlohmann::json{
		{"id", data_src.text_ID},
		{"text", data_src.text},
		{"comment", data_src.comment},
		{"evaluation", data_src.text_eval}
	};

	return tmp;
}

Text_data Text_data::from_json(const nlohmann::json& file_src)
{
	Text_data tmp_data;
	file_src.at("id").get_to(tmp_data.text_ID);
	file_src.at("text").get_to(tmp_data.text);
	file_src.at("comment").get_to(tmp_data.comment);
	file_src.at("evaluation")
		.get_to(static_cast<std::array<uint16_t, 5>&>(tmp_data.text_eval));

	return tmp_data;
}

std::string Text_data::print_data()
{
	std::string tmp_string;
	tmp_string += "ID : " + text_ID;
	tmp_string += "; text : " + text;
	tmp_string += "; comment : " + comment;
	tmp_string += "; Evaluation : [";
	for (size_t i = 0; i < 5; i++) {
		tmp_string += SSS::toString(text_eval[i]) + ",";
	}
	tmp_string += "]";

	return tmp_string;
}

nlohmann::json Traduction_data::parse_traduction_data_to_json()
{
	nlohmann::json dst;

	//Store a json objects array
	std::vector<nlohmann::json> j_data;
	j_data.reserve(text_data.size());

	//Fill the json objects array
	for (size_t i = 0; i < text_data.size(); i++) {
		j_data.emplace_back(Text_data::to_json(text_data[i]));
	}

	//Create the complete json object
	dst = nlohmann::json{
		{"_MOTHER_FILE", mother_file},
		{"_LANGUAGE", language},
		{"_TRADUCTION_ID", trad_ID},
		{"DATA", j_data}
	};

	return dst;
}
