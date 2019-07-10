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


public:
	static Kuski kus;

	enum  { bikePosX = 0x00453A20, lWheelPosX = 0x00453A88, rWheelPosX = 0x00453Af0, headPosX = 0x00453b30 };
	enum  { bikePosY = 0x00453A28, lWheelPosY = 0x00453A90, rWheelPosY = 0x00453Af8, headPosY = 0x00453b38 };

	
	bool enableKuskiShadow = true;

	void toggleInvulnerability(bool toggle);
	void toggleInvulnerabilityFloor(bool toggle);
	void toggleInvulnerabilityKillers(bool toggle);

	void accelerationOfKuski(double speed);

	void shadowKuski();
	void saveCurrentRide();
	void onExitLevel();
	void enterNewLevel();
};