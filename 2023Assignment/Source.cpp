#include "Mountains.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

//Time complexity: O(1) + O(n) = O(n)
bool checkInteger(std::string input){ //O(n)
	//loops over a string a checks for integers
	for (int i = 0; i < input.length(); i++) { //O(n)
	if (!isdigit(input[i])) { //0(1)
			return false;
		}
	}
	return true;
}
//Time complexity: O(3) = O(1)
std::string editString(std::string mainString, const std::string editString) { 
	//takes in a string and a substring and erases the substring from the string
	size_t pos = mainString.find(editString); //O(1)
	if (pos != std::string::npos) { //O(1)
		mainString.erase(pos, editString.length()); //O(1)
	}
	return mainString;
}
//Time complexity: O(6) + O(n) = O(n)
std::vector<std::string> vectorTrim(std::vector<std::string> filenames) {
	//A loop for removing the file type from the filenames
	std::string fileType = filenames[0]; //O(1)
	std::string dot = "."; //O(1)
	size_t found = fileType.find(dot); //O(1)
	if (found != std::string::npos) { //O(1)
		fileType.erase(0, found); //O(1)
	}
	for (int i = 0; i < filenames.size(); i++) { //O(n)
		filenames[i] = editString(filenames[i], fileType); //O(1)
	}
	return filenames;
}
//Time complexity: O(24) + O(n) + O(n) + O(n) + O(n) = O(n)
void runGame() {
	int gameCounter = 0; //O(1)
	int gameScore = 0; //O(1)

	std::vector<std::string> files = { "Alps.txt", "Carpathians.txt", "Icelandic Highlands.txt", "Pyrenees.txt" }; //O(1)
	Mountains mountainObject(files); //O(n)
	std::vector<std::string> mountainRange = vectorTrim(files); //O(n)

	while (true) { //O(1)
		bool isTrue;//O(1)
		std::string userInput;//O(1)
		std::string randomMountain = mountainObject.getRandomMountain(); //O(n)
		std::cout << "\n";
		std::cout << "Which mountain range does the following mountain belong too: " << randomMountain << "\n"; //O(1)
		std::cout << "[1]" << mountainRange[0] << "   " << "[2]" << mountainRange[1] << "   " << "[3]" << mountainRange[2] << "   " << "[4]" << mountainRange[3] << std::endl; //O(1)
		std::cin >> userInput; //O(1)

		if (userInput == "quit" || userInput == "exit") { //O(1)
			std::cout << "Game Exited" << std::endl; //O(1)
			exit(1); //O(1)
		}
		if (checkInteger(userInput) == true) { //O(1)
			//Checks if it's an int then converts into an int 
			int userInputInt = std::stoi(userInput); //O(1)
			if (userInputInt > 0 && userInputInt <= mountainRange.size()) { //O(1)
				isTrue = mountainObject.checkRange(randomMountain, mountainRange[userInputInt - 1]); //O(n)
				if (isTrue == true) { //O(1)
					gameCounter = gameCounter + 1; //O(1)
					gameScore = gameScore + 1; //O(1)
					std::cout << "Correct!, Your score is now " << gameScore << " / " << gameCounter << std::endl; //O(1)
				}
				else if (isTrue == false) { //O(1)
					gameCounter = gameCounter + 1; //O(1)
					std::cout << "Incorrect, your score is now " << gameScore << " / " << gameCounter << std::endl; //O(1)
				}
			}
			else {
				std::cout << "Invalid input please enter a 1,2,3,4 or type 'quit' or 'exit'" << std::endl; //O(1)
			}
		}
		else {
			std::cout << "Invalid input please enter a 1,2,3,4 or type 'quit' or 'exit'" << std::endl; //O(1)
		}
	}
}
//Time complexity: O(4) + O(n) = O(n)
int main() {
	std::cout << "Welcome to RangeCheck, a quiz game to test your knowledge about mountains!" << std::endl; //O(1)
	std::cout << "Rules are simple you will be presented with a mountain and you must select the range it belongs too." << std::endl; //O(1)
	std::cout << "Enter 1,2,3,4 to answer or enther 'exit' or 'quit' to stop playing" << std::endl; //O(1)
	std::cout << "\n"; //O(1)

	runGame(); //O(n)
}