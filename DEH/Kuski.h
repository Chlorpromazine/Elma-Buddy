#pragma once
#include "DEH.h"

class Kuski {
private:
	

public:
	static Kuski kus;

	enum  { bikePosX = 0x00453A20, lWheelPosX = 0x00453A88, rWheelPosX = 0x00453Af0, headPosX = 0x00453b30 };
	enum  { bikePosY = 0x00453A28, lWheelPosY = 0x00453A90, rWheelPosY = 0x00453Af8, headPosY = 0x00453b38 };


	void toggleInvulnerability(bool toggle);
	void toggleInvulnerabilityFloor(bool toggle);
	void toggleInvulnerabilityKillers(bool toggle);

	void accelerationOfKuski(double speed);


};