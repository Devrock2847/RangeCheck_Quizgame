#include "Mountains.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <numeric>
#include <thread>

bool checkInteger(std::string input){
	//loops over a string a checks for integers
	for (int i = 0; i < input.length(); i++) {
	if (!isdigit(input[i])) {
			return false;
		}
	}
	return true;
}

std::string editString(std::string mainString, const std::string editString) { 
	//takes in a string and a substring and erases the substring from the string
	size_t pos = mainString.find(editString);
	if (pos != std::string::npos) {
		mainString.erase(pos, editString.length());
	}
	return mainString;
}

std::vector<std::string> vectorTrim(std::vector<std::string> filenames) {
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

std::string userInputStr(std::string userInput) {
	std::cin >> userInput;
	return userInput;
}

float percentage(int a, int b) {
	//Calculates the percentage of two ints
	float percentageCalc = (static_cast<float>(a) / b) * 100;
	//Rounds the number, converts to a whole number and divides by 100 to make it 00.00 format
	float decimalPoint = (int)(percentageCalc * 100 + .5);
	return (float)decimalPoint / 100;
}

void viewScoreBoard(std::vector<std::pair<double, std::string>> scoreBoard) {
	sort(scoreBoard.begin(), scoreBoard.end());
	int a;
	std::cout << "Scoreboard" << std::endl;
	for (int i = 0; i < scoreBoard.size(); i++) {
		a = i + 1;
		std::cout << a << ". " << scoreBoard[i].second << "\n" << "Time: " << scoreBoard[i].first << std::endl;
	}
}

void viewPercentages(int gameScore, int gameCounter, std::vector<float> const& timeKeeper) {
	//Calculates the average from the vector of floats
	auto const count = static_cast<float>(timeKeeper.size());
	float average = std::accumulate(timeKeeper.begin(), timeKeeper.end(), 0.0) / count;
	std::cout << "You scored: " << gameScore << " / " << gameCounter << std::endl;
	std::cout << "Your average: " << percentage(gameScore, gameCounter) << "%" << std::endl;
	std::cout << "Average time per question: " << average << " : Seconds" << std::endl;
}

int runGame() {
	int gameCounter = 0; 
	int gameScore = 0; 
	bool timedOut = false;
	std::vector<std::pair<double, std::string>> scoreBoard;
	std::vector<float> timeKeeper;

	std::vector<std::string> files = { "Alps.txt", "Carpathians.txt", "Icelandic Highlands.txt", "Pyrenees.txt" };
	Mountains mountainObject(files); 
	std::vector<std::string> mountainRange = vectorTrim(files);

	while (true) { 
		bool isTrue;
		std::string userInput;
		std::string randomMountain = mountainObject.getRandomMountain();
		std::cout << "\n";
		std::cout << "Which mountain range does the following mountain belong too: " << randomMountain << "\n";
		std::cout << "[1]" << mountainRange[0] << "   " << "[2]" << mountainRange[1] << "   " << "[3]" << mountainRange[2] << "   " << "[4]" << mountainRange[3] << std::endl;
		std::chrono::steady_clock::time_point t = std::chrono::steady_clock::now();
		bool inputReceived = false;
		time_t startTime = time(NULL);
		time_t waitTime = 10;
		
		std::thread t1([&]() {
			std::cin >> userInput;
		inputReceived = true;
			});
		t1.detach();
		// check the inputReceived flag once every 50ms for 10 seconds
		while (time(NULL) < startTime + waitTime && !inputReceived) {
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
		}
		if (inputReceived) {
			long double elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - t).count() / 1000000000.0;
			timeKeeper.push_back(elapsed);
			if (userInput == "score") {
				viewScoreBoard(scoreBoard);
				viewPercentages(gameScore, gameCounter, timeKeeper);
			}
			if (userInput == "quit" || userInput == "exit") {
				viewScoreBoard(scoreBoard);
				viewPercentages(gameScore, gameCounter, timeKeeper);
				std::cout << "Game Exited" << std::endl;
				exit(1);
			}
			if (checkInteger(userInput) == true) {
				//Checks if it's an int then converts into an int 
				int userInputInt = std::stoi(userInput);
				if (userInputInt > 0 && userInputInt <= mountainRange.size()) {
					isTrue = mountainObject.checkRange(randomMountain, mountainRange[userInputInt - 1]);
					if (isTrue == true) {
						gameCounter = gameCounter + 1;
						gameScore = gameScore + 1;
						std::cout << "Correct!, Your score is now " << gameScore << " / " << gameCounter << " Answered in : " << elapsed << std::endl;
						scoreBoard.push_back(std::make_pair(elapsed, randomMountain));
					}
					else if (isTrue == false) {
						gameCounter = gameCounter + 1;
						std::cout << "Incorrect, your score is now " << gameScore << " / " << gameCounter << std::endl;
					}
				}
				else {
					std::cout << "Invalid input please enter a 1,2,3,4 or type 'quit' or 'exit' or 'score'" << std::endl;
				}
			}
			else {
				std::cout << "Invalid input please enter a 1,2,3,4 or type 'quit' or 'exit' or 'score'" << std::endl;
			}
		}
		else {
			gameCounter = gameCounter + 1;
			std::cout << "\n";
			std::cout << "You were too slow to answer, Your score is now " << gameScore << " / " << gameCounter << std::endl;
		}
	}
	return 0;
}

int main() {
	std::cout << "Welcome to RangeCheck, a quiz game to test your knowledge about mountains!" << std::endl;
	std::cout << "Rules are simple you will be presented with a mountain and you must select the range it belongs too." << std::endl;
	std::cout << "Enter 1,2,3,4 to answer or enther 'exit' or 'quit' to stop playing" << std::endl;
	std::cout << "Enter 'score' to view your fastest times and if you take longer than 10 seconds your answer will be marked incorrect" << std::endl;
	std::cout << "\n";
	runGame();
}