#pragma once
#include <string>
#include <iostream>
#include <vector>

//Declares a class to hold the all functions that calculate or work along side the main file Source.cpp
//The function definitions for this class can be found on the Calculations.cpp
class Calculations
{
public:
	bool checkInteger(std::string input);
	std::string editString(std::string mainString, const std::string editString);
	std::vector<std::string> vectorTrim(std::vector<std::string> filenames);
	std::string userInputStr(std::string userInput);
	float percentage(int a, int b);
	void viewScoreBoard(std::vector<std::pair<double, std::string>> scoreBoard);
	void viewPercentages(int gameScore, int gameCounter, std::vector<float> const& timeKeeper);
};