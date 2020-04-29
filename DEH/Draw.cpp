#pragma once
#include "Draw.h"

draw draw::dd;

void draw::initDraw() 
{
	

}

void draw::createText(char *objName, std::string text, int x, int y, int zOrd, char* parent = "", bool visible, int surface, int charSpace, int font)
{
	
	//If the name is already used, change it instead.
	auto result = std::find_if(std::begin(DrawingObjects), std::end(DrawingObjects), [objName](const auto & n) {
		
		return strcmp(n.name, objName) == 0 && n.type == drawType::Text;
	});
	
	//create text object
	stDrawText* textStruct = new stDrawText;
	textStruct->charSpace = charSpace;
	textStruct->currSurface = surface;
	textStruct->font = font;
	textStruct->text = text;
	textStruct->x = x;
	textStruct->y = y;

	if (!DrawingObjects.empty() && result != DrawingObjects.end())
	{

		//Modify the current object if found. (name/type stays the same)
		result->zOrder = zOrd;
		result->parentName = parent;
		result->visible = visible;

		//Delete old value
		delete result->object;

		result->object = textStruct;

	}
	else
	{
		
		//Add the object if not found.
		drawObject genericObj;
		genericObj.name = objName;
		genericObj.type = drawType::Text;
		genericObj.zOrder = zOrd;
		genericObj.parentName = parent;
		genericObj.visible = visible;

		genericObj.object = textStruct;

		DrawingObjects.push_back(genericObj);
		
		//Sort for zOrder. (lowest number = first drawn/under all)
		DrawingObjects.sort([](drawObject const  a, drawObject const  b) {return a.zOrder < b.zOrder; });
	}
	
}

void draw::createRectFill(char* objName, BYTE color, int x, int y, int x2, int y2, int zOrd, char* parent, bool visible, int surface)
{
	
	
	//If the name is already used, change it instead.
	auto result = std::find_if(std::begin(DrawingObjects), std::end(DrawingObjects), [objName](const auto & n) {
		return strcmp(n.name, objName) == 0 && n.type == drawType::Rect;
	});
	drawObject genericObj;

	//create rectangle object
	stDrawRect* rectStruct = new stDrawRect;
	rectStruct->color = color;
	rectStruct->x = x;
	rectStruct->y = y;
	rectStruct->x2 = x2;
	rectStruct->y2 = y2;
	rectStruct->surface = surface;

	if (!DrawingObjects.empty() && result != DrawingObjects.end())
	{
		//Modify the current object if found. (name/type stays the same)
		result->zOrder = zOrd;
		result->parentName = parent;
		result->visible = visible;

		//Delete old value		
		delete result->object;

		result->object = rectStruct;
		
	}
	else 
	{
		
		//Add the object if not found.
		genericObj.name = objName;
		genericObj.parentName = parent;
		genericObj.type = drawType::Rect;
		genericObj.zOrder = zOrd;
		genericObj.visible = visible;

		genericObj.object = rectStruct;

		DrawingObjects.push_back(genericObj);
		
		//Sort for zOrder. (lowest number = first drawn/under all)
		DrawingObjects.sort([](drawObject const  a, drawObject const  b) {return a.zOrder < b.zOrder; });
		
	}
	
}


void draw::createLine(char* objName, int x, int y, int x2, int y2, int color, drawType type, double maxLength, double minLength, int zOrd, char* parent, bool visible, int surface)
{


	//If the name is already used, change it instead.
	auto result = std::find_if(std::begin(DrawingObjects), std::end(DrawingObjects), [=](const auto & n) {
		return strcmp(n.name, objName) == 0 && n.type == type;
	});
	drawObject genericObj;

	//create line object
	stDrawLine* lineStruct = new stDrawLine;
	lineStruct->x = x;
	lineStruct->y = y;
	lineStruct->x2 = x2;
	lineStruct->y2 = y2;
	lineStruct->color = color;
	lineStruct->surface = surface;
	lineStruct->maxLength = maxLength;
	lineStruct->minLength = minLength;

	if (!DrawingObjects.empty() && result != DrawingObjects.end())
	{
		//Modify the current object if found. (name/type stays the same)
		result->zOrder = zOrd;
		result->parentName = parent;
		result->visible = visible;

		//Delete old value
		delete result->object;

		result->object = lineStruct;
		
	}
	else
	{

		//Add the object if not found.
		genericObj.name = objName;
		genericObj.parentName = parent;
		genericObj.type = type;
		genericObj.zOrder = zOrd;
		genericObj.visible = visible;

		genericObj.object = lineStruct;

		DrawingObjects.push_back(genericObj);

		//Sort for zOrder. (lowest number = first drawn/under all)
		DrawingObjects.sort([](drawObject const  a, drawObject const  b) {return a.zOrder < b.zOrder; });

	}

}


