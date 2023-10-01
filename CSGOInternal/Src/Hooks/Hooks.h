#pragma once

bool DetourHook(void* src, void* dst, int len);
BYTE* TrampolineHook(BYTE* src, BYTE* dst, const DWORD len);

class Hook
{
public:
	bool bStatus = false;

	BYTE* src = nullptr;
	BYTE* dst = nullptr;
	BYTE* ptrToGatewayPtr = nullptr;
	int len = 0;

	BYTE originalBytes[10]{ 0 };

	Hook(BYTE* src, BYTE* dst, BYTE* ptrToGatewayPtr, uintptr_t len);
	Hook(const char* exportName, const char* moduleName, BYTE* dst, BYTE* ptrToGatewayPtr, uintptr_t len);

	void Enable();
	void Disable();
	void Toggle();
};

namespace Hooks
{
	void Initialize();
	void Unhook();

	void APIENTRY hkEndScene(LPDIRECT3DDEVICE9 o_pDevice);

	inline void* d3d9Device[119]; // vtable of dx device that we are going to steal
	inline BYTE EndSceneBytes[7]{ 0 };
	inline tEndScene oEndScene = nullptr;
}