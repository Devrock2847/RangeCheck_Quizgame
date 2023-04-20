#pragma once
#include<vector>
#include<string>
#include<map>

class Mountains {
	//declares variables used throughout the class including the main data struture the map
	//i have received comments about vectorious's place here as part of the class but i use it in several places where i would other have to declare a new variable so i feel it's place is justified
	std::vector<std::string> vectorious;
	std::map < std::string, std::vector<std::string> > data;
	std::string fileType;
public:
	//declares the functions detailed in the Mountains.cpp file
	Mountains(std::vector<std::string>& filenames);
	std::string getRandomMountain();
	bool checkRange(std::string mountain, std::string range);
	~Mountains();
};