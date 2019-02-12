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

	//Undefined behaviour, fuck off, don't care.
	unsigned int tmpValueRight = *(int*)((int)&speed + 0x04);
	speed *= -1; //negative for left wheel
	unsigned int tmpValueLeft = *(int*)((int)&speed + 0x04);

	//Right wheel:
	MemPatchInt((BYTE*)0x00420D17, &tmpValueRight, 4);

	//Left wheel:
	MemPatchInt((BYTE*)0x00420CF2, &tmpValueLeft, 4);

}