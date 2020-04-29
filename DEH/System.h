#pragma once
#include "DEH.h"

class System {
private:
	
public:
	static System sys;

	//Timestamp
	std::vector<std::string> chatTimestampList = { "Off", "hh:mm", "hh:mm:ss" };
	//Selected Timestamp value
	int chatTimestampValue = 0;

	char* getUserTime();
};

