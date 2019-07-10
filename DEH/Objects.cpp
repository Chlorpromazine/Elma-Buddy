#include "objects.h"

objects objects::obj;

objects::objects() {

	//object currently selected
	curObject = 0;

	//current lev check
	for (int i = 0; i < 8; i++)
		oldLev[i] = 0;

	reload = 1;
	
}


//unused
/*
*	Changes the selected object to the next value.
*	1 = flower, 2 = apple, 3 = killer, 4 = start (only 1 start location or it crashes)
*	Values other than those crashes the game.
*/
void objects::changeObject(int curObj)
{
	if (allObjects.size() > curObj)
	{
		//read current object type;
		BYTE* Dest = (BYTE*)(allObjects[curObject]->type);
		BYTE type = *(BYTE*)Dest;

		type++;
		if (type > 4) type = 1;

		BYTE Buff[1] = { type };
		MemPatch(Dest, Buff, 1);

	}
}

/*
*	Changes the activation flag of selected object.
*	Apples will become visible or invisible when toggled.
*	Start object does nothing.
*	Killers and flowers will always show but the collision can be removed if toggled off.
*/
void objects::objectActive(int curObj, bool active)
{
	if (allObjects.size() > curObj)
	{
		//read current object type;
		BYTE* Dest = (BYTE*)(allObjects[curObj]->active);
		BYTE type = *(BYTE*)Dest;

		//1 active, 0 non active
		type = active;

		BYTE Buff[1] = { type };
		MemPatch(Dest, Buff, 1);

	}
}




/*
*	Selects the next object in the array to be modified.
*/
void objects::nextObject()
{
	if (allObjects.size())
	{
		//The last object is always null, I don't know what it is so I'm just removing it.
		if (curObject < allObjects.size() - 1)
			curObject++;
		else
			curObject = 0;

		//debug
		cout << "Current Object: " << curObject;
		cout << "\tType: ";
		switch (*(BYTE*)(allObjects[curObject]->type))
		{
		case 1:
			cout << "Flower";
			break;
		case 2:
			cout << "Apple";
			break;
		case 3:
			cout << "Killer";
			break;
		case 4:
			cout << "Start";
			break;
		default:
			cout << "Unknown";
			break;
		}
		cout << endl;
	}
}

/*
*	Moves the selected object to another position using the arrow keys.
*/
void objects::moveObject(int dir)
{
	if (allObjects.size())
	{
		pos position = getLocation();

		switch (dir) {
		case 0: //Up
			position.y++;
			break;
		case 1: //Down
			position.y--;
			break;
		case 2: //Left
			position.x--;
			break;
		case 3: //Right
			position.x++;
			break;
		}

		newLocation(position);
	}
}

/*
*	Gets the X/Y location of the selected object.
*/
objects::pos objects::getLocation()
{
	pos position;

	//take the current position from the memory
	position.x = allObjects[curObject]->x;
	position.y = allObjects[curObject]->y;

	return position;
}

/*
*	Gets the X/Y location of a choosen object.
*/
objects::pos objects::getLocation(int obj)
{
	pos position;

	//take the current position from the memory
	position.x = allObjects[obj]->x;
	position.y = allObjects[obj]->y;

	return position;
}
/*
*	Sets the X/Y location of the selected object.
*/
void objects::newLocation(pos newPos)
{
	//copy object location x
	allObjects[curObject]->x = newPos.x;
	
	//copy object location y
	allObjects[curObject]->y = newPos.y;
	
}

