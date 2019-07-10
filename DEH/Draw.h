#pragma once
#include "DEH.h"

static int TextDrawFunction = 0x00401340;
static int RectFillDrawFunction = 0x00429580;
static int fontText = *(int*)0x00499164;
static int playingSurf = *(int*)0x00454140;
static int PixelDrawFunction = 0x00429490;// 0x004294F0;// 0x0042A730; //0x00429650;// 0x00429490; // 0x004294F0; //0x0042A6A0;

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
		Circle,
		Line,
		LineArrow
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

	struct stDrawLine {
		int x;
		int y;
		int x2;
		int y2;
		int surface;
		int color;
		double maxLength;
		double minLength;
	};

	struct stDrawCircle {
		int x;
		int y;
		int rad;
		int surface;
		int color;
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

	void drawPixel(int x, int y, int color, int surface);
	
	void drawLine(int x1, int y1, int x2, int y2, int color, int surface = playingSurf);

	void createLineArrow(int x1, int y1, int x2, int y2, int color, double maxLength = -1, double minLength = -1);

	void drawCircle(int x, int y, int rad, int color, int surface);

	
	
	

	//todo: struct for parameters would look cleaner. Or class
	void createText(char* objName, std::string text, int x, int y, int zOrd, char* parent, bool visible = true, int surface = playingSurf, int charSpace = -1000, int font = fontText);
	void createRectFill(char* objName, BYTE color, int x, int y, int height, int width, int zOrd, char* parent = "", bool visible = true, int surface = playingSurf);

	void createLine(char * objName, int x, int y, int x2, int y2, int color, drawType type, double maxLength = -1, double minLength = -1, int zOrd = 1, char * parent = "", bool visible = true, int surface = playingSurf);


	void createCircle(char* objName, int x, int y, int rad, int color, int zOrd = 1, char* parent = "", bool visible = true, int surface = playingSurf);

	void deleteObjectFromArray(char* name);



	SIZE getSizeString(char* c, HFONT h);

	std::list<drawObject> DrawingObjects;
	std::list<drawObject> DrawingObjectsBuffer;

};

