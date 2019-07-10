#pragma once
#include "hotkeys.h"
#include "Draw.h"

Hotkeys Hotkeys::HK;

HHOOK _hook;

//Keyboard callback function
LRESULT __stdcall HookCallback(int nCode, WPARAM wParam, LPARAM lParam)
{
	
	if (nCode > 0)
	{

		if ((lParam & 0x80000000) == 0)//Key down
		{
			
			//if ((lParam & 0x40000000) == 0) //not repeated
			{
				Hotkeys::HK.processKeysInLev(wParam);
			}
		}

	}

	
	return CallNextHookEx(_hook, nCode, wParam, lParam);
}


//Hook the keyboard
void Hotkeys::SetHook()
{
	//Hopefully this is done right
	//We get the hInstance from dinput.dll then get the main threadID from the main HWND saved from a variable that Milagro made.
	//We then add a keyboard hook to that.
	HMODULE dInputMod = LoadLibrary("dinput.dll");
	
	if (!(_hook = SetWindowsHookEx(WH_KEYBOARD, HookCallback, dInputMod, (DWORD)GetWindowThreadProcessId(Addr.mainHWND, NULL))))
	{
		std::cout << "Failed to install hook!" << std::endl;
	}
}

void Hotkeys::ReleaseHook()
{
	UnhookWindowsHookEx(_hook);
}

void Hotkeys::processKeysInLev(WPARAM wParam)
{
	
	switch (*(int*)Addr.CurrentScreen) {

	case 0: //menu
		
		break;
	case 1: //main game
	case 3: //in editor level

		//Show/hide options UI
		switch (wParam)
		{
		case VK_TAB:
			//Exit menu and save
			draw::dd.optionsUIactive = !draw::dd.optionsUIactive;
			draw::dd.optionsUIChanged = true;
			draw::dd.OptionsScreen(draw::dd.optionsUIactive);

			if (draw::dd.optionsUIactive == false)
			{
				Menu::menu.saveSettings();
			}

			break;
		case VK_UP:
			if (draw::dd.optionsUIactive)
				Menu::menu.incSelOpt();
			
			break;
		case VK_DOWN:
			if (draw::dd.optionsUIactive)
				Menu::menu.decSelOpt();
			
			break;
		case VK_LEFT:
			if (draw::dd.optionsUIactive)
				Menu::menu.changeValue(-1);

			break;
		case VK_RIGHT:
			if (draw::dd.optionsUIactive)
				Menu::menu.changeValue(1);

			break;
		case VK_NEXT:
			if (draw::dd.optionsUIactive)
				Menu::menu.changeValue(-100);

			break;
		case VK_PRIOR:
			if (draw::dd.optionsUIactive)
				Menu::menu.changeValue(100);

			break;
		case VK_RETURN:
			if (draw::dd.optionsUIactive)
				Menu::menu.enterSubMenu();
			
			break;
		case VK_BACK:
			if (draw::dd.optionsUIactive)
				Menu::menu.exitSubMenu();

			break;

		case  0x53: //s
			if (GetKeyState(VK_MENU) & 0x8000) //alt
			{
				Kuski::kus.enableKuskiShadow = !Kuski::kus.enableKuskiShadow;
			}
			break;

		//case VK_ESCAPE:
		//	//Exit menu without saving
		//	draw::dd.optionsUIactive = false;
		//	draw::dd.optionsUIChanged = true;
		//	draw::dd.OptionsScreen(false);

		//				
		//	break;
		}

		break;
	case 2: //replay

		break;
		
	}

}