#pragma once

typedef HRESULT(APIENTRY* tEndScene)(LPDIRECT3DDEVICE9 pDevice);

bool GetD3D9Device(void** pTable, size_t size);

HWND GetProcessWindow();

static HWND window;
extern LONG windowHeight, windowWidth;

inline LPDIRECT3DDEVICE9 pDevice;