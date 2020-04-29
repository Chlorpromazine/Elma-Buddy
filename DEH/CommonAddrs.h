#pragma once
#include "DEH.h"

class commonAddresses {
public:

	std::string IPtoS(int i);
	
	

	//Collision (objects):
	//Returns the object ID being collided with.
	int ObjectIDCollided = 0x004869E0;

	//Returns the current screen that you're on.
	int CurrentScreen = 0x004a1404;





	//Window height/width
	int WindowHeight = 0x004495EC;
	int WindowWidth = 0x004495E8;

	int mainHWND = 0x0048df6c;

	

} static Addr;

 

#define degree2radian(a) (a * 0.017453292519)


