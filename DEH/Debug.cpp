#include "Debug.h"

Debug Debug::debug;

void Debug::drawDebugInfo()
{

	for (int i = 0; i < debugInfoVec.size(); i++) 
	{
		draw::dd.createText(debugInfoVec[i].debugName, debugInfoVec[i].debugText, Addr.WindowWidth - 200, Addr.WindowHeight - 175 - (20 * i), 100, "", debugInfoEnabled);
	}

}

void Debug::addDebugInfoItem(std::string InfoStr) noexcept
{
	debugInfo Info(InfoStr);
	//Remove the first element if there's more than 10
	if (debugInfoVec.size() > 10) 
	{
		debugInfoVec.erase(debugInfoVec.begin());
	}

	debugInfoVec.push_back(Info);

	for (int i = 0; i < debugInfoVec.size(); i++)
	{
		char* name = new char[20];
		sprintf(name, "debugInfo%d", i);
		debugInfoVec[i].debugName = name; 
	}

	drawDebugInfo();
}
