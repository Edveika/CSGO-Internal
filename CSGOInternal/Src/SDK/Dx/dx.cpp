#include "../../Includes.h"

LONG windowHeight, windowWidth;

BOOL CALLBACK enumWind(HWND handle, LPARAM lp)
{
	DWORD procId;
	GetWindowThreadProcessId(handle, &procId);

	if (GetCurrentProcessId() != procId)
		return TRUE;

	window = handle;

	return FALSE;
}

HWND GetProcessWindow()
{
	window = NULL;

	EnumWindows(enumWind, NULL);

	RECT size;
	while (GetWindowRect(window, &size) == 0)
		Sleep(10);

	GetWindowRect(window, &size);
	windowWidth = size.right - size.left;
	windowHeight = size.bottom - size.top;

	//windowHeight -= 29;
	//windowWidth -= 5;

	return window;
}

bool GetD3D9Device(void** pTable, size_t size)
{
	if (!pTable)
		return false;

	IDirect3D9* pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (!pD3D)
		return false;

	IDirect3DDevice9* pDummyDevice = nullptr;

	D3DPRESENT_PARAMETERS d3dpp = {};
	d3dpp.Windowed = false;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = GetProcessWindow();

	HRESULT dummyDeivceCreated = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pDummyDevice);

	if (dummyDeivceCreated != S_OK)
	{
		d3dpp.Windowed = !d3dpp.Windowed;
		HRESULT dummyDeivceCreated = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pDummyDevice);
		
		if (dummyDeivceCreated != S_OK)
		{
			pD3D->Release();
			return false;
		}
	}

	memcpy(pTable, *(void***)(pDummyDevice), size);
	pDummyDevice->Release();
	pD3D->Release();
	return true;
}