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
	
	//user pressed escape (leaves level)
	JumpPatch((BYTE*)0x0041F759, (BYTE*)&escapeKeyExitLev, 0);

	//When bike hits a killer
	JumpPatch((BYTE*)0x0041FD50, (BYTE*)&onHitKiller, 0);
	
	//When head hits floor
	JumpPatch((BYTE*)0x0041F9A8, (BYTE*)&onHeadHitFloor, 0);
	
	//When level is finished (hit flower with all apples)
	JumpPatch((BYTE*)0x0041FC82, (BYTE*)&onFlowerFinish, 0);

	//Change You Failed to Finish! string to something else to display more stats. (death time and what killed you)
	JumpPatch((BYTE*)0x0042AFCD, (BYTE*)&changeStringFailedToFinish, 0);
	
	//Get information on all polygons of current level.
	JumpPatch((BYTE*)0x004303EE, (BYTE*)&polyInject, 1);


	//Timestamp
	JumpPatch((BYTE*)jmpAddTimeStampStartMe, (BYTE*)&addTimeStampMe, 0);
	JumpPatch((BYTE*)jmpAddTimeStampStartOther, (BYTE*)&addTimeStampOther, 0);


	//hook packets
	JumpPatch((BYTE*)jmpPacketHook, (BYTE*)&testPacketHook, 1);

	Debug::debug.addDebugInfoItem(std::string("Loaded Hooks"));
}

//Placed right after Milagros' drawing function so we draw last (on top of everything else)
void __declspec(naked) drawInject()
{
		
	draw::dd.drawAllObjectsOnScreen();
	Objects::obj.displayObjectNumbers();
	Objects::obj.displayObjectArrow();
	
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
	if (Level::lev.LGRchanged) 
	{
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
	if (Level::lev.LGRchanged) 
	{
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


//Triggers after touching an apple with wheel or head.
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
	Objects::obj.allObjects.push_back((Objects::objStruct*)objAddr);
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
	Objects::obj.allObjects.clear();
	Objects::obj.allObjectsNewProperties.clear();
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

void __declspec(naked) escapeKeyExitLev()
{

	Stats::stats.escapeKeyExitLev();

	__asm {
		call callEscapeKeyExitLev
		jmp jmpEscapeKeyExitLev
	}
}

void __declspec(naked) onHitKiller()
{
	__asm {
		cmp ecx, 03
		je hitKiller
		jmp jneOnHitKiller
	hitKiller:
		pushad
	}

	//Killer has been hit
	Stats::stats.killedExitLev();
	
	__asm {
		popad
		jmp jmpOnHitKiller
	}
}

void __declspec(naked) onHeadHitFloor()
{
	__asm {
		mov ecx, [ebp + 0x24]
		mov edx, [ebp + 0x20]
		pushad
	}

	//floor has been hit by head
	Stats::stats.killedExitLev();

	__asm {
		popad
		jmp jmpOnHeadHitFloor
	}
}

void __declspec(naked) onFlowerFinish()
{
	__asm {
		call callHeadHitFlower
		pushad
	}

	//flower has been hit (and all apples taken)
	Stats::stats.finishExitLev();

	__asm {
		popad
		jmp jmpOnFlowerFinish
	}
}

//called when player died
void __declspec(naked) changeStringFailedToFinish()
{
	__asm {
		mov edi, Stats::stats.failedToFinishNewString
		jmp jmpFailedToFinish
	}
}

//called when starting a level, to get polygon information.
void __declspec(naked) polyInject() {
	
	__asm {
		//edi stores the start address of the objects of the current level.
		mov Polygons::Pol.polygonObjStart, edi
		jmp jmpPolygonInject
	}
	
}


void __declspec(naked) addTimeStampMe() {

	addTimeStamp();
	
	__asm {
		add esp, 0x10
		push 0x14
		jmp jmpAddTimeStampEndMe
	}
}

void __declspec(naked) addTimeStampOther() {

	addTimeStamp();
	
	__asm {
		add esp, 0x10
		push 0x14
		jmp jmpAddTimeStampEndOther
	}

}
void __declspec(naked) addTimeStamp() {

	
	//Copy the chat message and length
	__asm{
		
		mov ebx, esp
		add ebx, 0x14 //16 bytes offset for message and 4 bytes for function return address
		mov chatMessagelength,eax
		mov ecx, tmpTimeStampMessage
		mov tmpOldStrLocation, ebx
	nextLetter: //can't use strcpy since it screws up the stack.
		mov al, [ebx]
		mov [ecx],al
		inc ecx
		inc ebx
		dec eax
		cmp eax,0
		jg nextLetter

		mov al,0
		mov [ecx],al
	
	}
	

	__asm {
		pushad
	}

	
	strcpy(addedTimeStamp, System::sys.getUserTime());
	strcat(addedTimeStamp, tmpTimeStampMessage);
	strcpy(tmpOldStrLocation, addedTimeStamp);
	
	__asm {
		popad
		mov eax, chatMessagelength
		ret
	}
}


void __declspec(naked) testPacketHook() {

	__asm {
		mov edx, [ebp + 0x08]
		mov packetStartAddr, edx
		pushad
	}

	Debug::debug.readUnencryptedPacket(packetStartAddr);

	__asm{
		popad
		mov [edx + 0x29],eax
		jmp jmpPacketEnd
	}

	
}
