#pragma once

#include "DEH.h"

void loadHooks();

void __declspec() drawInject();
void __declspec() changeLRGinject();
void __declspec() changeToNewLevel();
void __declspec() changeToNewLGR();
void __declspec() keyboardInject();
void __declspec() getAllObjects();
void __declspec() resetObjects();
void __declspec() touchApple();
void __declspec() getTimeObject();
void __declspec() exitToMenuInt();
void __declspec() exitToMenuExt();

//void __declspec() collisionObject();

//Draw hook
static int jmpElmaDrawAddr = 0x004955A3;
//Call the original elma function that we removed.
static int callElmaAddr = 0x0041BAF0;


//LGR hook
static int jmpChangeLGR = 0x00422DAE;
static int jmpNewLevel = 0x00425870;
static int callNewLevel = 0x00445E00;
static int callNewLGR = 0x00445E00;
static int jmpNewLGR = 0x00422B0B;

//Keyboard hook
static int callKeyboardStart = 0x00438560;
static int jmpKeyboardEnd = 0x0043A227;


//Object hook
static int jmpGetObjEnd = 0x00408DFA;
static int objAddr;
static int callObjStart = 0x0040AEF0;
static int jmpObjEnd = 0x00425A7F;

//Touch apple
static int touchAppleEnd = 0x0041FD69;

//Object collision
static int objCollisionEnd = 0x0042E713;
static int objID;

//time object
static int jmpTimeEnd = 0x0042D5B3;
static int timeAddrTmp;


//exit level

static int jmpExitLevInt = 0x0042C29B;
static int jmpExitLevExt = 0x00428D9E;

//hook keyboard
static int jmpKeyboardHookEnd = 0x0043A2B1;
static int keyPressASM;