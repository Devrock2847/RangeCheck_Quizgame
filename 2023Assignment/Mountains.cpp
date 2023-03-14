#include "Mountains.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <random>

Mountains::Mountains(std::vector<std::string>& filenames) {
	//Takes the first file in filenames and seperates the file type into a separate variable
	std::string fileType = filenames[0]; //O(1)
	std::string dot = ".";	//O(1)
	size_t found = fileType.find(dot); //O(n)
	if (found != std::string::npos) { //O(1)
		fileType.erase(0, found); //O(n)
	}
	//Using a loop inputs the data into a tempory vector and adds it to the map with the relevant shortend key
	for (int i = 0; i < filenames.size(); i++) { //O(n)
		std::string inputValue = filenames[i]; //O(1)
		std::string input; //O(1)
		std::fstream fileInput; //O(1)
		fileInput.open(filenames[i], std::ios::in); //O(n)

		if (fileInput.is_open()) { //O(1)
			while (std::getline(fileInput, input)) { //O(n)
				vectorious.push_back(input); //O(1)
			}
			fileInput.close(); //O(1)
		}
		else {
			std::cout << "No file found" << std::endl; //O(1)
		}
		inputValue.erase(inputValue.length() - fileType.length()); //O(1)

		data.insert({ inputValue, vectorious }); //O(log(n))
		vectorious.clear(); //O(1)
	}
}

std::string Mountains::getRandomMountain() {
	//Iterates over the map and imports all values into a vector
	auto it = data.begin(); //O(1)
	//std::advance(it, rand() % data.size()); //O(n)
	std::advance(it, (1 + std::rand() / ((RAND_MAX + 1u) / data.size())) - 1); //O(n)
	vectorious = it->second; //O(1)
	//returns a random value from a vector of every mountain, with research this was the most reliable random number generation
	return vectorious[(1 + std::rand() / ((RAND_MAX + 1u) / vectorious.size())) - 1]; //O(1) 
} 

bool Mountains::checkRange(std::string mountain, std::string range) {
	//Checks range is valid before inserting data 
	auto it = data.find(range); // O(1)
	if(it != data.end()) { // O(1)
		vectorious = data.at(range); //O(1)
		//Checks the vector for the value the user selected
		for (int i = 0; i < vectorious.size(); i++) { //O(n)
			if (vectorious[i] == mountain) { //O(1)
				return true;
			}
		}
	}
	return false;
}
Mountains::~Mountains() {};