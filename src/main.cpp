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

    // FIRST SETUP OPERATION
    // Fill the languages ISO code map 
    std::unordered_map<std::string, std::string> iso_map;
    iso_map = retrieve_iso_codes("iso_codes/iso.json");


    // Check if the folder traduction exist and create/update the file in it
    std::string folder = "translation";
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

    Traduction_data mt;
    mt.parse_traduction_data_from_json("test.json");
    for (unsigned int i = 0; i < mt.text_data.size(); i++) {
        std::cout << mt.text_data[i].text << std::endl;
    }

    //  GENERATE THE CATEGORY MAP
    std::map<uint32_t, GUI_Category> CAT;

    
    //  CREATE THE GUI CATEGORIES MAP
    for (auto& m : mt.categories) {
        GUI_Category cat;
        cat._name = m.second;
        CAT.insert(std::make_pair(m.first, cat));
    }

    //  FILL EACH CATEGORY WITH IT'S TEXTS
    for (auto& t : mt.text_data) {
        GUI_Text _line;
        _line.text = t;
        CAT[t.category]._tradline.emplace_back(_line);
    }

    //  Create a window
    SSS::GL::Window::Args args;
    args.title = "ImGUI example window";
    args.w = 1280;
    args.h = 720;
    SSS::GL::Window::Shared window = SSS::GL::Window::create(args);
    window->setVSYNC(true);

    //  Setup Dear ImGui window
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::GetIO().IniFilename = nullptr;

    //  Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window->getGLFWwindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // Main loop
    while (!window->shouldClose()) {
        // Set GLFW context
        SSS::GL::Context const context(window);
    
        // Feed inputs to dear imgui, start new frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        // Display demo
        ImGui::Begin("First language", NULL ,ImGuiWindowFlags_NoMove);
        ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
        ImGui::SetWindowSize(ImVec2(args.w, args.h), ImGuiCond_FirstUseEver);
    
       
        //ImGui::Columns(3, "mycolumns"); // 3-ways, with border
        for (auto& c : CAT) {
            c.second.show();
        }
    
        ImGui::End();
    
        // Render dear imgui into screen
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        window->printFrame();
    }

    //  SETUP THE TRANSLATED FILE
    Traduction_data dt;
    dt.magnitude = mt.magnitude + 1;
    dt.trad_ID = mt.trad_ID;
    dt.categories = mt.categories;
    dt.language = "fra";

    //  EXPORT TRANSLATION INTO JSON FILE
    for (auto& c : CAT)
    {
        c.second.export_cat(c.first, dt);
    }

    nlohmann::json ej;
    dt.parse_traduction_data_to_json("trad_fr.json", true);

    // Clean up ImGUI
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    return 0;
}


