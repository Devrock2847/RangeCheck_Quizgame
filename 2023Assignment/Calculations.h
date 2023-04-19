#pragma once
#include <string>
#include <iostream>
#include <vector>

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