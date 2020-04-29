#pragma once
#include "DEH.h"





class Polygons {
private:
	
public:
	static Polygons Pol;

	void initPolygons();

	int polygonObjStart = 0;

#pragma pack(push, 1)
	struct polStruct {
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
};