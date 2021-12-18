#pragma once

#include "backend.hpp"

#include <string>
#include <SSS/GL.hpp>
#include <imgui.h>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


struct GUI_Text {
public:
    void show();
    Text_data save();
    char bfr[128] = "";
    Text_data text;

};


struct GUI_Category {
public:
    void show();
    void export_cat(uint32_t cat_ID, Traduction_data& data);
    std::string _name;
    std::vector<GUI_Text> _tradline;
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


    //CONTEXT BEHAVIOR
    SSS::GL::Window::Shared _window;
    SSS::GL::Window::Args _args;

    //CATEGORY MAP FOR THE GUI
    std::map<uint32_t, GUI_Category> CAT;


    //File and project management
    std::string _translation_folder_path = "translation";
    std::string _project_name = "";
    void save();
    void load(std::string path);
    

    //INTERFACE
    void menu_bar();
    void language_selector();
    std::string lang_ext_file_name(std::string &id, std::string &lang_iso_ext);

};