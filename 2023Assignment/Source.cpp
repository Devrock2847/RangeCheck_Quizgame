#include "Mountains.h"
#include "Calculations.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <exception>

int runGame() {
	//! gameCounter will total the amount of games played 
	int gameCounter = 0; 
	//gameScore will total the amount of games won by the user 
	int gameScore = 0; 
	//boolean value used in try catch block
	bool isTrue;
	//timedOut is generic boolean required for the 10s timeout function
	bool timedOut = false;
	//scoreBoard is a generic variable that will be populated with the viewScoreBoard function
	std::vector<std::pair<double, std::string>> scoreBoard;
	//timeKeeper stores the times the user takes to answer a question
	std::vector<float> timeKeeper;
	//declaration of the filenames used within the project structure
	std::vector<std::string> files = { "Aps.txt", "Carpathians.txt", "Icelandic Highlands.txt", "Pyrenees.txt" };
	//creates an object of the Mountains class
	Mountains mountainObject(files);
	//Checks files for compatibility priory to reading 
	try {
		for (int i = 0; i < files.size(); i++) {
			//informs user of the filetypes
			std::cout << "Checking filetype of " << files[i] << std::endl;
			//true if filetype is compatible and false if not
			isTrue = mountainObject.checkFileType(files[i]);
			if (isTrue = false) {
				throw isTrue;
			}
		}
	} catch (bool isTrue) {
		//Exits game when incompatable file type is found
		std::cout << "Filetype is incompatible, exiting program." << std::endl;
		exit(EXIT_FAILURE);
	}
	//triggerBool is triggered when an invalid file is attempted to be loaded 
	if (mountainObject.triggerBool == true) {
		std::cout << "Filetype is incompatible, exiting program." << std::endl;
		exit(EXIT_FAILURE);
	}
	
	//creates an object of the Calculations class
	Calculations calculationObject;
	//calls vectorTrim to take the filenames and remove the filetype from them and place them into a new vector with the values; { "Alps", "Carpathians", "Icelandic Highlands", "Pyrenees" }
	std::vector<std::string> mountainRange = calculationObject.vectorTrim(files);
	//while loop put the game in infinite loop unless the user types 'quit' or 'exit'
	while (true) { 
		//generic variables that will be used later 
		bool isTrue;
		std::string userInput;
		//calls getRandomMountain from the Mountains class to give a random mountain from the 4 text files
		std::string randomMountain = mountainObject.getRandomMountain();
		//Presents the user with the question of where the mountain belongs
		std::cout << "\n";
		std::cout << "Which mountain range does the following mountain belong too: " << randomMountain << "\n";
		//presents the user with 4 different mountain ranges calling from the mountainRange variable initialised on line 28
		std::cout << "[1]" << mountainRange[0] << "   " << "[2]" << mountainRange[1] << "   " << "[3]" << mountainRange[2] << "   " << "[4]" << mountainRange[3] << std::endl;
		//The program tracks how quickly a user answers the question, the timer starts with this line
		std::chrono::steady_clock::time_point t = std::chrono::steady_clock::now();
		//inputReceived remains false untill the user has submitted there answer 
		bool inputReceived = false;
		//starts the 10s timeout counter at 0
		time_t startTime = time(NULL);
		//this is the timeout number, if the timeout needs to be changed this is the place to do it.
		time_t waitTime = 10;
		//a thread asks for the userInput(to answer the question) and changes inputReceieved to true when the input is received therby restarting the loop
		std::thread t1([&]() {
			std::cin >> userInput;
		inputReceived = true;
			});
		t1.detach();
		// check the inputReceived flag once every 50ms for 10 seconds 
		while (time(NULL) < startTime + waitTime && !inputReceived) {
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
		}
		//if the user inputs an answer within the 10s this code runs
		if (inputReceived) {
			//stops the clock and logs it into a variable, uses nanoseconds for the count then converts it to seconds using / 1000000000.0
			long double elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - t).count() / 1000000000.0;
			//adds the logged time to the timeKeeper vector called on line 20
			timeKeeper.push_back(elapsed);
			//if the user enters "score" they will be presented with the scoreBoard, the details can be found in the Calculations.cpp file
			if (userInput == "score") {
				calculationObject.viewScoreBoard(scoreBoard);
				calculationObject.viewPercentages(gameScore, gameCounter, timeKeeper);
			}
			//if the user enters "quit" or "exit" the program will show the scoreboard and then exit
			if (userInput == "quit" || userInput == "exit") {
				calculationObject.viewScoreBoard(scoreBoard);
				calculationObject.viewPercentages(gameScore, gameCounter, timeKeeper);
				std::cout << "Game Exited" << std::endl;
				exit(1);
			}
			//checks if the user entered an integer despite the input being of type string
			if (calculationObject.checkInteger(userInput) == true) {
				//if the user has entered an int, convert it from string to int
				int userInputInt = std::stoi(userInput);
				//checks if the number is between 0 and the length of the array that holds the answers that were presented to the user
				if (userInputInt > 0 && userInputInt <= mountainRange.size()) {
					//checks if the user is correct with there answer with the checkRange function in the Mountains class 
					//the -1 at the end is because the user is presented with numbers begining at 1 and vectors start at 0
					isTrue = mountainObject.checkRange(randomMountain, mountainRange[userInputInt - 1]);
					//if the user is correct
					if (isTrue == true) {
						//adds +1 to both the gameCounter and the gameScore
						gameCounter = gameCounter + 1;
						gameScore = gameScore + 1;
						//announces to the user they were correct with the gameScore, gameCounter and the time they took to answer the question
						std::cout << "Correct!, Your score is now " << gameScore << " / " << gameCounter << " Answered in : " << elapsed << std::endl;
						//Adds the correct answer to the scoreBoard with the time taken to answer it
						scoreBoard.push_back(std::make_pair(elapsed, randomMountain));
					}
					//if the user is incorrect only the gameCounter is increased
					else if (isTrue == false) {
						gameCounter = gameCounter + 1;
						//the user is informed they were incorrect with an updated score to game counter
						std::cout << "Incorrect, your score is now " << gameScore << " / " << gameCounter << std::endl;
					}
				}
				//if the userInput is a integer but is not within the parameters of the game, in this case between 1-4
				else {
					std::cout << "Invalid input please enter a 1,2,3,4 or type 'quit' or 'exit' or 'score'" << std::endl;
				}
			}
			//if the user did not enter an integer 
			else {
				std::cout << "Invalid input please enter a 1,2,3,4 or type 'quit' or 'exit' or 'score'" << std::endl;
			}
		}
		//if the user did not input an answer before the 10s timeout this code will run telling them they were too slow and adding the incorrect answer to the total
		else {
			gameCounter = gameCounter + 1;
			std::cout << "\n";
			std::cout << "You were too slow to answer, Your score is now " << gameScore << " / " << gameCounter << std::endl;
		}
	}
	//! if this point is ever met by the program it will break the loop, although by design it should never be met
	return 0;
}

int main() {
	//Explaining the rules to the game prior to the main while loop
	std::cout << "Welcome to RangeCheck, a quiz game to test your knowledge about mountains!" << std::endl;
	std::cout << "Rules are simple you will be presented with a mountain and you must select the range it belongs too." << std::endl;
	std::cout << "Enter 1,2,3,4 to answer or enther 'exit' or 'quit' to stop playing" << std::endl;
	std::cout << "Enter 'score' to view your fastest times and if you take longer than 10 seconds your answer will be marked incorrect" << std::endl;
	std::cout << "\n";
	//calls for the game to be run 
	runGame();
}