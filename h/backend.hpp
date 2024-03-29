#pragma once

#include "data.hpp"
#include <fstream>
#include <filesystem>
#include <chrono>
#include <string>

#include <SSS/ImGuiH.hpp>
#include <SSS/Commons.hpp>
#include <SSS/GL.hpp>



///////////////////////////////////////
/* UUID - TEXT DATA & TRADUCTION DATA*/
///////////////////////////////////////

namespace ImGui {
	IMGUI_API bool  InputText(const char* label, std::string* str, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = NULL, void* user_data = NULL);
}



// Converts a value to a hex string by outputing it to a string stream
template <typename T>
std::string hex_convertor(T const& arg) noexcept try
{
	std::ostringstream strstream;
	strstream << std::hex << arg;
	return strstream.str();
}
catch (...) {
	return "[SSS::toHex() error]";
}



//Create a hash value for the ID gen
std::string time_stamp();
//Create a string value to store ID for each traduction segment
std::string ID_text_data_stringify(std::string category, std::string sub_cat, std::string time_stamp);
//Create a hash value for each traduction participation
std::string ID_trad_file_stringify(std::string user, std::string time_stamp);
//Time diff

////////
/*FILE*/
////////

//Check for the presence of the selected folder (absolute or relative path)
bool check_folder_exists(const std::string &path);
//Create the folder using its future path
void create_folder(const std::string &path);
//Check if the path is absolute and convert it if necessary
std::string absolute_path(const std::string &path);
//Create a new file to hold the traduction
void create_traduction_file(const std::string& path, const uint16_t language, const Traduction_data& mother);
void gen_info_traduction_file(const std::string& path);

void create_files(const std::string name, Traduction_data& data);

std::map<std::string, std::string> retrieve_iso_codes(const std::string path);

//////////////////
/*BASE DE DONNEE*/
//////////////////
void string_compare(const std::string& first, const std::string& second);
