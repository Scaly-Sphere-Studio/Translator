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
