#pragma once
#include "DEH.h"


class objects {

private:
	int curObject;
	char oldLev[8];

public:
	static objects obj;
	objects();

	struct pos {
		double x;
		 double y;
	};

	enum objType{ Flower = 1, Apple, Killer, Start };

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

	struct newProp {
		double bestTime = 0;
		std::string bestTimeStr;
	};

	std::vector<objStruct*> allObjects;
	std::unordered_map<int, newProp> allObjectsNewProperties;

	bool reload;


	void changeObject(int curObj);
	void objectActive(int curObj, bool active);
	void nextObject();
	void moveObject(int);

	pos getLocation();
	pos getLocation(int obj);
	
	void newLocation(pos);

	void displayObjectNumbers();

	void displayObjectArrow();

	int getClosestObject(objType type);

	
};
