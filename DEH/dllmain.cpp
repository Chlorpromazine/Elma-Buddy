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
MSG msg = {0};



//__declspec(dllimport)  DWORD WINAPI mainLoop(LPVOID lpParam);

DWORD WINAPI mainLoop(LPVOID lpParam)
{
	run = true;
	
	
	try{
	
		//Add hook for keybord presses
		Hotkeys::HK.SetHook();

		//Initialize the level
		Level::lev.initLevel();

		//Initialize the menu.
		Menu::menu.initMenu();

		//Initialize the stats
		Stats::stats.initPatch();

		loadHooks();
		
		while (run) 
		{
			
			switch (*(int*)Addr.CurrentScreen)
			{

				
				case 0: //menu
					draw::dd.optionsUIactive = false;
					draw::dd.optionsUIChanged = true;
					//draw::dd.OptionsScreen(draw::dd.optionsUIactive);
					break;
				case 1: //main game
				case 3: //in editor level
					
					
					//Hotkeys::HK.processKeysInLev();
					
				
					//draw::dd.OptionsScreen(draw::dd.optionsUIactive);

					
					//draw::dd.updateStats();


					break;
				case 2: //replay
					draw::dd.optionsUIactive = false;
					draw::dd.optionsUIChanged = true;
					//draw::dd.OptionsScreen(draw::dd.optionsUIactive);
					break;
			}

			Sleep(1);

		}
	}
	catch (exception ex) 
	{
		cout << ex.what();
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
		CreateThread(NULL, 0, mainLoop, 0, 0, NULL);

		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		//run = false;
		break;
	}
	return TRUE;
}

