#include "backend.hpp"

std::string time_stamp()
{
	//Access the TAI(Internation Atomic Time) and convert its value into a hex string
	return hex_convertor(std::chrono::tai_clock::now().time_since_epoch().count());
}

std::string ID_text_data_stringify(std::string cat, std::string sub_cat, std::string time_stamp)
{
	//Text ID : CAT_SUB_HEXTIMESTAMP
	return cat + "_"+ sub_cat + "_" + time_stamp;
}

std::string ID_trad_file_stringify(std::string userID, std::string time_stamp)
{
	return userID + "_" + time_stamp;
}

bool check_folder_exists(std::string &path)
{	
	std::string abs_path_str = absolute_path(path);

	//Check if the folder exists using it's supposed path
	if (std::filesystem::exists(path)) {
		SSS::log_msg("[FILE] : " + abs_path_str + " folder already exists");
		return true;
	}
	else {
		SSS::log_msg("[FILE] : \"" + abs_path_str + "\" folder doesn't exists");
		return false;
	}
}

void create_folder(std::string &path)
{
	std::filesystem::create_directory(path);

	SSS::log_msg("[FILE] : Generating : \"" + absolute_path(path) + "\" folder");
}

std::string absolute_path(std::string& path)
{
	std::string absolute_path;

	//check if the path is a relative path and log the absolute path
	if (static_cast<std::filesystem::path>(path).is_relative()) {
		absolute_path = std::filesystem::current_path().string() + "\\" + path;
	}
	else {
		absolute_path = path;
	}

	return absolute_path;
}
