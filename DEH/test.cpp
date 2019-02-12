//#pragma once
//
////Just some typedefs:
//#include <Windows.h>
//#include <iostream>
//
//#include <winioctl.h>
//#if (MSC_VER < 1400)
//#include <strmif.h>
//#endif
//
//using namespace std;
//
//LPDIRECTDRAWSURFACE7 g_pDDSBack = NULL;
//LPDIRECTDRAW7  g_pDD = NULL;
//LPDIRECTDRAWSURFACE7 g_pDDSFront = NULL;
//
//static HDC hdcTest;
//
//void testsurface()
//{
//	DDSURFACEDESC2 ddsd;
//	
//	HRESULT          hRet;
//	DDSCAPS2       ddscaps;
//	RECT    rcRect;
//
//	g_pDD = (LPDIRECTDRAW7)*(int*)0x4893D8;
//
//	ZeroMemory(&ddsd, sizeof(ddsd));
//	ddsd.dwSize = sizeof(ddsd);
//	ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
//	ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP |
//		DDSCAPS_COMPLEX;
//	ddsd.dwBackBufferCount = 1;
//
//	// Create the primary surface.
//	hRet = g_pDD->CreateSurface(&ddsd, &g_pDDSFront, NULL);
//	if (hRet != DD_OK)
//		cout << "Error 1" << endl;
//
//	ZeroMemory(&ddscaps, sizeof(ddscaps));
//	ddscaps.dwCaps = DDSCAPS_BACKBUFFER;
//	hRet = g_pDDSFront->GetAttachedSurface(&ddscaps, &g_pDDSBack);
//
//	if (hRet != DD_OK)
//		cout << "Error 2" << endl;
//
//	g_pDDSBack->Restore();
//
//	rcRect.left = 0;
//	rcRect.top = 0;
//	rcRect.right = 50 ;
//	rcRect.bottom = 50 ;
//
//	g_pDDSBack->GetDC(&hdcTest);
//
//
//	HFONT hFont;
//	hFont = CreateFont(12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ANTIALIASED_QUALITY, 0, L"Lucida Console");
//	SelectObject(hdcTest, hFont);
//	SetTextColor(hdcTest, RGB(255, 255, 0)); //yellow
//	SetBkMode(hdcTest, TRANSPARENT);
//
//}
//
//void drawOnElmaTest(wchar_t OutputText[], int x, int y, HDC hdcTmp) {
//
//	RECT rect;
//
//	rect.left = x;
//	rect.top = y;
//
//	DrawText(hdcTmp, OutputText, -1, &rect, DT_SINGLELINE | DT_NOCLIP);
//
//}
//
//void testdrawing() 
//{
//	drawOnElmaTest(L"Test", 5, 50 / 2, hdcTest);
//	g_pDDSBack->Flip(NULL, 0);
//}
//
