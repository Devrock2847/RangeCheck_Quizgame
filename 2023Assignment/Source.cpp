#include "Mountains.h"
#include "Calculations.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>

int runGame() {
	int gameCounter = 0; 
	int gameScore = 0; 
	bool timedOut = false;
	std::vector<std::pair<double, std::string>> scoreBoard;
	std::vector<float> timeKeeper;

	std::vector<std::string> files = { "Alps.txt", "Carpathians.txt", "Icelandic Highlands.txt", "Pyrenees.txt" };
	Mountains mountainObject(files); 
	Calculations calculationObject;
	std::vector<std::string> mountainRange = calculationObject.vectorTrim(files);

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
				calculationObject.viewScoreBoard(scoreBoard);
				calculationObject.viewPercentages(gameScore, gameCounter, timeKeeper);
			}
			if (userInput == "quit" || userInput == "exit") {
				calculationObject.viewScoreBoard(scoreBoard);
				calculationObject.viewPercentages(gameScore, gameCounter, timeKeeper);
				std::cout << "Game Exited" << std::endl;
				exit(1);
			}
			if (calculationObject.checkInteger(userInput) == true) {
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