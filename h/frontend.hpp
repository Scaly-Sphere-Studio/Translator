#pragma once

#include "backend.hpp"

struct GUI_Text {
public:
    std::string txt = "";
    Text_data mt_data;

    void show();
    Text_data save();
};


struct GUI_Category {
public:
    std::string _name;
    std::vector<GUI_Text> _tradline;

    void show();
    void export_cat(uint32_t cat_ID, Traduction_data& data);
};

class TRANSLATOR {
public :
    TRANSLATOR();
    ~TRANSLATOR();

    void show();
private :
    //BACKEND INFORMATIONS
    std::map<std::string, std::string> iso_map;
    std::vector<std::string> _translated;
    //Keep track of the first and second language iso code
    std::string _fl;
    std::string _sl;
    //Informations about current project
    Trad_info _ti;
    Traduction_data _mt;
    Traduction_data _dt;


    //CONTEXT BEHAVIOR
    SSS::GL::Window::Shared _window;
    SSS::GL::Window::Args _args;

    //CATEGORY MAP FOR THE GUI
    std::vector<std::pair<uint32_t, GUI_Category>> CATEGORIES;


    //File and project management
    std::string _translation_folder_path = "translation";
    std::string _project_name = "bohemian";
    void save(std::string path);
    void load();
    void autosave();
    void create_new_file_trad(std::string path);

    //Chrono for the autosave
    std::chrono::steady_clock::time_point start;
    std::chrono::steady_clock::time_point end;

    //INTERFACE
    void menu_bar();
    void language_selector();
    std::string project_path();
    std::string lang_file_name(std::string &lang);
    

    
};