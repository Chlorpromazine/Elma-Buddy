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
	
	if (!DrawingObjects.empty() && result != DrawingObjects.end())
	{

		//Modify the current object if found. (name/type stays the same)
		result->zOrder = zOrd;
		result->parentName = parent;
		result->visible = visible;

		//Delete after replacing so elma thread doesn't read junk data.
		stDrawText* tmpPointer = (stDrawText*)result->object;
		
		stDrawText* textStruct = new stDrawText;
		textStruct->charSpace = charSpace;
		textStruct->currSurface = surface;
		textStruct->font = font;
		textStruct->text = text;
		textStruct->x = x;
		textStruct->y = y;

		result->object = textStruct;

		//todo: maybe mutex would work?
		//Sleep(1); //For some reason it deletes the struct before allocating the new one without this?....
		delete tmpPointer;
		
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

		stDrawText* textStruct = new stDrawText;
		textStruct->charSpace = charSpace;
		textStruct->currSurface = surface;
		textStruct->font = font;
		textStruct->text = text;
		textStruct->x = x;
		textStruct->y = y;

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

	if (!DrawingObjects.empty() && result != DrawingObjects.end())
	{
		//Modify the current object if found. (name/type stays the same)
		result->zOrder = zOrd;
		result->parentName = parent;
		result->visible = visible;

		//Delete after replacing so elma thread doesn't read junk data.
		void* tmpPointer = result->object;
		
		stDrawRect* rectStruct = new stDrawRect;
		rectStruct->color = color;
		rectStruct->x = x;
		rectStruct->y = y;
		rectStruct->x2 = x2;
		rectStruct->y2 = y2;
		rectStruct->surface = surface;


		result->object = rectStruct;
		Sleep(1);
		delete tmpPointer;
	}
	else 
	{
		
		//Add the object if not found.
		genericObj.name = objName;
		genericObj.parentName = parent;
		genericObj.type = drawType::Rect;
		genericObj.zOrder = zOrd;
		genericObj.visible = visible;

		stDrawRect* rectStruct = new stDrawRect;
		rectStruct->color = color;
		rectStruct->x = x;
		rectStruct->y = y;
		rectStruct->x2 = x2;
		rectStruct->y2 = y2;
		rectStruct->surface = surface;

		genericObj.object = rectStruct;

		DrawingObjects.push_back(genericObj);
		
		//Sort for zOrder. (lowest number = first drawn/under all)
		DrawingObjects.sort([](drawObject const  a, drawObject const  b) {return a.zOrder < b.zOrder; });
		
	}
	
}

//void draw::deleteObjectFromArray(char* name)
//{
//	cout << name << endl;
//	cout << "1: " << DrawingObjects.size() << endl;
//	auto result = std::find_if(std::begin(DrawingObjects), std::end(DrawingObjects), [name](const auto & n) {
//		return n.name == name;
//	});
//	
//	if (DrawingObjects.size() != 0 && result != DrawingObjects.end()) 
//	{
//		
//		DrawingObjects.erase(result);
//		cout << "2: " << DrawingObjects.size() << endl;
//	}
//
//}
//Calculate the height/width of text of a font.
SIZE draw::getSizeString(char* c, HFONT f = (HFONT)fontText)
{
	SIZE sz;
	HFONT font = CreateFont(12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ANTIALIASED_QUALITY, 0, "Lucida Console");//Segoe UI tahoma maybe
	HDC hdc = GetDC(NULL);
	SelectObject(hdc, font);    //attach font to hdc

	GetTextExtentPoint32(hdc, c, lstrlen(c), &sz);
	ReleaseDC(NULL, hdc);

	return sz;
}

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

	/*applesCollected
	createRectFill("testRect4", Colors.Red, 30, 30, 350, 350, 5);*/
	/*while (lockDraw);
	if (DrawingObjects.size() != 0) {
		lockDraw = true;
		DrawingObjectsBuffer = DrawingObjects;
		lockDraw = false;
		std::cout << "ok1" << std::endl;
	}*/
		
	/*int p = 16;
	int d = 16;
	for (int i = 0; i < p; i++) {
		
		for(int j = 0; j < d; j++){
			char* integer_string = new char[32];
			sprintf(integer_string, "%d", j + (i*d));

			char* integer_string2 = new char[32];
			sprintf(integer_string2, "%d", j + (i*d) + 1000);

		

			Sleep(10);
			createText(integer_string2, integer_string, i*30, j*30, 3);
			createRectFill(integer_string,  (j + (i*d)), i*30, j*30, (i+1)*30, (j+1)*30, 2);
		
		}
	}*/
	
	
	


	statsChanged = false;
	
		
}

