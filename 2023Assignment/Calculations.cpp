#include "Calculations.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <numeric>

bool Calculations::checkInteger(std::string input) {
	//loops over a string a checks for integers
	for (int i = 0; i < input.length(); i++) {
		if (!isdigit(input[i])) {
			return false;
		}
	}
	return true;
}

std::string Calculations::editString(std::string mainString, const std::string editString) {
	//takes in a string and a substring and erases the substring from the string
	size_t pos = mainString.find(editString);
	if (pos != std::string::npos) {
		mainString.erase(pos, editString.length());
	}
	return mainString;
}

std::vector<std::string> Calculations::vectorTrim(std::vector<std::string> filenames) {
	//A loop for removing the file type from the filenames
	std::string fileType = filenames[0];
	std::string dot = ".";
	size_t found = fileType.find(dot);
	if (found != std::string::npos) {
		fileType.erase(0, found);
	}
	for (int i = 0; i < filenames.size(); i++) {
		filenames[i] = editString(filenames[i], fileType);
	}
	return filenames;
}

std::string Calculations::userInputStr(std::string userInput) {
	std::cin >> userInput;
	return userInput;
}

float Calculations::percentage(int a, int b) {
	//Calculates the percentage of two ints
	float percentageCalc = (static_cast<float>(a) / b) * 100;
	//Rounds the number, converts to a whole number and divides by 100 to make it 00.00 format
	float decimalPoint = (int)(percentageCalc * 100 + .5);
	return (float)decimalPoint / 100;
}

void Calculations::viewScoreBoard(std::vector<std::pair<double, std::string>> scoreBoard) {
	sort(scoreBoard.begin(), scoreBoard.end());
	int a;
	std::cout << "Scoreboard" << std::endl;
	for (int i = 0; i < scoreBoard.size(); i++) {
		a = i + 1;
		std::cout << a << ". " << scoreBoard[i].second << "\n" << "Time: " << scoreBoard[i].first << std::endl;
	}
}

void Calculations::viewPercentages(int gameScore, int gameCounter, std::vector<float> const& timeKeeper) {
	//Calculates the average from the vector of floats
	auto const count = static_cast<float>(timeKeeper.size());
	float average = std::accumulate(timeKeeper.begin(), timeKeeper.end(), 0.0) / count;
	std::cout << "You scored: " << gameScore << " / " << gameCounter << std::endl;
	std::cout << "Your average: " << percentage(gameScore, gameCounter) << "%" << std::endl;
	std::cout << "Average time per question: " << average << " : Seconds" << std::endl;
}
