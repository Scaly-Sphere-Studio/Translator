#include "frontend.hpp"

void GUI_Text::show()
{
    ImGui::Columns(2);                                          ImGui::Separator();
    ImGui::TextWrapped(mt_data.text.c_str());                   ImGui::NextColumn();
    
    ImGui::SetNextItemWidth(-1);
    std::string TEXT_ID = "##" + mt_data.text_ID;
    ImGui::InputText(TEXT_ID.c_str(), &txt);                    ImGui::NextColumn();

    if (!mt_data.comment.empty()) {
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.33f, 0.51f, 0.07f, 1.0f));
        ImGui::Columns(1);                                      ImGui::Bullet();
        ImGui::TextWrapped(mt_data.comment.c_str());
        ImGui::PopStyleColor(1);
    }
}

Text_data GUI_Text::save()
{
    Text_data dst;
    dst.text = txt;
    dst.category = mt_data.category;
    dst.comment = mt_data.comment;
    dst.text_ID = mt_data.text_ID;
    return dst;
}

void GUI_Category::show()
{
    if (ImGui::TreeNode(_name.c_str())) {
        for (uint32_t i = 0; i < _tradline.size(); i++) {
            _tradline[i].show();
        }
        
        ImGui::Separator();
        ImGui::TreePop();
    }
}

void GUI_Category::export_cat(uint32_t cat_ID, Traduction_data& data)
{
    //Rewrite completly the text data
    data.text_data.clear();

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
        iso_map = retrieve_iso_codes(iso_file);
        SSS::log_msg("ISO File found");
    }

    //TODO check for the translator info and retrieve the last opened project

    // Check if the folder translation exist and create/update the file in it
    std::string folder = "translation";
    if (!check_folder_exists(folder)) {
        create_folder(folder);
    }

    //  Create a window
    _args.title = "SSS Translator";
    _args.w = 1280;
    _args.h = 720;
    _window = &SSS::GL::Window::create(_args);
    _window->setVSYNC(true);

    //_ti.parse_info_data_to_json("translation/bohemian/bohemian.ini", true);
    _ti.parse_info_data_from_json("translation/bohemian/bohemian.ini");
    SSS::log_msg("TRANSLATION INI File loaded");

    //Load the first and second language
    _fl = _ti.fl;
    _sl = _ti.sl;

    start = std::chrono::steady_clock::now();
}

TRANSLATOR::~TRANSLATOR()
{
    iso_map.clear();
    _translated.clear();
    CATEGORIES.clear();
}

void TRANSLATOR::show()
{
    //Load both languages from the last opened one in the ini file
    load();

    SSS::ImGuiH::setContext(_window->getGLFWwindow());

    // Main loop
    while (!_window->shouldClose()) {

        SSS::GL::pollEverything();

        // Feed inputs to dear imgui, start new frame
        if (!SSS::ImGuiH::newFrame())
            continue;

        //Create and update the ImGui Window with the context info
        //FLAGS
        ImGuiWindowFlags window_flags = 0;
        window_flags |= ImGuiWindowFlags_MenuBar;
        window_flags |= ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoResize;
        window_flags |= ImGuiWindowFlags_NoTitleBar;
        window_flags |= ImGuiWindowFlags_NoDecoration;

        if (ImGui::Begin("First language", NULL, window_flags))
        {
            ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
            _window->getDimensions(_args.w, _args.h);
            ImGui::SetWindowSize(ImVec2(static_cast<float>(_args.w), static_cast<float>(_args.h)), ImGuiCond_Always);

            //Display the menu bar
            menu_bar();

            //Display the categories
            for (uint32_t i = 0; i < CATEGORIES.size(); i++) {
                CATEGORIES[i].second.show();
            }

            autosave();

            // Render dear imgui into screen
            ImGui::End();
        }
        SSS::ImGuiH::render();
        _window->printFrame();
    }

    save(lang_file_name(_sl));
}


void TRANSLATOR::save(std::string path)
{
    //  SETUP THE TRANSLATED FILE
    _dt.magnitude = _mt.magnitude + 1;
    _dt.trad_ID = _mt.trad_ID;
    _dt.categories = _mt.categories;
    _dt.language = _sl;

    //TODO CAT NAMES
    for (std::pair<uint32_t, GUI_Category> c : CATEGORIES)
    {
        c.second.export_cat(c.first, _dt);
    }

    //EXPORT TRANSLATION INTO JSON FILE
    nlohmann::json ej;
    _dt.parse_traduction_data_to_json(path, true);

    //UPDATE THE INI FILE
    std::string path_ini_file = project_path() + "/" + _project_name + ".ini";
    _ti.parse_info_data_to_json(path_ini_file, true);
}