/*
*	Displays a number on all of the object. The number is when it first got placed in the editor.
*/
void objects::displayObjectNumbers()
{

	for (int i = 0; i < allObjects.size(); i++)
	{
		char* objTimeName = new char[20];
		char* gravName = new char[20];

		sprintf(objTimeName, "objectTime%d", i);
		sprintf(gravName, "objectGrav%d", i);

		//todo: change 48 with elma varible for screen size
		//position of object minus bike position, add window width/height to place in center.
		int posX = (int)std::round(((double)allObjects[i]->x - *(double*)Kuski::kus.bikePosX) * 48) + Addr.WindowWidth / 2;
		int posY = (int)std::round(((double)allObjects[i]->y - *(double*)Kuski::kus.bikePosY) * 48) + Addr.WindowHeight / 2;
		
		//Get the new time of the apple taken
		if (Stats::stats.displayTimeAppleTaken && allObjects[i]->active == 0 && allObjects[i]->type == objType::Apple)
		{
			
			double tmpBestTime = Level::lev.getTimeInLevel();
			if (tmpBestTime < allObjectsNewProperties[i].bestTime || allObjectsNewProperties[i].bestTime == 0.0f)
			{
				allObjectsNewProperties[i].bestTime = tmpBestTime;
				allObjectsNewProperties[i].bestTimeStr = Level::lev.decimalTimeToStr(allObjectsNewProperties[i].bestTime);
			}
		}

		//display the time of the apple taken if present.
		if (Stats::stats.displayTimeAppleTaken && allObjectsNewProperties[i].bestTime != 0.0f )
		{
			draw::dd.createText(objTimeName, allObjectsNewProperties[i].bestTimeStr, posX - 20, posY, 999, "");
		}

		
		//display the gravity of each apple.
		if (Stats::stats.displayAppleGravity && allObjects[i]->active == 1)
		{
			switch (allObjects[i]->gravity)
			{
			case 0:
				break;
			case 1:
				draw::dd.createText(gravName, std::string("^"), posX, posY - 15, 999, "");
				break;
			case 2:
				draw::dd.createText(gravName, std::string("v"), posX, posY - 15, 999, "");
				break;
			case 3:
				draw::dd.createText(gravName, std::string("<"), posX, posY - 15, 999, "");
				break;
			case 4:
				draw::dd.createText(gravName, std::string(">"), posX, posY - 15, 999, "");
				break;
			default:
				break;
			}
		}
		else
		{
			draw::dd.createText(gravName, std::string(""), posX, posY - 15, 999, "");
		}
		
	}
}

void objects::displayObjectArrow() 
{
	//display arrow to closest apple/flower
	int closestApple = objects::obj.getClosestObject(objects::objType::Apple);

	if (closestApple == -1) draw::dd.deleteObjectFromArray("closestApple");
	if (closestApple != -1)
		draw::dd.createLine("closestApple", Addr.WindowWidth / 2, Addr.WindowHeight / 2,
		(objects::obj.allObjects[closestApple]->x - *(double*)Kuski::kus.bikePosX) * 48 + Addr.WindowWidth / 2,
			(objects::obj.allObjects[closestApple]->y - *(double*)Kuski::kus.bikePosY) * 48 + Addr.WindowHeight / 2,
			Colors.Red, draw::drawType::LineArrow, 200);

	int closestFlower = objects::obj.getClosestObject(objects::objType::Flower);

	if (closestFlower == -1) draw::dd.deleteObjectFromArray("closestFlower");
	if (closestFlower != -1)
		draw::dd.createLine("closestFlower", Addr.WindowWidth / 2, Addr.WindowHeight / 2,
		(objects::obj.allObjects[closestFlower]->x - *(double*)Kuski::kus.bikePosX) * 48 + Addr.WindowWidth / 2,
			(objects::obj.allObjects[closestFlower]->y - *(double*)Kuski::kus.bikePosY) * 48 + Addr.WindowHeight / 2,
			Colors.White, draw::drawType::LineArrow, 200);
}
int objects::getClosestObject(objType type)
{
	double closestDist = 9999999;
	double currentDist = 0;
	int closestApple = -1;
	

	for (int i = 0; i < allObjects.size(); i++) 
	{
		//Must be same type and active
		if (allObjects[i]->type != type) continue;
		if (allObjects[i]->active == false) continue;

		//pythagore dist
		currentDist = sqrt((allObjects[i]->x - *(double*)Kuski::kus.bikePosX) * (allObjects[i]->x - *(double*)Kuski::kus.bikePosX)
						 + (allObjects[i]->y - *(double*)Kuski::kus.bikePosY) * (allObjects[i]->y - *(double*)Kuski::kus.bikePosY));
		
		if (closestDist > currentDist)
		{
			closestDist = currentDist;
			closestApple = i;
		}

	}
	
	return closestApple;
}

