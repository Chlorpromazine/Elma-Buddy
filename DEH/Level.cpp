#include "Level.h"

Level Level::lev;

void Level::initLevel()
{
	Level::lev.getLGRlist();
}

void Level::changeLGR()
{
	strcpy((char*)LGRNameAddr, LGRlist[LGRselected].c_str());
}

//The only way to get the lgr is to just check the LGR folder where the .exe is located
void Level::getLGRlist()
{
	char selfdir[MAX_PATH] = { 0 };
	std::string folderPath;
	std::string LGRpath;

	std::string LGRname;
	std::string LGRext;

	//Get the full path of the executable
	GetModuleFileNameA(NULL, selfdir, MAX_PATH);

	//Remove eol.exe
	folderPath = std::string(selfdir).substr(0, std::string(selfdir).find_last_of("\\/"));

	//Go to the LGR folder
	LGRpath = folderPath + "\\" + "LGR";


	for (const auto & entry : std::filesystem::directory_iterator(LGRpath))
	{	
		//remove path 
		LGRname = std::string(entry.path().string()).substr(std::string(entry.path().string()).find_last_of("\\/") + 1, entry.path().string().length());


		//get extention of file
		if (LGRname.length() > 4) 
		{
			LGRext = std::string(LGRname).substr(LGRname.length() - 4, LGRname.length());

			//tolower
			std::transform(LGRext.begin(), LGRext.end(), LGRext.begin(), ::tolower);

			//remove .lgr
			if (LGRext == ".lgr") 
			{
				LGRname = std::string(LGRname).substr(0, LGRname.length() - 4);

				//Add to vector
				LGRlist.push_back(LGRname);
			}

		}
		//Debug::debug.addDebugInfoItem(Debug::debugInfo(std::string(LGRname)));
	}

	LGRselected = findIndexLGR("default");
}

int Level::findIndexLGR(std::string LGRname)
{
	std::transform(LGRname.begin(), LGRname.end(), LGRname.begin(), ::tolower);

	int pos = std::distance(LGRlist.begin(), std::find(LGRlist.begin(), LGRlist.end(), LGRname));

	if (pos < 0) return 0;

	return pos;
}

double Level::getTimeInLevel()
{
	return *(int*)(timeAddress+0x38) / *(double*)framesPerSecond;
}

std::string Level::decimalTimeToStr(double timeDec)
{
	char tmpTimeDesplayStr[15];
	int minStr;
	int secStr;
	int msStr;
	double tmp;

	minStr = (int)timeDec / 60;
	secStr = (int)timeDec % 60;
	msStr = (int)roundf(std::modf(timeDec, &tmp) * 100);

	sprintf(tmpTimeDesplayStr, "%02i:%02i:%02i", minStr, secStr, msStr);

	return tmpTimeDesplayStr;
}

//Gets the current level name, works in replay.
std::string Level::getLevelName()
{
	//Can't convert to string directly?
	return (std::string)(char*)LevName;
}
