#include "Mountains.h"
#include "ExceptionHandle.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <random>

Mountains::Mountains(std::vector<std::string>& filenames) {
	//Takes the first file in filenames and seperates the file type into a separate variable, in this 
	std::string fileType = filenames[0];
	std::string dot = ".";
	size_t found = fileType.find(dot);
	if (found != std::string::npos) {
		fileType.erase(0, found);
	}
	//Using a loop inputs the data into a tempory vector and adds it to the map as the shortend key value
	for (int i = 0; i < filenames.size(); i++) {
		std::string inputValue = filenames[i];
		std::string input;
		//using fstream reads from the files specified inside the filenames vector and adds the data into a tempory vector
		std::fstream fileInput;
		fileInput.open(filenames[i], std::ios::in);

		if (fileInput.is_open()) {
			while (std::getline(fileInput, input)) {
				vectorious.push_back(input);
			}
			fileInput.close();
		}
		else {
			std::cout << "No file found" << std::endl;
		}
		inputValue.erase(inputValue.length() - fileType.length());
		//at the end of the loop adds both the file name with the type type to the map as the key and the contents of the file as the data for that key 
		data.insert({ inputValue, vectorious });
		//then wipes the data from the variable vector ready to start again
		vectorious.clear();
	}
}

std::string Mountains::getRandomMountain() {
	//Iterates over the map and imports all values into a vector
	auto it = data.begin();
	//Fills the iterator with the values of the map
	std::advance(it, rand() % data.size());
	vectorious = it->second;
	//returns a random value from a vector of every mountain using the same algorithm
	return vectorious[(1 + std::rand() / ((RAND_MAX + 1u) / vectorious.size())) - 1];
} 

bool Mountains::checkRange(std::string mountain, std::string range) {
	//Checks range is valid before inserting data 
	auto it = data.find(range);
	if(it != data.end()) {
		vectorious = data.at(range);
		//Checks the vector for the value the user selected and return true if the user was correct 
		for (int i = 0; i < vectorious.size(); i++) {
			if (vectorious[i] == mountain) {
				//returns boolean value of true
				return true;
			}
		}
	}
	//returns boolean value false if they are incorrect
	return false;
}

std::string Mountains::exceptionHandle() {
	std::map<std::string, std::vector<std::string>> mountains = getMountainData();
	
	int mapSize = mountains.size();

	if (mapSize < 2) {
		ExceptionHandle e;
		std::cout << "ERROR: Insufficient categories." << std::endl;
		throw e;
	}
	std::vector<std::string> mapLength;
	int mapTotal;

	for (auto const& item : mountains) {
		mapLength = item.second;
		mapTotal = mapLength.size();
		if (mapTotal < 1) {
			ExceptionHandle e;
			std::cout << "ERROR: Insufficient members in category." << std::endl;
			throw e;
		}
		//membersVec.clear();
		//membersTotal = 0;
	}
}

bool Mountains::checkFileType(std::string file) {
	std::string fileTypeTwo = "txt";
	
	std::string fileTypeThree = file.substr(file.length() - 3, 3);
	int checkFile = fileTypeThree.compare(fileTypeTwo);

	if (checkFile == 0) {
		std::cout << "File type is txt." << std::endl;
		return true;
	} else {
		ExceptionHandle e;
		std::cout << "File type is not compatable." << std::endl;
		//throw e;
		std::cout << "Program exiting" << std::endl;
		exit(EXIT_FAILURE);
	}
}
Mountains::~Mountains() {};