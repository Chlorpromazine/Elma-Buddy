#pragma once
#include "DEH.h"


class Objects {

private:
	int curObject;
	
public:
	static Objects obj;
	Objects();

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
	std::unordered_map<int, newProp> allObjectsNewPropertiesPrev;

	bool reload;

	
	void changeObject(int curObj);
	void objectActive(int curObj, bool active);
	void nextObject();
	void moveObject(int);

	pos getLocation();
	pos getLocation(int obj);
	
	void newLocation(pos);

	void displayObjectNumbers();

	//Display arrow
	std::vector<std::string> arrowObjectList = { "Off", "Closest Apple", "Closest Flower", "Closest Apple & Flower" };
	//selected arrow object value
	int arrowObjectValue = 0;
	void displayObjectArrow();

	int getClosestObject(objType type);

	
};
