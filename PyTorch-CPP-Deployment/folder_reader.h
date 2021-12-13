#pragma once

#include <string>
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;

auto folder_to_file(std::string& location) -> std::vector<std::tuple<std::string>>{
	std::vector<std::tuple<std::string>> file_location;
	std::string path = location;
	for (const auto & entry : fs::directory_iterator(path)){
		file_location.push_back(std::make_tuple(entry.path()));
	}
	return file_location;
}