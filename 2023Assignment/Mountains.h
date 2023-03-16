#pragma once
#include<vector>
#include<string>
#include<map>

class Mountains {
	std::vector<std::string> vectorious;
	std::map < std::string, std::vector<std::string> > data;
	std::string fileType;
public:
	Mountains(std::vector<std::string>& filenames);
	std::string getRandomMountain();
	bool checkRange(std::string mountain, std::string range);
	~Mountains();
};