#include "Hooks.h"

void loadHooks()
{
	
	//Draw on screen
	JumpPatch((BYTE*)0x0049559E, (BYTE*)&drawInject, 0);

	//Force change LGR
	JumpPatch((BYTE*)0x00422DA9, (BYTE*)&changeLRGinject, 0);
	JumpPatch((BYTE*)0x0042586B, (BYTE*)&changeToNewLevel, 0);
	JumpPatch((BYTE*)0x00422B06, (BYTE*)&changeToNewLGR, 0);
	
	//Hook before elma/EOL keyboard inputs are processed.
	JumpPatch((BYTE*)0x0043A222, (BYTE*)&keyboardInject, 0);

	//JumpPatch((BYTE*)0x0042E713, (BYTE*)&UIdataChanged, 0);
	JumpPatch((BYTE*)0x00408DEF, (BYTE*)&getAllObjects, 0);

	JumpPatch((BYTE*)0x00425A7A, (BYTE*)&resetObjects, 0);

	//JumpPatch((BYTE*)0x0042E70E, (BYTE*)&collisionObject, 0);

	JumpPatch((BYTE*)0x0042D5AE, (BYTE*)&getTimeObject, 0);


	//on exit level
	JumpPatch((BYTE*)0x0049D153, (BYTE*)&exitToMenuInt, 0);
	JumpPatch((BYTE*)0x0049D173, (BYTE*)&exitToMenuExt, 0);
	


	Debug::debug.addDebugInfoItem(std::string("Loaded Hooks"));
}

//Placed right after Milagros' drawing function so we draw last (on top of everything else)
void __declspec(naked) drawInject()
{
		
	draw::dd.drawAllObjectsOnScreen();
	objects::obj.displayObjectNumbers();
	objects::obj.displayObjectArrow();
	
	Kuski::kus.saveCurrentRide();
	Kuski::kus.shadowKuski();

	__asm {

		//Call the function that we replaced and jump back to elma code once we're done.
		call callElmaAddr
		jmp jmpElmaDrawAddr
	}

}

//Placed after getting the LGR name (so we can change it now) and before loading the LGR.
void __declspec(naked) changeLRGinject()
{
	__asm {
		
	}

	Level::lev.changeLGR();

	__asm {
		

		push 0x0000A280
		jmp jmpChangeLGR
	}
}

//Compares to see if the level is the same being played or not.
void __declspec(naked) changeToNewLevel()
{
	
	__asm {
		call callNewLevel
		pushad
	}

	//Force LGR change
	if (Level::lev.LGRchanged) {
		__asm {
			popad
			mov eax, 1
		}
	}
	else
	{
		__asm {
			popad
		}
	}

	__asm{
		jmp jmpNewLevel
	}
}

//Compares the current LGR with the selected level LGR (only called when changeToNewLevel() is called)
void __declspec(naked) changeToNewLGR()
{
	
	__asm {
		call callNewLGR
		pushad
	}

	//Force LGR change
	if (Level::lev.LGRchanged) {
		Level::lev.LGRchanged = false;
		__asm {
			popad
			mov eax, 1
		}
	}
	else
	{
		__asm {
			popad
		}
	}
	
	__asm{
		jmp jmpNewLGR
	}

	

}

//Placed right before elma/EOL keyboard functions are called
void __declspec(naked) keyboardInject()
{
	//Disable all other inputs if our UI is opened.
	if (draw::dd.optionsUIactive)
	{
		__asm {
			jmp jmpKeyboardEnd
		}
		

	}
	else
	{
		__asm {
			call callKeyboardStart
			jmp jmpKeyboardEnd
		}
	}

}

//
////todo: use the hook when you touch any object then read what that object is, then do switch.
//void __declspec(naked) UIdataChanged()
//{
//	draw::dd.statsChanged = true;
//		__asm {
//			ret
//		}
//
//}
//

/*
*	Triggers after touching an apple with wheel or head.
*/
void __declspec(naked) touchApple() 
{
	//To update the apple counter
	draw::dd.statsChanged = true;
	
	__asm {
		mov[eax + 0x2C], 00000000
		jmp touchAppleEnd
	}
}

void test324(int objAddr)
{
	objects::obj.allObjects.push_back((objects::objStruct*)objAddr);
}
/*
*	Get the pointer address of the objects and store them into an array.
*	Only loads when entering a new level and these changes every level.
*/
void  __declspec(naked) getAllObjects()
{
	__asm {pusha}

	//cout << "Objects loaded" << endl;
	
	__asm {
		popa

		fld qword ptr[esi + 8]
		fchs
		mov objAddr, esi
		mov [esi + 0x10], eax
		fsub qword ptr[edi + 0x20]
		pusha
	}
	
	test324(objAddr);
	

	__asm {
		popa
		jmp jmpGetObjEnd
	}

}

/*
*	Called right before loading a new level.
*	Entering the same level multiple times won't trigger this.
*/
void __declspec(naked) resetObjects()
{
	__asm {pusha}

	//Clear all of the objects for the previous level.
	objects::obj.allObjects.clear();
	objects::obj.allObjectsNewProperties.clear();
	Kuski::kus.enterNewLevel();

	__asm {
		popa
		call callObjStart
		jmp jmpObjEnd
	}
}

//injected function which detects when you hit an object that's activated (flower/killer/apple/floor)
//start position are default deactivated, same with apples that you already touched
void __declspec(naked) collisionObject()
{
	__asm {
		push ebx
		mov ebx, 0x00487044
		mov[ebx], eax
		pop ebx
		//read which object id you touched.
		mov objID, edx

	}

	
	//add function(s) here
	
	//debugObjGrav(objID);
	//teleport(objID);
	//objects::obj.gravIntensity(objID);

	//go back to elma
	__asm {
		jmp objCollisionEnd
	}
}

void __declspec(naked) getTimeObject()
{
	
	__asm {
		mov esi, ecx
		mov timeAddrTmp, esi
		xor eax, eax
		push edi
		pushad
	}

	Level::lev.timeAddress = timeAddrTmp;

	__asm {

		popad
		jmp jmpTimeEnd
	}
}

void __declspec(naked) exitToMenuInt()
{

	__asm {pushad}

	Kuski::kus.onExitLevel();

	__asm {

		popad
		jmp jmpExitLevInt

	}
}

void __declspec(naked) exitToMenuExt()
{

	__asm {pushad}

	Kuski::kus.onExitLevel();

	__asm {

		popad
		jmp jmpExitLevExt

	}
}
