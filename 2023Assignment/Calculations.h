#pragma once
#include <string>
#include <iostream>
#include <vector>

/**
* Calculations class, this class holds many key functions and mathematical calculations used throughout the project 
*/

class Calculations {
public:
	/**
	* Checks if a string holds a numeric value by checking each character in the string 
	* @param string input can be any string but the method will only return true if all characters present in the string hold a numerical value
	* @return boolean will return true is all characters are numbers eg "786483" but will return false if a character is found such as "276hjsa"
	*/
	bool checkInteger(std::string input);
	/**
	* Takes in two strings and removes a part of the string
	* @param string mainString needs to be the larger of the two strings for example "Alps.txt"
	* @param string editString will identify what will be removes for example ".txt"
	* @return string that has been successfully edited for example "Alps.txt" with the editString of ".txt" will return "Alps"
	*/
	std::string editString(std::string mainString, const std::string editString);
	/**
	* Takes a vector of files names and removes the filetype, based on the position of a "." fullstop
	* @param vector<string> filenames is vector of filenames eg {"Alps.txt", "Pyrenees.txt"}
	* @return vector<string> that has been edited to be without the filetype eg {"Alps", "Pyrenees"}
	*/
	std::vector<std::string> vectorTrim(std::vector<std::string> filenames);
	/**
	* The program takes in userInput as an integer, when a string is needed this function converts it
	* @param string userInput is the value the user input to the console
	* @return the same value but with the string datatype
	*/
	std::string userInputStr(std::string userInput);
	/**
	* Calculates the percentage value of 2 numbers, used to show % of correct answers 
	* @param int a should be the lowest of the two values
	* @param int b should be the highest of the two values
	* @return float with the value of the percentage difference
	*/
	float percentage(int a, int b);
	/**
	* Presents the user with a scoreboard of thier best times 
	* @param scoreBoard is a vector of pairs string the time and the answers
	* @return void, returns nothing
	*/
	void viewScoreBoard(std::vector<std::pair<double, std::string>> scoreBoard);
	/**
	* Presents the user with a list of percentages of correct answers, sorts the list to show the fastest times
	* @param int gameScore is a counter for how many questions have been answered correctly
	* @param int gameCounter is a counter for how many questions have been asked
	* @param vector<float> const& timekeeper is a vector containing the times it took the user to answers each question 
	*/
	void viewPercentages(int gameScore, int gameCounter, std::vector<float> const& timeKeeper);
};