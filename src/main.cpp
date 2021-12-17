#include <iostream>
#include <nlohmann/json.hpp>

#include <string>

#include "frontend.hpp"
#include "backend.hpp"

//TODO Create a proper translator program class
std::map<std::string, std::string> iso_map;


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

void language_selector() {
    int width = 250;
    static int style = 0;


    //static int item_current_idx = 0; // Here we store our selection data as an index.

    static std::string item_current_idx = iso_map.begin()->first;
    const char* combo_preview_value = iso_map[item_current_idx].c_str();  // Pass in the preview value visible before opening the combo (it could be anything)
    ImGui::SetNextItemWidth(width);


    static std::string iterator = "";
    if (ImGui::BeginCombo("##FirstLanguage", combo_preview_value))
    {

        //todo performance drop here
        //Here need only the languages that have already been translated
        for (auto& m : iso_map)
        {
            iterator = m.first;

            const bool is_selected = (item_current_idx == iterator);
            if (ImGui::Selectable(m.second.c_str(), is_selected))
                  item_current_idx = iterator;

            if (is_selected) {
                ImGui::SetItemDefaultFocus();
            }
     
        }   

        ImGui::EndCombo();
    }

    ImGui::SetNextItemWidth(width);

    static std::string item_current_idx_sl = iso_map.begin()->first;
    const char* combo_preview_value_sl = iso_map[item_current_idx_sl].c_str();  // Pass in the preview value visible before opening the combo (it could be anything)
    ImGui::SetNextItemWidth(width);


    static std::string iterator_sl = "";

    if (ImGui::BeginCombo("##test1", combo_preview_value_sl))
    {
        //todo performance drop here 
        //Here is the need for the cover of the whole iso map to chose a language to translate

        for (auto& m : iso_map)
        {
            iterator_sl = m.first;

            const bool is_selected = (item_current_idx_sl == iterator_sl);
            if (ImGui::Selectable(m.second.c_str(), is_selected))
                item_current_idx_sl = iterator_sl;

            if (is_selected) {
                ImGui::SetItemDefaultFocus();
            }
        }

        ImGui::EndCombo();
    }
};

void menu() {
    ImGui::PushItemWidth(ImGui::GetFontSize() * -12);
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("Menu"))
        {
            //SAVE CURRENT PROGRESSION
            if (ImGui::MenuItem("Save"))
            {
                std::cout << "saved";
            }

            ImGui::EndMenu();
        }

        language_selector();

        ImGui::EndMenuBar();
    }
};

int main()
{

    // FIRST SETUP OPERATION
    // Fill the languages ISO code map 

    std::string iso_file = "iso_codes/iso.json";
    if (check_folder_exists(iso_file)) {
        std::cout << "le fichier iso existe" << std::endl;
    }
    /*std::unordered_map<std::string, std::string> iso_map;*/
    iso_map = retrieve_iso_codes(iso_file);

    for (auto& l : iso_map) {
        /*std::cout << l.second << std::endl;*/
    }



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



    //  GENERATE THE CATEGORY MAP
    std::map<uint32_t, GUI_Category> CAT;

    //LOAD FUNCTION
    Traduction_data mt;
    mt.parse_traduction_data_from_json("test.json");
    for (unsigned int i = 0; i < mt.text_data.size(); i++) {
        /*std::cout << mt.text_data[i].text << std::endl;*/
    }
    


    //  CREATE THE GUI CATEGORIES MAP
    for (auto& m : mt.categories) {
        GUI_Category cat;
        cat._name = m.second;
        CAT.insert(std::make_pair(m.first, cat));
    }

    //  FILL EACH CATEGORY WITH ITS TEXTS
    for (auto& t : mt.text_data) {
        GUI_Text _line;
        _line.text = t;
        CAT[t.category]._tradline.emplace_back(_line);
    }

    //  Create a window
    SSS::GL::Window::Args args;
    args.title = "SSS Translator";
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

        //FLAGS
        ImGuiWindowFlags window_flags = 0;
        window_flags |= ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoTitleBar;
        window_flags |= ImGuiWindowFlags_MenuBar;

        // Display demo
        ImGui::Begin("First language", NULL, window_flags);
        ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
        ImGui::SetWindowSize(ImVec2(args.w, args.h), ImGuiCond_FirstUseEver);
        

        menu();



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

    //Save function
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


