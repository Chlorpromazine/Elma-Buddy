#include "Kuski.h"

Kuski Kuski::kus;

void Kuski::toggleInvulnerability(bool toggle)
{
	toggleInvulnerabilityFloor(toggle);
	toggleInvulnerabilityKillers(toggle);
}

void Kuski::toggleInvulnerabilityFloor(bool toggle)
{
	//Old bytecode to detect collision.
	BYTE data[5] = { 0x8B, 0x0D, 0x1C, 0x38, 0x45 };
	BYTE* addr = (BYTE*)0x00422874;

	if (toggle) {
		//Remove the collision check
		for (int i = 0; i < 5; i++) data[i] = 0x00;
		MemPatch(addr, data, 5);
	}
	else {
		//Place the collision check
		MemPatch(addr, data, 5);
	}
}

void Kuski::toggleInvulnerabilityKillers(bool toggle)
{
	//Old bytecode to detect collision.
	BYTE data[6] = { 0xC7, 0x02, 0x00, 0x00, 0x00 , 0x00 };
	BYTE* addr = (BYTE*)0x0041FC91;

	if (toggle) {
		//Remove the collision check
		MemPatch(addr, data, 6);
	}
	else {
		//Place the collision check
		data[5] = 0x01;
		MemPatch(addr, data, 6);
	}
}

/*
*	Changes the speed of which the kuski accelerates.
*	Default value: 600
*	Can be negative.
*/
void Kuski::accelerationOfKuski(double speed) 
{

	//Going too fast will just crash
	if (speed > 3000) speed = 3000;
	else if (speed < 0) speed = 0;

	//Undefined behaviour
	unsigned int tmpValueRight = *(int*)((int)&speed + 0x04);
	speed *= -1; //negative for left wheel
	unsigned int tmpValueLeft = *(int*)((int)&speed + 0x04);

	//Right wheel:
	MemPatchInt((BYTE*)0x00420D17, &tmpValueRight, 4);

	//Left wheel:
	MemPatchInt((BYTE*)0x00420CF2, &tmpValueLeft, 4);

}

void Kuski::shadowKuski()
{
	const int sizeWheel = 18;
	const int sizeHead = 12;
	const int sizeBike = 5;
	const int screenSize = 48;
	const int centerBikeX = Addr.WindowWidth / 2 - *(double*)bikePosX * screenSize;
	const int centerBikeY = Addr.WindowHeight / 2 - *(double*)bikePosY * screenSize;

	//Go to the last fps if we ended the replay
	if (currentFPS == prevKuskiRide.size() && currentFPS != 0) currentFPS--;

	if (currentFPS < prevKuskiRide.size() && enableKuskiShadow)
	{
		int lWheelX = prevKuskiRide[currentFPS].lWheel.x * screenSize + centerBikeX;
		int lWheelY = prevKuskiRide[currentFPS].lWheel.y * screenSize + centerBikeY;

		int rWheelX = prevKuskiRide[currentFPS].rWheel.x * screenSize + centerBikeX;
		int rWheelY = prevKuskiRide[currentFPS].rWheel.y * screenSize + centerBikeY;

		//Head is calculated differently for some reason (1.44 comes from the static value of 0x004537F0, 0.44)
		int headX = (prevKuskiRide[currentFPS].head.x + ((prevKuskiRide[currentFPS].head.x - prevKuskiRide[currentFPS].bike.x))*1.44) * screenSize + centerBikeX;
		int headY = (prevKuskiRide[currentFPS].head.y + ((prevKuskiRide[currentFPS].head.y - prevKuskiRide[currentFPS].bike.y))*1.44) * screenSize + centerBikeY ;

		int bikeX = prevKuskiRide[currentFPS].bike.x * screenSize + centerBikeX;
		int bikeY = prevKuskiRide[currentFPS].bike.y * screenSize + centerBikeY;

		draw::dd.createCircle("lWheelShadow", lWheelX, lWheelY, sizeWheel, Colors.LightOrange);
		draw::dd.createCircle("rWheelShadow", rWheelX, rWheelY, sizeWheel, Colors.LightOrange);
		draw::dd.createCircle("headShadow", headX, headY, sizeHead, Colors.LightOrange);
		draw::dd.createCircle("bodyShadow", bikeX, bikeY, sizeBike, Colors.LightGreen);

		currentFPS++;
	}
	else if (!enableKuskiShadow)
	{
		draw::dd.createCircle("lWheelShadow", 0, 0, 0, 0);
		draw::dd.createCircle("rWheelShadow", 0, 0, 0, 0);
		draw::dd.createCircle("headShadow", 0, 0, 0, 0);
		draw::dd.createCircle("bodyShadow", 0, 0, 0, 0);
	}
	
	
}

void Kuski::saveCurrentRide()
{
	bikePoints currentLocation;
	currentLocation.bike = coord(*(double*)bikePosX, *(double*)bikePosY);
	currentLocation.lWheel = coord(*(double*)lWheelPosX, *(double*)lWheelPosY);
	currentLocation.rWheel = coord(*(double*)rWheelPosX, *(double*)rWheelPosY);
	currentLocation.head = coord(*(double*)headPosX, *(double*)headPosY);

	kuskiRide.push_back(currentLocation);
	
}

void Kuski::onExitLevel()
{
	prevKuskiRide = kuskiRide;
	kuskiRide.clear();
	currentFPS = 0;
}

void Kuski::enterNewLevel()
{
	kuskiRide.clear();
	prevKuskiRide.clear();
	currentFPS = 0;
}