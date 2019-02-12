#pragma once
#include "DEH.h"

static int TextDrawFunction = 0x00401340;
static int RectFillDrawFunction = 0x00429580;
static int fontText = *(int*)0x00499164;
static int playingSurf = *(int*)0x00454140;

class draw {
private:
	int screenWidth;
	int screenHeight;
	int screenX;
	int screenY;
	bool activeCursor;
	
	bool renewDraw = false;
public:
	static draw dd;
	
	//enums
	enum drawType {
		Text,
		Rect,
		Circle
	};

	//Structs
	struct drawObject {
		char* name;
		char* parentName;
		int zOrder; //Adding this so we can more easily order things.
		drawType type;
		void* object;
		bool visible;
	};

	struct stDrawText {
		int charSpace; //Space between each characters (-1000 = default)
		std::string text;
		int x;
		int y;
		int currSurface;
		int font;
	};

	struct stDrawRect {
		BYTE color;
		int x;
		int y;
		int x2;
		int y2;
		int surface;
	};

	//Vars
	bool optionsUIactive = false;
	bool optionsUIChanged = false;

	bool statsChanged = false;

	//Functions
	void initDraw();
	void updateStats();
	void OptionsScreen(bool show);
	
	
	void drawAllObjectsOnScreen();
	

	void drawTextScreen(int brush, std::string text, int x, int y, int charSpace, int surface);
	void drawRectFillScreen(BYTE color, int x, int y,int x2, int y2, int surface);

	

	//todo: struct for parameters would look cleaner. Or class
	void createText(char* objName, std::string text, int x, int y, int zOrd, char* parent, bool visible = true, int surface = playingSurf, int charSpace = -1000, int font = fontText);
	void createRectFill(char* objName, BYTE color, int x, int y, int height, int width, int zOrd, char* parent = "", bool visible = true, int surface = playingSurf);

	void deleteObjectFromArray(char* name);



	SIZE getSizeString(char* c, HFONT h);

	std::list<drawObject> DrawingObjects;
	std::list<drawObject> DrawingObjectsBuffer;

};