void draw::createCircle(char* objName, int x, int y, int rad, int color, int zOrd, char* parent, bool visible, int surface)
{


	//If the name is already used, change it instead.
	auto result = std::find_if(std::begin(DrawingObjects), std::end(DrawingObjects), [=](const auto & n) {
		return strcmp(n.name, objName) == 0 && n.type == drawType::Circle;
	});
	drawObject genericObj;

	//create the circle object
	stDrawCircle* circleStruct = new stDrawCircle;
	circleStruct->x = x;
	circleStruct->y = y;
	circleStruct->rad = rad;
	circleStruct->color = color;
	circleStruct->surface = surface;

	if (!DrawingObjects.empty() && result != DrawingObjects.end())
	{
		//Modify the current object if found. (name/type stays the same)
		result->zOrder = zOrd;
		result->parentName = parent;
		result->visible = visible;

		//Delete old value
		delete result->object;

		result->object = circleStruct;
		
	}
	else
	{

		//Add the object if not found.
		genericObj.name = objName;
		genericObj.parentName = parent;
		genericObj.zOrder = zOrd;
		genericObj.type = drawType::Circle;
		genericObj.visible = visible;

		genericObj.object = circleStruct;

		DrawingObjects.push_back(genericObj);

		//Sort for zOrder. (lowest number = first drawn/under all)
		DrawingObjects.sort([](drawObject const  a, drawObject const  b) {return a.zOrder < b.zOrder; });

	}

}


void draw::deleteObjectFromArray(char* name)
{
	auto result = std::find_if(std::begin(DrawingObjects), std::end(DrawingObjects), [name](const auto & n) {
		return n.name == name;
	});
	
	if (DrawingObjects.size() != 0 && result != DrawingObjects.end()) 
	{
		
		DrawingObjects.erase(result);
	}

}

double oldTime = 0;
void draw::updateStats()
{
	
	//Display the apple counter
	if(Stats::stats.displayAppleCounter)
		createText("lblApplesCollected", "Apples Collected: " + std::to_string(Stats::stats.getLevAppleCollected()) + "/" + std::to_string(Stats::stats.getLevApplesTotal()), 20, 200, 3);
	else
		createText("lblApplesCollected", "" , 20, 200, 3);

	if(Stats::stats.displayDeathCounter)
		createText("lblCompletedDeath", "Finish/Death/Esc: " + std::to_string(Stats::stats.currentLevelFinish) + "/" + std::to_string(Stats::stats.currentLevelDeaths) + "/" + std::to_string(Stats::stats.currentLevelEsc), 20, 220, 3);
	else
		createText("lblCompletedDeath", "", 20, 200, 3);

	//display level info:
	createText("LevelName", Level::lev.getLevelName(), 20, Addr.WindowHeight - 20, 1);


	//display dots at current location.
	if (oldTime < Level::lev.getTimeInLevel() - 30)
	{
		

		//oldTime = Level::lev.getTimeInLevel();

		//char* point = new char[20];
		//sprintf(point, "point%d", (int)oldTime);

		//createText(point, "O", *(double*)Kuski::kus.bikePosX, *(double*)Kuski::kus.bikePosY, 1);
	}

	


	statsChanged = false;
	
		
}

