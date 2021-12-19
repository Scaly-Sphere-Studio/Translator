#include <iostream>
#include <nlohmann/json.hpp>

#include <string>

<<<<<<< HEAD
#include "frontend.hpp"
#include "backend.hpp"

//TODO Create a proper translator program class
std::map<std::string, std::string> iso_map;

=======

//#include <SSS/GL.hpp>
//#include <imgui.h>
//#include "imgui_impl_glfw.h"
//#include "imgui_impl_opengl3.h"

//#include "frontend.hpp"
#include "backend.hpp"

>>>>>>> parent of 58187b2 (First try for integration of front end)

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

<<<<<<< HEAD
    o << std::setw(4) << j;
=======

>>>>>>> parent of 58187b2 (First try for integration of front end)
};

int main()
{
    TRANSLATOR t;
    t.show();

<<<<<<< HEAD
    return 0;
}


=======
    // FIRST SETUP OPERATION
    // Fill the languages ISO code map 
    std::unordered_map<std::string, std::string> iso_map;
    iso_map = retrieve_iso_codes("iso_codes/iso.json");


    // Check if the folder traduction exist and create/update the file in it
    std::string folder = "traduction";
    if (!check_folder_exists(folder)) {
        create_folder(folder);
    }

    ////Go into the traduction folder
    //std::filesystem::current_path(folder);

    ////Create a new work traduction folder 
    //std::string workfolder = "group_traduction";
    //if (!check_folder_exists(workfolder)) {
    //    create_folder(workfolder);
    //}

    //std::filesystem::current_path(workfolder);

    Traduction_data td;
    td.parse_traduction_data_from_json("test.json");
    for (unsigned int i = 0; i < td.text_data.size(); i++) {
        std::cout << td.text_data[i].text << std::endl;
    }

    return 0;
}
>>>>>>> parent of 58187b2 (First try for integration of front end)
