#pragma once

#include "data.hpp"
#include <filesystem>
#include <fstream>
#include <chrono>
#include <string>

#include <SSS/Commons.hpp>


///////////////////////////////////////
/* UUID - TEXT DATA & TRADUCTION DATA*/
///////////////////////////////////////


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


////////
/*FILE*/
////////

//Check for the presence of the selected folder (absolute or relative path)
bool check_folder_exists(std::string &path);
//Create the folder using its future path
void create_folder(std::string &path);
//Check if the path is absolute and convert it if necessary
std::string absolute_path(std::string &path);


//////////////////
/*BASE DE DONNEE*/
//////////////////

