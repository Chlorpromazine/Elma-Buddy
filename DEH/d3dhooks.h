#pragma once
#include "stdafx.h"
#include <string>
#include <windows.h>
#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")
#include <d3dx9.h>
#pragma comment(lib, "d3dx9.lib")
#include <iostream>

using namespace std;

HRESULT __stdcall EndScene(LPDIRECT3DDEVICE9 pDevice);
typedef HRESULT(__stdcall* EndScene_t)(LPDIRECT3DDEVICE9);
typedef HRESULT(WINAPI* oEndScene)             (LPDIRECT3DDEVICE9 pDev);
typedef int (WINAPI *Present_t)(LPDIRECT3DDEVICE9 pDevice, const RECT *pSourceRect, const RECT *pDestRect, HWND hDestWindowOverride, const RGNDATA *pDirtyRegion);
static Present_t oPresent;
static EndScene_t pEndScene;

static LPD3DXFONT m_pFont;
static ID3DXLine* m_rectLine;
static DWORD* dwpVTableStart = NULL;

static const D3DCOLOR Pink = D3DCOLOR_ARGB(255, 255, 0, 255);
static const D3DCOLOR Red = D3DCOLOR_ARGB(255, 255, 0, 0);

DWORD WINAPI HookThread(LPVOID lpParameter);
template <typename T> T HookVTableFunction(DWORD* dwpTable, int index, DWORD dwNewFunc);
int WINAPI HookedPresent(LPDIRECT3DDEVICE9 pDevice, const RECT *pSourceRect, const RECT *pDestRect, HWND hDestWindowOverride, const RGNDATA *pDirtyRegion);
void DrawExample(LPDIRECT3DDEVICE9 pDevice);
void DrawFont(int X, int Y, D3DCOLOR Color, char *format, ...);
void DrawLine(ID3DXLine* pLine, float x1, float y1, float x2, float y2, D3DCOLOR color);
void DrawRect(LPDIRECT3DDEVICE9 Device_t, int X, int Y, int L, int H, D3DCOLOR color);
DWORD D3D9VTable();
DWORD dwFindPattern(DWORD dwAddress, DWORD dwLen, BYTE *bMask, char * szMask);
bool bDataCompare(const BYTE* pData, const BYTE* bMask, const char* szMask);