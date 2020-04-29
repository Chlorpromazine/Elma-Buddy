#include "System.h"

System System::sys;

char* System::getUserTime()
{
	// get time now
	std::time_t t = std::time(0);   
	std::tm* now = std::localtime(&t);
	char TimeStr[15];
	std::stringstream ss;

	switch (System::sys.chatTimestampValue)
	{
	case 0:
		strcpy(TimeStr, "");
		break;

	case 1:
		ss << "<" << now->tm_hour << ":" << now->tm_min << ">";
		ss >> TimeStr;
		break;

	case 2:
		ss << "<" << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec << ">";
		ss >> TimeStr;
		break;

	default:
		strcpy(TimeStr, "");
		break;
	}
	

	return TimeStr;
}
