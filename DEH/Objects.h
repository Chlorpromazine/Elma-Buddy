#pragma once
#include "DEH.h"

using namespace std;


class objects {

public:
	static objects obj;
	objects();

	struct pos {
		 int x;
		 int y;
	};
#pragma pack(push, 1)
	struct objStruct{
		double x;
		double y;
		int _1;
		int _2;
		int xMap;
		int yMap;
		int type;
		int gravity;
		int animation;
		bool active;
	};
#pragma pack(pop)
	vector<objStruct*> allObjects;
	bool reload;


private:
	int curObject;
	char oldLev[8];

public:
	void changeObject(int curObj);
	void objectActive(int curObj, bool active);
	void nextObject();
	void moveObject(int);
	pos getLocation();
	pos getLocation(int obj);
	
	void newLocation(pos);

	void displayObjectNumbers();

	

};
