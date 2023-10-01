#include "../../Includes.h"

void Misc::OverrideFOV(float value)
{
	// Get the default FOV for local player
	float defaultFOV = *(float*)(localPlayer + Dumper::Offsets::m_iDefaultFOV);

	// Simply set m_iDefaultFOV varibale to selected value
	defaultFOV = value;
}

void Misc::NoFlash()
{
	// Get the flash duration value for local player
	int flashDuration = *(int*)(localPlayer + Dumper::Offsets::m_FlashDuration);

	// If flash duration is more then 0(basically if you are flashed)
	if (flashDuration > 0)
		// Write 0 to flash duration variable
		flashDuration = 0;
}

void Misc::BunnyHop()
{
	// If entity is dead
	if (!CSGO::EntityIsAlive(localPlayer))
		// Dont do shit
		return;

	// If the key is pressed
	if (GetAsyncKeyState(VK_SPACE))
	{
		// If local player is on the ground
		if (CSGO::EntityIsOnTheGround(localPlayer))
			// Force a jump
			*(int*)(Dumper::Offsets::dwForceJump) = 6;
		// If in air
		else
			// Revert
			*(int*)(Dumper::Offsets::dwForceJump) = 4;
	}
	//
	// A correct way to set bitflags:
	// 
	// If local player is on the ground
	// Force a jump
	//*(int*)(Dumper::Offsets::dwForceJump) |= force;

	// If we in air
	// Reset the bit back
	//*(int*)(Dumper::Offsets::dwForceJump) &= ~force;
}
Misc* g_Misc;