void draw::OptionsScreen(bool show)
{
	//SIZE sz;
	std::string menuStr;
	Menu::menuItem* selItem;

	//Nothing changed, exit
	if (!optionsUIChanged) return;

	//Debug::debug.addDebugInfoItem(Debug::debugInfo(std::string("test debug")));

	//Draw the back rectangle at the far right of the screen
	createRectFill("MainOptionWindow", Colors.LightGray, 20, Addr.WindowHeight - 150, 500, Addr.WindowHeight - (200 + ((Menu::menu.currentMenu->subMenu->size() - 1)*20)), 1, "", show);
	
	//Show the current menu
	createText("CurrentMenu", Menu::menu.currentMenu->Name, 80, Addr.WindowHeight - 175 , 100, "MainOptionWindow", show);

	
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

		

		createText(&selItem->Name[0u], menuStr, 40, Addr.WindowHeight - 200 - (20 * i), 100, "MainOptionWindow", show);
		
		//draw the value if there is one.
		switch (selItem->value->Type) 
		{
		case Menu::menuValueType::b: //bool
			createText(&selItem->value->Name[0u], std::string("Off  On"), 240, Addr.WindowHeight - 200 - (20 * i), 100, "MainOptionWindow", show);

		
			if(selItem->value->Value == false)
				createRectFill(&selItem->value->Name[0u], Colors.LightRed, 240, Addr.WindowHeight - 200 - (20 * i), 255, Addr.WindowHeight - 184 - (20 * i), 50, "MainOptionWindow", show);
			else
				createRectFill(&selItem->value->Name[0u], Colors.LightGreen, 265, Addr.WindowHeight - 200 - (20 * i), 280, Addr.WindowHeight - 184 - (20 * i), 50, "MainOptionWindow", show);

			break;

		case Menu::menuValueType::i: //integer

			createText(&selItem->value->Name[0u], std::to_string(selItem->value->Value), 240, Addr.WindowHeight - 200 - (20 * i), 100, "MainOptionWindow", show);

			break;

		case Menu::menuValueType::a: //Array
			
			if(selItem->value->ArrayValue.size() != 0)
				createText(&selItem->value->Name[0u], selItem->value->ArrayValue[selItem->value->Value], 240, Addr.WindowHeight - 200 - (20 * i), 100, "MainOptionWindow", show);

			break;
		}

		
	}
	

	optionsUIChanged = false;

	//If we modified the settings, update the stats.
	statsChanged = true;
}


//Draws everything in the current list on the playing screen.
void draw::drawAllObjectsOnScreen() {

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
			
			stDrawText tmpTextStruct = *(stDrawText *)curObject.object;
			drawTextScreen(tmpTextStruct.font, tmpTextStruct.text, tmpTextStruct.x, tmpTextStruct.y, tmpTextStruct.charSpace, tmpTextStruct.currSurface);
			
			break;
		}
		case drawType::Rect:
		{
			stDrawRect tmpRectStruct = *(stDrawRect *)curObject.object;
			drawRectFillScreen(tmpRectStruct.color,  tmpRectStruct.x, tmpRectStruct.y, tmpRectStruct.x2, tmpRectStruct.y2, tmpRectStruct.surface);

			break;
		}
		case drawType::Circle:
		{


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
	if (surface != playingSurf) 
	{
		std::cout << "Error in textscreen draw" << std::endl;
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
	if (surface != playingSurf)
	{
		std::cout << "Error in drawRect draw" << std::endl;
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

//static wchar_t* DtoWC(double data)
//{
//	wchar_t *result = new wchar_t[100];
//	swprintf(result, 100, L"%f", data);
//	wprintf(L"[%ls]\n", result);
//	return result;
//}
//
//static wchar_t* ItoWC(int data)
//{
//	wchar_t *result = new wchar_t[100];
//	swprintf(result, 100, L"%d", data);
//	wprintf(L"[%ls]\n", result);
//	return result;
//}
