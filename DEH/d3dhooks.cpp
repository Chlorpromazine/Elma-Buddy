//#include <Windows.h>
//#include <d3d9.h>
//
//DWORD * VTable;
//DWORD dwEndscene_hook, dwEndscene_ret;
//IDirect3DDevice9* m_pD3Ddev;
//
//BOOL bCompare(const BYTE* pData, const BYTE* bMask, const char* szMask)
//{
//	for (; *szMask; ++szMask, ++pData, ++bMask)
//		if (*szMask == 'x' && *pData != *bMask)   return 0;
//	return (*szMask) == NULL;
//}
//
//DWORD FindPattern(DWORD dwdwAdd, DWORD dwLen, BYTE *bMask, char * szMask)
//{
//	for (DWORD i = 0; i < dwLen; i++)
//		if (bCompare((BYTE*)(dwdwAdd + i), bMask, szMask))  return (DWORD)(dwdwAdd + i);
//	return 0;
//}
//
//void DrawFillRect(IDirect3DDevice9* dev, int x, int y, int w, int h, unsigned char r, unsigned char g, unsigned char b)
//
//{
//
//	D3DCOLOR rectColor = D3DCOLOR_XRGB(r, g, b);   //No point in using alpha because clear & alpha dont work!
//
//	D3DRECT BarRect = { x, y, x + w, y + h };
//
//
//
//	dev->Clear(1, &BarRect, D3DCLEAR_TARGET | D3DCLEAR_TARGET, rectColor, 0, 0);
//
//}
//
//void Dx9Hook(LPCSTR D3D9)
//{
//	DWORD hD3D = NULL;
//	while (!hD3D) hD3D = (DWORD)GetModuleHandle(D3D9);
//	DWORD PPPDevice = FindPattern(hD3D, 0x128000, (PBYTE)"\xC7\x06\x00\x00\x00\x00\x89\x86\x00\x00\x00\x00\x89\x86", "xx????xx????xx");
//	memcpy(&VTable, (void *)(PPPDevice + 2), 4);
//
//	dwEndscene_hook = VTable[42] + 0x2A; //mid function
//	dwEndscene_ret = dwEndscene_hook + 0x6; //return address
//}
//
//INT Thread_XD3DXINIT()
//{
//	Dx9Hook("d3d9.dll");
//
//	while( 1 )
//	{
//	Sleep( 1000 );
//
//	if(memcmp((void *)Endscene_opcodes, (void *)dwEndscene_hook, 6) == 0 )
//	Detour(dwEndscene_hook, MyEndscene);
//
//	}
//
//	return NULL;
//}
//
//__declspec(naked) void MyEndscene()
//{
//	__asm
//	{
//		mov dword ptr ss : [ebp - 10], esp;
//		mov esi, dword ptr ss : [ebp + 0x8]; //replace patched code
//		mov m_pD3Ddev, esi; //Get the device
//	}
//
//	DrawFillRect(m_pD3Ddev, 500, 100, 100, 100, 90, 100, 255);
//
//	__asm
//	{
//		jmp dwEndscene_ret; //jump back to normal endscene
//	}
//
//}
//
//BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
//{
//	if (fdwReason == 1) //1 = On inject to process//
//	{
//		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Thread_XD3DXINIT, NULL, NULL, NULL);
//
//		//Thread_XD3DXINIT is now starting to execute code in a new thread//
//
//		return TRUE;
//	}
//
//	return FALSE;
//}