void draw::OptionsScreen(bool show)
{
	
	std::string menuStr;
	Menu::menuItem* selItem;


	//Nothing changed, exit
	if (!optionsUIChanged) return;
	
	//Debug::debug.addDebugInfoItem(Debug::debugInfo(std::string("test debug")));

	//Draw the back rectangle at the far right of the screen
	createRectFill("MainOptionWindow", Colors.LightGray, 20, *(int*)Addr.WindowHeight - 150, 500, *(int*)Addr.WindowHeight - (200 + ((Menu::menu.currentMenu->subMenu->size() - 1)*20)), 1, "", show);
	
	//Show the current menu
	createText("CurrentMenu", Menu::menu.currentMenu->Name, 80, *(int*)Addr.WindowHeight - 175 , 100, "MainOptionWindow", show);

	//Draw all the menu options
	for (int i = Menu::menu.currentMenu->subMenu->size() - 1; i >= 0; i--)
	{
		//Get the selected item
		selItem = Menu::menu.currentMenu->subMenu->at(i);

		//if it's the selected item, add *
		if (i == Menu::menu.selOpt)
			menuStr = std::string("*") + std::string(selItem->Name) + std::string("*");
		else
			menuStr = std::string(" ") + std::string(selItem->Name);

		createText(&selItem->Name[0u], menuStr, 40, *(int*)Addr.WindowHeight - 200 - (20 * i), 100, "MainOptionWindow", show);
		
		//draw the value if there is one.
		switch (selItem->value->Type) 
		{
		case Menu::menuValueType::b: //bool
			createText(&selItem->value->Name[0u], std::string("Off  On"), 240, *(int*)Addr.WindowHeight - 200 - (20 * i), 100, "MainOptionWindow", show);

		
			if(selItem->value->Value == false)
				createRectFill(&selItem->value->Name[0u], Colors.LightRed, 240, *(int*)Addr.WindowHeight - 200 - (20 * i), 258, *(int*)Addr.WindowHeight - 184 - (20 * i), 50, "MainOptionWindow", show);
			else
				createRectFill(&selItem->value->Name[0u], Colors.LightGreen, 265, *(int*)Addr.WindowHeight - 200 - (20 * i), 282, *(int*)Addr.WindowHeight - 184 - (20 * i), 50, "MainOptionWindow", show);

			break;

		case Menu::menuValueType::i: //integer

			createText(&selItem->value->Name[0u], std::to_string(selItem->value->Value), 240, *(int*)Addr.WindowHeight - 200 - (20 * i), 100, "MainOptionWindow", show);

			break;

		case Menu::menuValueType::a: //Array
			
			if(selItem->value->ArrayValue.size() != 0)
				createText(&selItem->value->Name[0u], selItem->value->ArrayValue[selItem->value->Value], 240, *(int*)Addr.WindowHeight - 200 - (20 * i), 100, "MainOptionWindow", show);

			break;
		}

		
	}
	
	
	optionsUIChanged = false;

	//If we modified the settings, update the stats.
	statsChanged = true;
}


//Draws everything in the current list on the playing screen.
void draw::drawAllObjectsOnScreen() 
{
	
	if (optionsUIChanged) 
	{
		DrawingObjects.clear();
		OptionsScreen(optionsUIactive);
	}
	if (statsChanged)
	{
		updateStats();
	}
	
	//Draw the object (already sorted by zorder)
	for (drawObject curObject : DrawingObjects)
	{
		//Skip if invisible
		if (!curObject.visible) continue;

		switch (curObject.type)
		{
		case drawType::Text:
		{
			
			stDrawText tmpTextStruct = *(stDrawText*)curObject.object;
			drawTextScreen(tmpTextStruct.font, tmpTextStruct.text, tmpTextStruct.x, tmpTextStruct.y, tmpTextStruct.charSpace, tmpTextStruct.currSurface);
			
			break;
		}
		case drawType::Rect:
		{
			stDrawRect tmpRectStruct = *(stDrawRect*)curObject.object;
			drawRectFillScreen(tmpRectStruct.color,  tmpRectStruct.x, tmpRectStruct.y, tmpRectStruct.x2, tmpRectStruct.y2, tmpRectStruct.surface);

			break;
		}
		case drawType::Circle:
		{
			
			stDrawCircle tmpCircleStruct = *(stDrawCircle*)curObject.object;
			drawCircle(tmpCircleStruct.x, tmpCircleStruct.y, tmpCircleStruct.rad, tmpCircleStruct.color, tmpCircleStruct.surface);

			break;
		}
		case drawType::Line:
		{
			stDrawLine tmpLineStruct = *(stDrawLine*)curObject.object;
			drawLine(tmpLineStruct.x, tmpLineStruct.y, tmpLineStruct.x2, tmpLineStruct.y2, tmpLineStruct.color, tmpLineStruct.surface);

			break;
		}
		case drawType::LineArrow:
		{
			stDrawLine tmpLineStruct = *(stDrawLine*)curObject.object;
			createLineArrow(tmpLineStruct.x, tmpLineStruct.y, tmpLineStruct.x2, tmpLineStruct.y2, tmpLineStruct.color, tmpLineStruct.maxLength, tmpLineStruct.minLength);

			break;
		}
		}
	}

	
}

