#include <iostream>
#include <nlohmann/json.hpp>

#include <string>

#include "frontend.hpp"
#include "backend.hpp"



void read_from_text() {
    std::fstream f("bohemian.txt");
    std::string str;

    std::vector<Text_data> rhapsody;
    while (std::getline(f, str)) {
        Text_data tmp;
        tmp.text = str;
        tmp.category = 2;
        tmp.text_ID = time_stamp();

        rhapsody.emplace_back(tmp);
    }

    for (Text_data c : rhapsody) {
        std::cout << c.text << std::endl;
    }

    std::string name = "bohemian.json";
    // write prettified JSON to another file
    std::ofstream o(name);
    nlohmann::json j = rhapsody;


    o << std::setw(4) << j;
};

int main()
{
    TRANSLATOR t;
    t.show();


    return 0;
}