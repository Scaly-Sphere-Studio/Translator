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