/*
*	Draws text on the screen at a specific location
*	charSpace is the distance between each letter, -1000 = default
*/
void draw::drawTextScreen(int font, std::string text, int x, int y, int charSpace, int surface)
{
	
	if (surface != *(int*)playingSurf)
	{
		std::cout << "Error in textscreen draw function" << std::endl;
		return;
	}
	

	if (text == "") return;
	
	const char* cText = text.c_str();

	__asm {
		push charSpace
		push cText
		push y
		push x
		mov eax, surface
		push eax
		mov ecx, font
		call TextDrawFunction
	}

}


void draw::drawRectFillScreen(BYTE color,  int x, int y, int x2, int y2, int surface)
{
	
	if (surface != *(int*)playingSurf)
	{
		std::cout << "Error in drawRect function" << std::endl;
		return;
	}

	__asm {
		push color
		push y
		push x
		push y2
		push x2
		mov ecx, surface
		call RectFillDrawFunction
	}
	
}

void draw::drawPixel(int x, int y, int color, int surface)
{
	
	if (surface != *(int*)playingSurf)
	{
		std::cout << "Error in drawPixel function" << std::endl;
		return;
	}

	__asm {

		mov ecx, surface

		push color 
		push y
		push x
		call PixelDrawFunction
	}
		
}

//Bresenhamfs Line Drawing Algorithm
void draw::drawLine(int x1, int y1, int x2, int y2, int color, int surface)
{
	
	if (surface != *(int*)playingSurf)
	{
		std::cout << "Error in drawLine draw function" << std::endl;
		return;
	}
	

	const bool steep = (fabs(y2 - y1) > fabs(x2 - x1));
	if (steep)
	{
		std::swap(x1, y1);
		std::swap(x2, y2);
	}

	if (x1 > x2)
	{
		std::swap(x1, x2);
		std::swap(y1, y2);
	}

	const float dx = x2 - x1;
	const float dy = fabs(y2 - y1);

	float error = dx / 2.0f;
	const int ystep = (y1 < y2) ? 1 : -1;
	int y = (int)y1;

	const int maxX = (int)x2;

	for (int x = (int)x1; x < maxX; x++)
	{
		if (steep)
		{
			drawPixel(y, x, color, surface);
		}
		else
		{
			drawPixel(x, y, color, surface);
		}

		error -= dy;
		if (error < 0)
		{
			y += ystep;
			error += dx;
		}
	}
}

void draw::createLineArrow(int x1, int y1, int x2, int y2, int color, double maxLength, double minLength)
{

	double dist;
	double dx;
	double dy;
	
	dx = x2 - x1;
	dy = y2 - y1;
	int x3 = x1;
	int y3 = y1;
	//Get the distance of point A to point B
	dist = std::sqrt(dx * dx + dy * dy);

	if (maxLength == -1) maxLength = dist;
	if (minLength == -1) minLength = dist;

	//Calculate maximum distance of arrow.
	if (dist > 0)
	{
		dx /= dist;
		dy /= dist;
	}

	if (dist > maxLength)
	{
		dx *= maxLength;
		dy *= maxLength;
	}
	else if (dist < minLength)
	{
		dx *= minLength;
		dy *= minLength;
	}
	else
	{
		dx *= dist;
		dy *= dist;
	}
	x3 = (int)(x1 + dx);
	y3 = (int)(y1 + dy);
	
	double pi = 3.1415926535897931;
	const int r = 20;
	double join_angle = pi / 4.0;
	double stem_angle = std::atan2(y2 - y1, x2 - x1);

	//Draw the line from point A to B
	drawLine(x1, y1, x3, y3, color);
	
	//Draw arrow
	drawLine(x3, y3, x3 - int(r * std::cos(stem_angle + join_angle)), y3 - int(r * std::sin(stem_angle + join_angle)), color);
	drawLine(x3, y3, x3 - int(r * std::cos(stem_angle - join_angle)), y3 - int(r * std::sin(stem_angle - join_angle)), color);

}

void draw::drawCircle(int x, int y, int rad, int color, int surface)
{
	const double pi = 3.1415926535897931;
	const double inc = pi / 12;
	const double max = 2 * pi;
	
	for (double d = 0; d < max; d += inc) {

		drawLine(cos(d) * rad + x, sin(d) * rad + y, cos(d - inc) * rad + x, sin(d - inc) * rad + y, color, surface);
			
	}
	
}