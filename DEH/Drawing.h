#pragma once
#include <windows.h>
#include <iostream>
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3d9.lib")
#include <d3dx9.h>
#include <d3d9.h>
#include <Dwmapi.h> 
#include <TlHelp32.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "CommonAddrs.h"


class Drawing
{

public:
	static Drawing Draw;
	void initD3D(HWND hWnd);
	char* ReadINI(const char* szSection, const char* szKey, const char* szDefaultValue);
	void DrawString(int x, int y, DWORD color, LPD3DXFONT g_pFont, const char *fmt);
	void DrawCircle(int X, int Y, int radius, int numSides, DWORD Color);
	void DrawLine(D3DXVECTOR2 p1, D3DXVECTOR2 p2, float Width, DWORD Color);
	void DrawRectangleEmpty(D3DXVECTOR2 Point, float Width, float Height, float Size, DWORD Color);
	void InitDraw(HINSTANCE hInstance);
	void render();

	
private:

};

