#include "../../Includes.h"

void APIENTRY Hooks::hkEndScene(LPDIRECT3DDEVICE9 o_pDevice)
{
	// If pDevice is null
	if (!pDevice)
		// Set pDevice' to o_pDevice
		pDevice = o_pDevice;

	// Local player base dynamic address
	localPlayer = *(DWORD*)(Dumper::Pointers::playerBasePtr);

	// If local player is valid/in game
	if (CSGO::EntityIsInGame(localPlayer))
	{
		// Run the aimbot
		g_Aimbot->Run();

		// Draw the ESP
		g_ESP->Draw();

		// Bunnyhop script
		g_Misc->BunnyHop();
	}

	// Return the gateway
	oEndScene(pDevice);
}
