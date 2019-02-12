#pragma once

#include "DEH.h"

void loadHooks();

void __declspec() drawInject();
void __declspec() changeLRGinject();
void __declspec() keyboardInject();
void __declspec() getAllObjects();
void __declspec() resetObjects();
void __declspec() touchApple();
//void __declspec() collisionObject();

//Draw hook
static int jmpElmaDrawAddr = 0x004955A3;
//Call the original elma function that we removed.
static int callElmaAddr = 0x0041BAF0;


//LGR hook
static int jmpChangeLGR = 0x00422DAE;


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