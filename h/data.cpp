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

float Traduction_data::mean_evaluation()
{
	float mean = 0;
	for (Text_data t : text_data) {
		mean += t.text_eval.average();
	}

	return mean / static_cast<float>(text_data.size());
}

void Traduction_data::print()
{
	std::cout << *this;
}

void Traduction_data::parse_traduction_data_to_json(const std::string& path)
{
	nlohmann::json dst;
	dst = *this;

	std::ofstream ofs(path);
	ofs << std::setw(4) << dst << std::endl;
	ofs.close();
}

void Traduction_data::parse_traduction_data_from_json(const std::string& path)
{
	std::ifstream ifs(path);
	nlohmann::json tmp;
	ifs >> tmp;
	ifs.close();

	*this = tmp;
	trad_evaluation = mean_evaluation();
}


void to_json(nlohmann::json& j, const Text_data& p)
{
	j = nlohmann::json{
		{"id", p.text_ID},
		{"text", p.text},
		{"comment", p.comment},
		{"evaluation", p.text_eval}
	};
}

void from_json(const nlohmann::json& j, Text_data& t)
{
	j.at("id").get_to(t.text_ID);
	j.at("text").get_to(t.text);
	j.at("comment").get_to(t.comment);
	j.at("evaluation")
		.get_to(static_cast<std::array<uint16_t, 5>&>(t.text_eval));

}

void to_json(nlohmann::json& j, const Traduction_data& t)
{
	j = nlohmann::json{
		{"DATA", t.text_data},
		{"LANGUAGE", t.language},
		{"TRADUCTION_ID", t.trad_ID},
		{"MOTHER_FILE", t.mother_file},
	};
}

void from_json(const nlohmann::json& j, Traduction_data& t)
{
	j.at("DATA").get_to(t.text_data);
	j.at("LANGUAGE").get_to(t.language);
	j.at("TRADUCTION_ID").get_to(t.trad_ID);
	j.at("MOTHER_FILE").get_to(t.mother_file);
}
 