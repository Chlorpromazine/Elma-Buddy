#include "Drawing.h"

using namespace std;



Drawing Drawing::Draw;

int s_width = 800;
int s_height = 600;
#define CENTERX (GetSystemMetrics(SM_CXSCREEN)/2)-(s_width/2)
#define CENTERY (GetSystemMetrics(SM_CYSCREEN)/2)-(s_height/2)
LPDIRECT3D9 d3d;    // the pointer to our Direct3D interface
LPDIRECT3DDEVICE9 d3ddev;
HWND hWnd;
const MARGINS  margin = { 0,0,s_width,s_height };
const MARGINS *tes2t = &margin;
LPD3DXFONT pFont;
LPD3DXLINE d3dLine;
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


void Drawing::initD3D(HWND hWnd)
{
	d3d = Direct3DCreate9(D3D_SDK_VERSION);    // create the Direct3D interface

	D3DPRESENT_PARAMETERS d3dpp;    // create a struct to hold various device information

	ZeroMemory(&d3dpp, sizeof(d3dpp));    // clear out the struct for use
	d3dpp.Windowed = TRUE;    // program windowed, not fullscreen
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;    // discard old frames
	d3dpp.hDeviceWindow = hWnd;    // set the window to be used by Direct3D
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;     // set the back buffer format to 32-bit
	d3dpp.BackBufferWidth = s_width;    // set the width of the buffer
	d3dpp.BackBufferHeight = s_height;    // set the height of the buffer

	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	// create a device class using this information and the info from the d3dpp stuct
	d3d->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddev);
	
	D3DXCreateFont(d3ddev, 50, 0, FW_BOLD, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &pFont);
	D3DXCreateLine(d3ddev, &d3dLine);
}

void Drawing::DrawString(int x, int y, DWORD color, LPD3DXFONT g_pFont, const char *fmt)
{
	RECT FontPos = { x, y, x + 120, y + 16 };
	char buf[1024] = { '\0' };
	va_list va_alist;

	va_start(va_alist, fmt);
	vsprintf_s(buf, fmt, va_alist);
	va_end(va_alist);
	g_pFont->DrawText(NULL, buf, -1, &FontPos, DT_NOCLIP, color);
}


void Drawing::DrawCircle(int X, int Y, int radius, int numSides, DWORD Color)
{
	D3DXVECTOR2 Line[128];
	
	double Step = M_PI * 2.0 / numSides;
	int Count = 0;

	for (double a = 0; a < M_PI*2.0; a += Step)
	{
		float X1 = radius * cos(a) + X;
		float Y1 = radius * sin(a) + Y;
		float X2 = radius * cos(a + Step) + X;
		float Y2 = radius * sin(a + Step) + Y;
		Line[Count].x = X1;
		Line[Count].y = Y1;
		Line[Count + 1].x = X2;
		Line[Count + 1].y = Y2;
		Count += 2;
	}

	d3dLine->SetWidth(1.0);
	d3dLine->Draw(Line, Count, Color);
}

void Drawing::DrawLine(D3DXVECTOR2 p1, D3DXVECTOR2 p2, float Width, DWORD Color)
{
	D3DXVECTOR2 points[2];

	points[0] = p1;
	points[1] = p2;
	
	d3dLine->SetWidth(Width);
	d3dLine->Draw(points, 2, Color);
}

void Drawing::DrawRectangleEmpty(D3DXVECTOR2 Point, float Width, float Height, float Size, DWORD Color)
{

	D3DXVECTOR2 points[5];
	
	points[0] = Point;
	points[1] = D3DXVECTOR2(Point.x + Width,Point.y);
	points[2] = D3DXVECTOR2(Point.x + Width, Point.y + Height);
	points[3] = D3DXVECTOR2(Point.x, Point.y + Height);
	points[4] = Point;

	d3dLine->SetWidth(Size);
	d3dLine->Draw(points, 5, Color);
}

