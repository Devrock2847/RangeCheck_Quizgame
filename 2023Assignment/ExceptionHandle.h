#pragma once
#include <iostream>
#include "Mountains.h"
#include <exception>

class ExceptionHandle : public std::exception {
public:
	const char* ex() {
		//TODO add exception warning here
		return "Incorrect file format, please try again";
	}

};

