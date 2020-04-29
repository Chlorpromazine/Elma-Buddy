#include "Stats.h"


Stats Stats::stats;

void Stats::initPatch()
{
	//Called when wheel/head touches apple
	JumpPatch((BYTE*)0x0041FD62, (BYTE*)&touchApple, 0);

}

int Stats::getLevApplesTotal()
{
	return *(int*)ApplesTotal;
}

int Stats::getLevAppleCollected()
{
	return *(int*)ApplesCollected;
}

//Modify stats when you exit level (esc key)
void Stats::escapeKeyExitLev()
{
	
	currentLevelEsc++;
	
	static char escapedStr[50] = "";
	strcpy(escapedStr, "*$$^&|@You Escaped at ");
	strcat(escapedStr, &Level::lev.decimalTimeToStr(Level::lev.getTimeInLevel())[0]);
	Stats::stats.failedToFinishNewString = escapedStr;
	
}

//Modify stats when you exit level (killed)
void Stats::killedExitLev()
{
	currentLevelDeaths++;
	
	static char killedStr[50] = "";
	strcpy(killedStr, "*$$^&|@You Died at ");
	strcat(killedStr, &Level::lev.decimalTimeToStr(Level::lev.getTimeInLevel())[0]);
	Stats::stats.failedToFinishNewString = killedStr;
}

//Modify stats when you finish the level
void Stats::finishExitLev()
{
	currentLevelFinish++;
	
	//Get the finished time
	Kuski::kus.shadowLastBestTime = Level::lev.getTimeInLevel();

	//Show best apple time only if you've finished the level.
	if (Stats::stats.timeAppleTakenValue == 2) {
		Objects::obj.allObjectsNewProperties = Objects::obj.allObjectsNewPropertiesPrev;
		Objects::obj.allObjectsNewPropertiesPrev.clear();
	}
}