void TRANSLATOR::load()
{
    // LOAD FUNCTION
    _mt.parse_traduction_data_from_json(lang_file_name(_fl));

    //Check for a previous translation in the selected second language
    bool previous_translation = check_folder_exists(lang_file_name(_sl));
    if (previous_translation) {
        _dt.parse_traduction_data_from_json(lang_file_name(_sl));
    }

    //  CREATE THE GUI CATEGORIES MAP
    CATEGORIES.clear();

    for (std::pair<int, std::string> m : _mt.categories) {
        GUI_Category cat;
        cat._name = m.second;
        CATEGORIES.emplace_back(std::make_pair(m.first, cat));
    }

    for (uint32_t i = 0; i < _mt.text_data.size(); i++) {
        GUI_Text _line;
        _line.mt_data = _mt.text_data[i];

        if (previous_translation) {
            //If a previous translation is found for the second language
            //Preload all the text from the second language file
            if (!_dt.text_data[i].text.empty()) {
                //Check if the text is empty
                _line.txt = _dt.text_data[i].text;
            }
        }
        //Add the text to its specified category
        CATEGORIES[_mt.text_data[i].category].second._tradline.emplace_back(_line);
    }
}

void TRANSLATOR::autosave()
{
    using namespace std::chrono_literals;

    end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_minutes = end - start;

    if (elapsed_minutes > 10min) {
        //Reset the counter
        start = end;
        
        //Save the file in the autosave folder in the project folder
        std::string autosave_file = project_path() + "/autosave";

        if (!check_folder_exists(autosave_file)) {
            //Check if the autosave folder exists and create it if not
            create_folder(autosave_file);
        }

        autosave_file += "/" + _project_name + "_auto.json";
        save(autosave_file);
    }

}

void TRANSLATOR::create_new_file_trad(std::string path)
{
    //  SETUP THE TRANSLATED FILE
    Traduction_data t_tmp;
    t_tmp.magnitude = _mt.magnitude + 1;
    t_tmp.trad_ID = _mt.trad_ID;
    t_tmp.categories = _mt.categories;
    t_tmp.language = _sl;

    //TODO CAT NAMES
    for (auto& m : _mt.text_data)
    {
        Text_data tmp;
        tmp.category = m.category;
        tmp.comment = m.comment;
        tmp.text_ID = m.text_ID;
        t_tmp.text_data.emplace_back(tmp);
    }

    //  EXPORT TRANSLATION INTO JSON FILE
    nlohmann::json ej;
    t_tmp.parse_traduction_data_to_json(path, true);
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
                save(lang_file_name(_sl));
                SSS::log_msg("FILE SAVED");
            }

            ImGui::EndMenu();
        }

        language_selector();


        ImGui::EndMenuBar();
    }
}

void TRANSLATOR::language_selector()
{
    ImGui::Text("        Translation :");
    constexpr float width = 150.f;
    ImGui::SetNextItemWidth(width);

    //initialize to the first item of the iso languages list
    static std::string item_current_idx = _ti.mother_language;
    //reviewed option for the first slider
    const char* combo_preview_value = iso_map[item_current_idx].c_str();
    static std::string iterator = "";

    if (ImGui::BeginCombo("##first_Language", combo_preview_value))
    {
        for (auto& m : _ti.trad_languages)
        {
            iterator = m.first;
            const bool is_selected = (item_current_idx == iterator);
            
            if (ImGui::Selectable(iso_map[m.first].c_str(), is_selected))
            {
                item_current_idx = iterator;
                _fl = item_current_idx;
                load();
            }

            if (is_selected) {
                ImGui::SetItemDefaultFocus();
                //TODO LOAD THE SPECIFIC FILE
            }
        }

        ImGui::EndCombo();
    }

    ImGui::Text(" TO ");
    ImGui::SetNextItemWidth(width);

    static std::string item_current_idx_sl = _sl;
    //reviewed option for the second slider
    const char* combo_preview_value_sl = iso_map[item_current_idx_sl].c_str(); 
    ImGui::SetNextItemWidth(width);


    iterator = "";
    if (ImGui::BeginCombo("##second_language", combo_preview_value_sl))
    {
        for (auto& m : iso_map)
        {
            iterator = m.first;
            const bool is_selected = (item_current_idx_sl == iterator);

            if (ImGui::Selectable(m.second.c_str(), is_selected)) {
                item_current_idx_sl = iterator;
                _sl = item_current_idx_sl;
                //Check if there is already a translation for this language
                if (check_folder_exists(lang_file_name(_sl)))
                {
                    //If a file is found, load the file for the second language
                    load();
                }
                else {
                    //TODO Create a blank file for the new translation
                    create_new_file_trad(lang_file_name(_sl));
                    load();
                    _ti.trad_languages.insert(std::make_pair(_sl, _dt.magnitude));
                }
            }

            if (is_selected) {
                //Modify the current shown second language
                ImGui::SetItemDefaultFocus();
            }
        }

        ImGui::EndCombo();
    }
}

std::string TRANSLATOR::project_path()
{
    std::string file_path = _translation_folder_path;
    file_path += "/" + _project_name;

    return file_path;
}

std::string TRANSLATOR::lang_file_name(std::string &lang)
{
    std::string ext = project_path();
    ext += "/" + _project_name + "_" ;
    ext += lang;
    ext += ".json";

    return ext;
}

