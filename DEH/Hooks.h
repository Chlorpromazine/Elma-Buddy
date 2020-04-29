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
void __declspec() escapeKeyExitLev();
void __declspec() onHitKiller();
void __declspec() onHeadHitFloor();
void __declspec() onFlowerFinish();
void __declspec() changeStringFailedToFinish();
void __declspec() polyInject();
void __declspec() addTimeStamp();
void __declspec() addTimeStampMe();
void __declspec() addTimeStampOther();
void __declspec() testPacketHook();
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

//escape key exit level
static int jmpEscapeKeyExitLev = 0x0041F75E;
static int callEscapeKeyExitLev = 0x0043B110;

//When the bike hits a killer
static int jmpOnHitKiller = 0x0041FD55;
static int jneOnHitKiller = 0x0041FD59;

//When head hits floor
static int jmpOnHeadHitFloor = 0x0041F9AE;

//When player finishes level (hits flower with all apples collected)
static int callHeadHitFlower = 0x0043CB4C;
static int jmpOnFlowerFinish = 0x0041FC87;


//Display something other than You Failed to Finish!
static int jmpFailedToFinish = 0x0042AFD2;
static char* failedToFinishNewString = "*$$^&|@You Failed to Finish!";

//to get infomation on all polygons in level.
static int jmpPolygonInject = 0x004303FF;

//timestamp
static int bsdllAddr = 0x00491A10;
static int jmpAddTimeStampStartMe = *(int*)bsdllAddr + 0x000059B7;//0x00005A23;
static int jmpAddTimeStampEndMe = *(int*)bsdllAddr + 0x000059BC;//0x00005A28;
static int jmpAddTimeStampStartOther = *(int*)bsdllAddr + 0x00005A23;
static int jmpAddTimeStampEndOther = *(int*)bsdllAddr + 0x00005A28;
static int chatMessagelength;
static char addedTimeStamp[255];
static char* tmpTimeStampMessage = new char[255]();
static char* tmpOldStrLocation;

//test packet hook
static int bsqvDLLStart = 0x00491A10;
static int jmpPacketHook = *(int*)bsqvDLLStart + 0x00001bfe; //bs.bs$qv+1bfe
static int jmpPacketEnd = *(int*)bsqvDLLStart + 0x00001c04; //bs.bs$qv+1c04
static int packetStartAddr = 0;
