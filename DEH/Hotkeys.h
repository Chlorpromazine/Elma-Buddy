#pragma once
#include "DEH.h"


class Hotkeys
{

public:
	static Hotkeys HK;
	void SetHook();
	void ReleaseHook();
	std::vector<int> keyPressed;

	void processKeysInLev(WPARAM wParam);

private:
	

};

