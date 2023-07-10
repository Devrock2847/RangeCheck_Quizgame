#pragma once
#include<vector>
#include<string>
#include<map>

/**
* Mountains class, holds majority of data used within the quiz
*/

class Mountains {
	std::vector<std::string> vectorious; /*< Random vector used througout code */
	std::map < std::string, std::vector<std::string> > data; /*< Main data structure used to store imported files */
	std::string fileType; /*< Variabe used to identify the file type */
	
public:
	/**
	* Variable used to exit program as part of source.cpp 
	*/
	bool triggerBool = false;
	/**
	* Constructor for the mountains class
	* @param string filenames consisting of full file names such as "Alps.txt" because on call it will trim them
	*/
	Mountains(std::vector<std::string>& filenames);
	/**
	* Pulls a random mountain from multiple different files 
	* @return string with value of random mountain 
	*/
	std::string getRandomMountain();
	/**
	* Checks if a mountain belongs to a certain range 
	* @param string mountain requires the individual mountain name
	* @param string range requires the mountain range chosen by the user
	* @return boolean value shows true if mountain does belong to that range and false if not 
	*/
	bool checkRange(std::string mountain, std::string range);
	/**
	* Checks file type and exits the program if filetype is not compatable
	* @param string file takes a filename like "Alps.txt" and checks the type ".txt" is compatable with the program before it attempts to load it
	* @return boolean value shows true if filetype is incompatible and remains false if it is compatable
	*/
	bool checkFileType(std::string file);
	/**
	* Default deconstructor
	*/
	~Mountains();
};