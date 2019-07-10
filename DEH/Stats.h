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
	bool displayTimeAppleTaken = true;


	int currentLevelFinish = 0;
	int currentLevelDeaths = 0;
	int currentLevelEsc = 0;
};

