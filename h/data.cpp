#include "data.hpp"


/// 
/// EVALUTION STRUCT FOR DATA AND USER COMPARISON
/// 
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
		mean += this->at(i) * (i+1);
	}

	return mean / count;
}

uint32_t  Evaluation::count() const
{
	uint32_t count = 0;
	for (uint32_t i = 0; i < 5; i++) {
		count += this->at(i);
	}

	return count;
}

/// 
/// MAIN TRADUCTION STRUCTURE MANAGER
/// 

Traduction_data::Traduction_data()
{

}


Traduction_data::Traduction_data(std::string &path)
{
	parse_traduction_data_from_json(path);
}

Traduction_data::~Traduction_data()
{
	text_data.clear();
	categories.clear();
}

float Traduction_data::mean_evaluation()
{
	//TODO
	//float mean = 0;
	//for (Text_data t : text_data) {
	//	mean += t.text_eval.average();
	//}

	//return mean / static_cast<float>(text_data.size());
	return 0.0f;
}

void Traduction_data::print()
{
	std::cout << *this;
}

void Traduction_data::parse_traduction_data_to_json(const std::string& path, const bool prettify)
{
	nlohmann::json dst;
	dst = *this;

	std::ofstream ofs(path);
	if (prettify) {
		ofs << std::setw(4) << dst << std::endl;
	}
	else {
		ofs <<  dst << std::endl;
	}
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

void Traduction_data::push_text_data(std::string text, std::string comment, std::string ID, uint32_t cat)
{
	Text_data t;
	t.comment = comment;
	t.text = text;
	t.text_ID = ID;
	//t.category = cat;

	text_data.emplace_back(t);
}

void Traduction_data::remove_text_data(std::string ID)
{
	for (size_t i = 0; i < text_data.size(); i++) {
		if (text_data[i].text_ID == ID) {
			text_data.erase(text_data.begin() + i);
		}
	}
}


/// 
/// TRADUCTION INFO
/// 


void Trad_info::parse_info_data_to_json(const std::string& path, const bool prettify)
{
	nlohmann::json dst;
	dst = *this;

	std::ofstream ofs(path);
	if (prettify) {
		ofs << std::setw(4) << dst << std::endl;
	}
	else {
		ofs << dst << std::endl;
	}
	ofs.close();
}

void Trad_info::parse_info_data_from_json(const std::string& path)
{
	std::ifstream ifs(path);
	nlohmann::json tmp;
	ifs >> tmp;
	ifs.close();

	*this = tmp;
}

//TEXT DATA PARSER
void to_json(nlohmann::json& j, const Text_data& p)
{
	j = nlohmann::json{
		{"id", p.text_ID},
		{"text", p.text},
		{"comment", p.comment},
		//{"evaluation", p.text_eval},
		{"category", p.category}
	};
}

void from_json(const nlohmann::json& j, Text_data& t)
{
	j.at("id").get_to(t.text_ID);
	j.at("text").get_to(t.text);
	j.at("comment").get_to(t.comment);
	//j.at("evaluation")
	//	.get_to(static_cast<std::array<uint16_t, 5>&>(t.text_eval));
	j.at("category").get_to(t.category);

}

//TRADUCTION DATA PARSER
void to_json(nlohmann::json& j, const Traduction_data& t)
{
	j = nlohmann::json{
		{"DATA", t.text_data},
		{"LANGUAGE", t.language},
		{"TRADUCTION_ID", t.trad_ID},
		{"MOTHER_FILE", t.magnitude},
		{"CATEGORIES", t.categories}
	};
}

void from_json(const nlohmann::json& j, Traduction_data& t)
{
	j.at("DATA").get_to(t.text_data);
	j.at("LANGUAGE").get_to(t.language);
	j.at("TRADUCTION_ID").get_to(t.trad_ID);
	j.at("MOTHER_FILE").get_to(t.magnitude);
	j.at("CATEGORIES").get_to(t.categories);
}

//TRADUCTION INFO PARSER
void to_json(nlohmann::json& j, const Trad_info& t)
{
	j = nlohmann::json{
		{"MOTHER_LANGUAGE", t.mother_language},
		{"TRAD_LANGUAGES", t.trad_languages},
		{"TRADUCTION_ID", t.trad_ID},
		{"FIRST_LANGUAGE", t.fl},
		{"SECOND_LANGUAGE", t.sl},
	};
}

void from_json(const nlohmann::json& j, Trad_info& t)
{
	j.at("TRAD_LANGUAGES").get_to(t.trad_languages);
	j.at("TRADUCTION_ID").get_to(t.trad_ID);
	j.at("MOTHER_LANGUAGE").get_to(t.mother_language);
	j.at("FIRST_LANGUAGE").get_to(t.fl);
	j.at("SECOND_LANGUAGE").get_to(t.sl);

}


