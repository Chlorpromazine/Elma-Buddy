#include "CommonAddrs.h"


//Dereference pointer of integer and convert to string
std::string commonAddresses::IPtoS(int i)
{
	return std::to_string(*(int*)i);
}

