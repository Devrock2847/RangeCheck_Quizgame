#include "Calculations.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <numeric>

bool Calculations::checkInteger(std::string input) {
	//loops over a string and checks for chars that are not integers and returns false if any are found and true if they are not
	for (int i = 0; i < input.length(); i++) {
		if (!isdigit(input[i])) {
			//returns boolean value false
			return false;
		}
	}
	//returns boolean value true 
	return true;
}

std::string Calculations::editString(std::string mainString, const std::string editString) {
	//takes in a string and a substring and erases the substring from the string
	//this is only used in the vectorTrim function after the editString has been isolated
	//for example if you put in 'mountain', 'ain' this function will return 'mount'
	size_t pos = mainString.find(editString);
	if (pos != std::string::npos) {
		mainString.erase(pos, editString.length());
	}
	//returns a string that has been modified by the function
	return mainString;
}

std::vector<std::string> Calculations::vectorTrim(std::vector<std::string> filenames) {
	//A loop for removing the file type from the filenames
	//first it takes a filename from the vector of filenames then finds the '.' where the filename begins and erases first part of the string eg; 'Alps.txt' becomes '.txt'
	//then loops through the filenames array and removes '.txt' from each member of the array and returns it
	std::string fileType = filenames[0];
	std::string dot = ".";
	size_t found = fileType.find(dot);
	if (found != std::string::npos) {
		fileType.erase(0, found);
	}
	for (int i = 0; i < filenames.size(); i++) {
		//requires the editString function declared in the Calculations.cpp file
		filenames[i] = editString(filenames[i], fileType);
	}
	//returns the vector of strings filenames with the file type removes from each element of the vector
	return filenames;
}

std::string Calculations::userInputStr(std::string userInput) {
	//simple user input method, was created to save typing it out multiple times
	std::cin >> userInput;
	//returns a string of the users input 
	return userInput;
}

float Calculations::percentage(int a, int b) {
	//Calculates the percentage of two ints
	float percentageCalc = (static_cast<float>(a) / b) * 100;
	//Rounds the number, converts to a whole number and divides by 100 to make it 00.00 format
	float decimalPoint = (int)(percentageCalc * 100 + .5);
	//returns the casted float of decimal point /100 to give the percentage value 
	return (float)decimalPoint / 100;
}

void Calculations::viewScoreBoard(std::vector<std::pair<double, std::string>> scoreBoard) {
	//sorts the scoreBoard vector from smallest to largest
	sort(scoreBoard.begin(), scoreBoard.end());
	//int a will represent the numbers of the score bored like 1. 2. 3. ect 
	int a;
	std::cout << "Scoreboard" << std::endl;
	//this loop prints out the entire scoreBoard in order 
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
	//uses the percentage function defined in Calculations.cpp
	std::cout << "Your average: " << percentage(gameScore, gameCounter) << "%" << std::endl;
	std::cout << "Average time per question: " << average << " : Seconds" << std::endl;
}