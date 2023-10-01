#pragma once

inline DWORD localPlayer;
inline DWORD clientBase;
inline DWORD engineBase;
inline DWORD serverBrowserBase;

namespace Dumper
{
	namespace Pointers
	{
		inline DWORD playerBasePtr;
		inline DWORD writableViewAnglesBase;
		inline DWORD entityListPtr;
	}
	namespace Offsets
	{
		inline DWORD m_iHealth;
		inline DWORD m_iArmor;
		inline DWORD bDormant;
		inline DWORD viewAngles; // Vec3
		inline DWORD coordinates; // Vec3
		inline DWORD m_iShotsFired;
		inline DWORD m_bSpotted;
		inline DWORD m_iTeam;
		inline DWORD m_FlashDuration;
		inline DWORD m_iCash;
		inline DWORD m_iCrosshairId;
		inline DWORD m_iFOV;
		inline DWORD m_iDefaultFOV;
		inline DWORD m_iVelocity;
		inline DWORD dwForceShot;
		inline DWORD m_fFlags;
		inline DWORD bHasDefuser;
		inline DWORD dwForceJump;
		inline DWORD dwViewMatrix;
		inline DWORD writableViewAngles;
		inline DWORD m_dwBoneMatrix;
	}

	void Initialize();
	void WriteToFile();
	void Cleanup();
}