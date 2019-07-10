#pragma once
#include "DEH.h"

class Level {
private:
	//Gets the name/LGR of the current level being played.
	int LevName = 0x00485674;
	int LGRNameAddr = 0x0048564C;
	int framesPerSecond = 0x00447418;
public:
	static Level lev;

	std::vector<std::string> LGRlist;
	int LGRselected = 0;
	bool LGRchanged = true;

	void initLevel();

	void changeLGR();
	void getLGRlist();
	int findIndexLGR(std::string LGRname);

	double getTimeInLevel();

	std::string decimalTimeToStr(double timeDec);

	std::string getLevelName();

	int timeAddress;
};