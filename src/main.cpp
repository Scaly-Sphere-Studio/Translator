#include <iostream>
#include <nlohmann/json.hpp>

#include <SSS/GL.hpp>
#include <imgui.h>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "frontend.hpp"
#include "backend.hpp"


//Text_data rng_data() {
//	Text_data rng;
//	rng.text_ID = time_stamp();
//	rng.text = time_stamp();
//	rng.comment = time_stamp();
//	rng.text_eval = std::array<uint16_t, 5> {0, 1, 2, 3, 4};
//	
//	return rng;
//};

//Check if the folder traduction exist and create/update the file in it
//std::string folder = "traduction";
//if (!check_folder_exists(folder)) {
//	create_folder(folder);
//}
//std::filesystem::current_path(folder);


/*std::string first = "This is an exemple of speech";
std::string second = "And This is an exemple of an other speech";

string_compare(first, first);*/

int main()
{

    // Create a window
    SSS::GL::Window::Args args;
    args.title = "ImGUI example window";
    args.w = 1280;
    args.h = 720;
    SSS::GL::Window::Shared window = SSS::GL::Window::create(args);
    window->setVSYNC(true);

    // Setup Dear ImGui window
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::GetIO().IniFilename = nullptr;

    // Setup Platform/Renderer bindings
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
        ImGui::ShowDemoWindow();

        // Render dear imgui into screen
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        window->printFrame();
    }

    // Clean up ImGUI
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

	return 0;
}