void Drawing::render()
{
	// clear the window alpha
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);

	if (currentScreen != 1)
	{
		d3ddev->Present(NULL, NULL, NULL, NULL);   // displays the created frame on the screen
		return;
	}

	d3ddev->BeginScene();    // begins the 3D scene
	
	
	DrawString(10, 50, D3DCOLOR_ARGB(255, 255, 255, 0), pFont, "Test rendering string");
	DrawCircle(100, 100, 50, 50, D3DCOLOR_ARGB(255, 255, 0, 0));
	DrawLine(D3DXVECTOR2(10, 10), D3DXVECTOR2(300, 300),1, D3DCOLOR_ARGB(255, 255, 0, 0));
	DrawLine(D3DXVECTOR2(200, 101), D3DXVECTOR2(40, 300), 1, D3DCOLOR_ARGB(255, 255, 255, 0));
	DrawRectangleEmpty(D3DXVECTOR2(123, 123), 50, 150, 2, D3DCOLOR_ARGB(255, 255, 255, 0));

	d3ddev->EndScene();    // ends the 3D scene

	d3ddev->Present(NULL, NULL, NULL, NULL);   // displays the created frame on the screen
}


char* Drawing::ReadINI(const char* szSection, const char* szKey, const char* szDefaultValue)
{
	char* szResult = new char[255];
	memset(szResult, 0x00, 255);
	GetPrivateProfileString(szSection, szKey,
		szDefaultValue, szResult, 255, ".\\conf.ini");
	return szResult;
}

BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam) {

		cout << "hwnd_Child = " << hwnd << endl;
		SetWindowPos(hwnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		return TRUE; // must return TRUE; If return is FALSE it stops the recursion

}

void Drawing::InitDraw(HINSTANCE hInstance)
{
	char* windowName = ReadINI("CONFIGURATION", "WIN_NAME", "Elasto Mania");


	RECT rc;

	HWND newhwnd = FindWindow(NULL, windowName);
	cout << GetForegroundWindow() << " : " << newhwnd << endl;
	
	if (newhwnd != NULL) {
		GetWindowRect(newhwnd, &rc);
		s_width = WindowWidth;
		s_height = WindowHeight;
	}
	else {
		cout << "Could not find Elma Window. Change the .ini file." << endl;
		return;
		
	}
	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)RGB(0, 0, 0);
	wc.lpszClassName = "WindowClass";

	RegisterClassEx(&wc);

	
	hWnd = CreateWindowEx(0,
		"WindowClass",
		"",
		 WS_POPUP | WS_CHILD,
		rc.left, rc.top,
		s_width, s_height,
		NULL,
		NULL,
		hInstance,
		NULL);


	//Hide from taskbar, make transparent, remove border.
	SetWindowLong(hWnd, GWL_EXSTYLE, (int)GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW);

	//SetWindowLong(hWnd, GWL_HWNDPARENT, (long)newhwnd);
	
	SetLayeredWindowAttributes(hWnd, RGB(0, 0, 0), 0, ULW_COLORKEY);
	SetLayeredWindowAttributes(hWnd, 0, 255, LWA_ALPHA);
	
	ShowWindow(hWnd, SW_SHOWNOACTIVATE);


	initD3D(hWnd);
	MSG msg;
	SetWindowPos(newhwnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	cout << newhwnd << endl;
	EnumChildWindows(newhwnd, EnumChildProc, 0);
	HWND hwndTest = (HWND)*(int*)0x0048DF6C;
	SetWindowPos(hwndTest, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	//SetWindowPos((HWND)0x006B0F2E, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	
	while (TRUE)
	{

		GetWindowRect(newhwnd, &rc);
		s_width = rc.right - rc.left;
		s_height = rc.bottom - rc.top;

		::SetWindowPos(hWnd, HWND_TOP, rc.left, rc.top, s_width, s_height, 0);

		
		if (!FindWindow(NULL, windowName))
			ExitProcess(0);
		
		
		//if (GetFocus())
			render();

		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		
		if (msg.message == WM_QUIT)
			exit(0);

	}

}


LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
		DwmExtendFrameIntoClientArea(hWnd, &margin);
		break;

	case WM_DESTROY:
	
		PostQuitMessage(0);
		return 0;
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}
