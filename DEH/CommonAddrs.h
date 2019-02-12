#pragma once
#include "DEH.h"

class commonAddresses {
public:
	std::string IPtoS(int i);
	
	

	//Collision (objects):
	//Returns the object ID being collided with.
	int ObjectIDCollided = *(int*)0x004869E0;

	//Returns the current screen that you're on.
	int CurrentScreen = 0x004a1404;





	//Window height/width
	int WindowHeight = *(int*)0x004495EC;
	int WindowWidth = *(int*)0x004495E8;


} static Addr;

 

#define degree2radian(a) (a * 0.017453292519)


