#pragma once
#include "DEH.h"

class Kuski {
public:
	struct coord {
		double x;
		double y;
		coord(double X, double Y) {
			x = X;
			y = Y;
		}
		coord() {

		}
	};
	
	struct bikePoints {
		coord bike;
		coord lWheel;
		coord rWheel;
		coord head;
		bikePoints() {
			
		}
	};
private:
	std::vector<bikePoints> prevKuskiRide;
	std::vector<bikePoints> kuskiRide;
	int currentFPS = 0;
	double delayOfDeathMS = 1000;

public:
	static Kuski kus;

	enum  { bikePosX = 0x00453A20, lWheelPosX = 0x00453A88, rWheelPosX = 0x00453Af0, headPosX = 0x00453b30 };
	enum  { bikePosY = 0x00453A28, lWheelPosY = 0x00453A90, rWheelPosY = 0x00453Af8, headPosY = 0x00453b38 };

	
	//Invulnerability
	std::vector<std::string> invulnerabilityList = { "None", "To Killers", "To Floor", "To All" };
	//selected invulnerabily value
	int invulnerabilityValue = 0;

	void toggleInvulnerability(int toggle);
	void toggleInvulnerabilityFloor(bool toggle);
	void toggleInvulnerabilityKillers(bool toggle);


	//Acceleration
	void accelerationOfKuski(double speed);


	//Shadow Kuski
	std::vector<std::string> shadowKuskiList = { "Off", "Last Played", "Best Completed Time" };
	//selected shadow kuski value
	int shadowKuskiValue = 0;
	int prevShadowKuskiValue = 0;
	int shadowLastBestTime = 0;
	int shadowCurrentTime = 0;

	void shadowKuski();
	void saveCurrentRide();
	void setDeathDelay(int ms);


	//On exit/enter
	void onExitLevel();
	void enterNewLevel();
};