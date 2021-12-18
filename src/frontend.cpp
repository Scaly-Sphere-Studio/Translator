#include "frontend.hpp"

void GUI_Text::show()
{
    
    ImGui::Columns(2);
    ImGui::Separator();
    ImGui::TextWrapped(text.text.c_str());                          ImGui::NextColumn();
    
    //Create a non read input ID 
    const std::string input_ID = "##" + text.text_ID;
    ImGui::SetNextItemWidth(-1);
    ImGui::InputText(input_ID.c_str(), bfr, IM_ARRAYSIZE(bfr));     ImGui::NextColumn();

    if (!text.comment.empty()) {
        ImGui::Columns(1);
        ImGui::Bullet();
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.33f, 0.51f, 0.07f, 1.0f));
        ImGui::TextWrapped(text.comment.c_str());
        ImGui::PopStyleColor(1);
    }
}

Text_data GUI_Text::save()
{
    Text_data dst;
    dst.text = bfr;
    dst.category = INT32_MAX;
    dst.comment = text.comment;
    dst.text_ID = text.text_ID;
    return dst;
}

void GUI_Category::show()
{
    if (ImGui::TreeNode(_name.c_str())) {
        for (GUI_Text td : _tradline) {
            td.show();
        }
        
        ImGui::Separator();
        ImGui::TreePop();
    }
}

void GUI_Category::export_cat(uint32_t cat_ID, Traduction_data& data)
{
    for (GUI_Text tl : _tradline) {
        Text_data txt = tl.save();
        txt.category = cat_ID;
        data.text_data.emplace_back(txt);
    }
}

TRANSLATOR::TRANSLATOR()
{
    // FIRST SETUP OPERATION
    // Fill the languages ISO code map 
    std::string iso_file = "iso_codes/iso.json";
    if (check_folder_exists(iso_file)) {
        std::cout << "le fichier iso existe" << std::endl;
    }
    iso_map = retrieve_iso_codes(iso_file);

    //TODO check for the translator info and retrieve the last opened project

    // Check if the folder traduction exist and create/update the file in it
    std::string folder = "translation";
    if (!check_folder_exists(folder)) {
        create_folder(folder);
    }

    //  Create a window
    _args.title = "SSS Translator";
    _args.w = 1280;
    _args.h = 720;
    _window = SSS::GL::Window::create(_args);
    _window->setVSYNC(true);

}

TRANSLATOR::~TRANSLATOR()
{
}

void TRANSLATOR::show()
{
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

    //  Setup Dear ImGui window
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::GetIO().IniFilename = nullptr;

    //  Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(_window->getGLFWwindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // Main loop
    while (!_window->shouldClose()) {
        // Set GLFW context
        SSS::GL::Context const context(_window);
        // Feed inputs to dear imgui, start new frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        //FLAGS
        ImGuiWindowFlags window_flags = 0;
        window_flags |= ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoTitleBar;
        window_flags |= ImGuiWindowFlags_MenuBar;

        ImGui::Begin("First language", NULL, window_flags);
        ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
        //Update the window dimensions
        _window.get()->getDimensions(_args.w, _args.h);
        ImGui::SetWindowSize(ImVec2(_args.w, _args.h), ImGuiCond_Always);

        //Display the menu bar
        menu_bar();

        //Display the categories
        for (std::pair<uint32_t, GUI_Category> c : CAT) {
            c.second.show();
        }

        // Render dear imgui into screen
        ImGui::End();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        _window->printFrame();
    }

    save();

    // Clean up ImGUI
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}


void TRANSLATOR::save()
{
    //  SETUP THE TRANSLATED FILE
    Traduction_data dt;
    dt.magnitude = _mt.magnitude + 1;
    dt.trad_ID = _mt.trad_ID;
    dt.categories = _mt.categories;
    dt.language = "fra";


    //TODO CAT NAMES
    for (std::pair<uint32_t, GUI_Category> c : CAT)
    {
        c.second.export_cat(c.first, dt);
    }

    //  EXPORT TRANSLATION INTO JSON FILE
    nlohmann::json ej;
    dt.parse_traduction_data_to_json("trad_fr.json", true);
}

void TRANSLATOR::load(std::string path)
{
}

void TRANSLATOR::menu_bar()
{
    ImGui::PushItemWidth(ImGui::GetFontSize() * -12);
    
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("Menu"))
        {
            //SAVE CURRENT PROGRESSION
            if (ImGui::MenuItem("Save"))
            {
                save();
                std::cout << "saved\n";
            }

            ImGui::EndMenu();
        }


        language_selector();


        ImGui::EndMenuBar();
    }
}

void TRANSLATOR::language_selector()
{
    ImGui::Text("        Traduction :");
    int width = 150;

    //initialize to the first item of the iso languages list
    static std::string item_current_idx = iso_map.begin()->first;
    //reviewed option
    const char* combo_preview_value = iso_map[item_current_idx].c_str();

    ImGui::SetNextItemWidth(width);

    static std::string iterator = "";
    if (ImGui::BeginCombo("##first_Language", combo_preview_value))
    {

        //todo Here need only the languages that have already been translated
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

    ImGui::Text(" TO ");
    ImGui::SetNextItemWidth(width);

    static std::string item_current_idx_sl = iso_map.begin()->first;
    const char* combo_preview_value_sl = iso_map[item_current_idx_sl].c_str();  // Pass in the preview value visible before opening the combo (it could be anything)
    ImGui::SetNextItemWidth(width);


    static std::string iterator_sl = "";

    if (ImGui::BeginCombo("##second_language", combo_preview_value_sl))
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
}

std::string TRANSLATOR::lang_ext_file_name(std::string& id, std::string& lang_iso_ext)
{
    return std::string();
}
