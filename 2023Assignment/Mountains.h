#pragma once
#include<vector>
#include<string>
#include<map>

class Mountains {
	std::vector<std::string> vectorious;
	std::map < std::string, std::vector<std::string> > data;
	std::string fileType;
public:
	//Time complexity: //O(12) + O(log(n) + O(n) + O(n) + O(n) + O(n) = O(n)
	Mountains(std::vector<std::string>& filenames);

	//Time complexity: //O(3) + O(n) = O(n)
	std::string getRandomMountain();

	//Time complexity: //O(4) + O(n) = O(n)
	bool checkRange(std::string mountain, std::string range);

	~Mountains();
};
