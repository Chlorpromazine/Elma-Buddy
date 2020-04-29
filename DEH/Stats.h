#pragma once
#include "DEH.h"

class Stats {
private:
	int ApplesTotal = 0x0045E524;
	int ApplesCollected = 0x00453B50;
public:
	static Stats stats;

	void initPatch();

	int getLevApplesTotal();
	int getLevAppleCollected();

	bool displayAppleCounter = true;
	bool displayDeathCounter = true;
	bool displayAppleGravity = true;
	
	//Show time of apple taken
	std::vector<std::string> timeAppleTakenList = { "Off", "Global Best Time", "Best Completed Time" };
	//selected time of apple taken option
	int timeAppleTakenValue = 0;

	void escapeKeyExitLev();
	void killedExitLev();
	void finishExitLev();

	int currentLevelFinish = 0;
	int currentLevelDeaths = 0;
	int currentLevelEsc = 0;

	char* failedToFinishNewString = "";
};

