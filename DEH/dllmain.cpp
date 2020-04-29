// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "draw.h"
//#include "drawing.h"
#include "CommonAddrs.h"

#include "guicon.h"

#include "mem.h"
//#include "Hooks.h"
#include "Hotkeys.h"

#include "hooks.h"

#include "Objects.h"
//#include "Level.h"

bool run;


extern "C" __declspec(dllexport) DWORD mainLoop(LPVOID lpParam)
{
	run = true;
	

	//Add hook for keybord presses
	Hotkeys::HK.SetHook();

	//Initialize the level
	Level::lev.initLevel();

	//Initialize the menu.
	Menu::menu.initMenu();

	//Initialize the stats
	Stats::stats.initPatch();

	//Load all other hooks
	loadHooks();

	
	while (run) 
	{
		//bs.bs$qv+d9f0
		//bs.bs$qv+1F18C
		//bs.bs$qv+27FCA
		switch (*(int*)Addr.CurrentScreen)
		{

			case 0: //menu
				draw::dd.optionsUIactive = false;
				draw::dd.optionsUIChanged = true;
			
				break;
			case 1: //main game
			case 3: //in editor level

			
				break;
			case 2: //replay
				draw::dd.optionsUIactive = false;
				draw::dd.optionsUIChanged = true;
				//draw::dd.OptionsScreen(draw::dd.optionsUIactive);
				break;
		}

		Sleep(1);

	}

	return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{

	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		RedirectIOToConsole(); //debug

		//Create the main loop thread
		CreateThread(NULL, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(mainLoop), 0, 0, NULL);

		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		//run = false;
		break;
	}
	return TRUE;
}

