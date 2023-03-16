#include "Mountains.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>

#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std::chrono_literals;

int timeOut() {
	std::this_thread::sleep_for(10s);
	return 1;
}
int timeOutWrapper() {
	std::mutex m;
	std::condition_variable cv;
	int retValue = 1;

	std::thread t([&cv, &retValue]() {

		retValue = timeOut();
		cv.notify_one();
		});
	t.detach();
	{	
		std::unique_lock<std::mutex> l(m);
		if (cv.wait_for(l, 10s) == std::cv_status::timeout) {
			//exit(1);
			throw std::runtime_error("You were too slow");
		}
	}	
	return retValue;
}
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
//Time complexity: O(24) + O(n) + O(n) + O(n) + O(n) = O(n)
int runGame() {
	int gameCounter = 0; //O(1)
	int gameScore = 0; //O(1)
	bool timedOut = false;
	std::vector<std::pair<double, std::string>> scoreBoard;

	std::vector<std::string> files = { "Alps.txt", "Carpathians.txt", "Icelandic Highlands.txt", "Pyrenees.txt" }; //O(1)
	Mountains mountainObject(files); //O(n)
	std::vector<std::string> mountainRange = vectorTrim(files); //O(n)

	while (true) { //O(1)
		bool isTrue;//O(1)
		//std::string userInput;//O(1)
		std::string userInput;
		std::string randomMountain = mountainObject.getRandomMountain(); //O(n)
		std::cout << "\n";
		std::cout << "Which mountain range does the following mountain belong too: " << randomMountain << "\n"; //O(1)
		std::cout << "[1]" << mountainRange[0] << "   " << "[2]" << mountainRange[1] << "   " << "[3]" << mountainRange[2] << "   " << "[4]" << mountainRange[3] << std::endl; //O(1)
		//ADDED
		std::chrono::steady_clock::time_point t = std::chrono::steady_clock::now();
		//ADDED
		//std::cin >> userInput;
		//int x;
		bool inputReceived = false;
		time_t startTime = time(NULL);
		time_t waitTime = 10;

		//std::cout << "Enter a number within " << waitTime << " seconds\n";

		// spawn a concurrent thread that waits for input from std::cin
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
			if (userInput == "score") {
				viewScoreBoard(scoreBoard);
				std::cout << "Your average: " << percentage(gameScore, gameCounter) << "%" << std::endl;
			}
			if (userInput == "quit" || userInput == "exit") { //O(1)
				viewScoreBoard(scoreBoard);
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
						std::cout << "Correct!, Your score is now " << gameScore << " / " << gameCounter << " Answered in : " << elapsed << std::endl; //O(1)
						scoreBoard.push_back(std::make_pair(elapsed, randomMountain));
					}
					else if (isTrue == false) { //O(1)
						gameCounter = gameCounter + 1; //O(1)
						std::cout << "Incorrect, your score is now " << gameScore << " / " << gameCounter << std::endl; //O(1)
					}
				}
				else {
					std::cout << "Invalid input please enter a 1,2,3,4 or type 'quit' or 'exit' or 'score'" << std::endl; //O(1)
				}
			}
			else {
				std::cout << "Invalid input please enter a 1,2,3,4 or type 'quit' or 'exit' or 'score'" << std::endl; //O(1)
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

	

//Time complexity: O(4) + O(n) = O(n)
int main() {
	std::cout << "Welcome to RangeCheck, a quiz game to test your knowledge about mountains!" << std::endl; //O(1)
	std::cout << "Rules are simple you will be presented with a mountain and you must select the range it belongs too." << std::endl; //O(1)
	std::cout << "Enter 1,2,3,4 to answer or enther 'exit' or 'quit' to stop playing" << std::endl; //O(1)
	std::cout << "Enter 'score' to view your fastest times and if you take longer than 10 seconds your answer will be marked incorrect" << std::endl;
	std::cout << "\n"; //O(1)
	runGame();

}