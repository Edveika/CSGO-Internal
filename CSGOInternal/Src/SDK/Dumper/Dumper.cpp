#include "../../Includes.h"

void Dumper::Initialize()
{
	//
	// Pointer patterns
	//
	DWORD playerBasePattern = Utils::FindPattern("client.dll", "\x8B\x00\x00\x00\x00\x00\x85\xC9\x74\x0F\x8B\x01\x8B\x00\x00\x00\x00\x00\xFF\xD0", "x?????xxxxxxx?????xx") + 2;
	Dumper::Pointers::playerBasePtr = *(DWORD*)playerBasePattern;
	std::cout << std::hex << " Local player ptr found at: 0x" << Pointers::playerBasePtr << "\n";

	DWORD entityListPattern = Utils::FindPattern("client.dll", "\x8B\x00\x00\x00\x00\x00\x85\xC9\x74\x42\x8B\x01\xFF\x50\x1C\x8B\xF8", "x?????xxxxxxxxxxx") + 2;
	Dumper::Pointers::entityListPtr = entityListPattern;
	std::cout << std::hex << " Entity list ptr found at: 0x" << Pointers::entityListPtr << "\n";

	DWORD writableViewAnglesBasePattern = Utils::FindPattern("engine.dll", "\xA1\x00\x00\x00\x00\x83\xB8\x00\x00\x00\x00\x00\x0F\x9D\xC0\xC3\x55", "x????xx?????xxxxx") + 1;
	Dumper::Pointers::writableViewAnglesBase = *(DWORD*)writableViewAnglesBasePattern;
	std::cout << std::hex << " Writable view angles base ptr found at: 0x" << Pointers::writableViewAnglesBase << "\n";

	//
	// Offset patterns
	// 
	DWORD m_iHealthOffsetPattern = Utils::FindPattern("client.dll", "\x75\x09\x83\xB9\x00\x00\x00\x00\x00\x7F\x2D\x8B\x01", "xxxx?????xxxx") + 4;
	Dumper::Offsets::m_iHealth = *(DWORD*)m_iHealthOffsetPattern;
	std::cout << std::hex << " m_iHealth found at: 0x" << Offsets::m_iHealth << "\n";

	DWORD m_iArmorOffsetPattern = Utils::FindPattern("client.dll", "\x89\x4D\xF4\x8B\x00\x00\x00\x00\x00\x33\xD2", "xxxx?????xx") + 5;
	Dumper::Offsets::m_iArmor = *(DWORD*)m_iArmorOffsetPattern;
	std::cout << std::hex << " m_iArmor found at: 0x" << Offsets::m_iArmor << "\n";

	DWORD bDormantOffsetPattern = Utils::FindPattern("client.dll", "\x8B\xF1\x88\x00\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x53", "xxx?????x????x") + 4;
	Dumper::Offsets::bDormant = *(DWORD*)bDormantOffsetPattern;
	std::cout << std::hex << " bDormant found at: 0x" << Offsets::bDormant << "\n";

	// NOTE: this is huge but it dumps 6 offsets(Viewangles: x y z and Coordinates: x y z) or 2 Vec3's(Vec3 viewAngles and Vec3 coordinates)
	DWORD viewAnglesAndCoordinatesOffsetPattern = Utils::FindPattern("client.dll", "\x8B\x00\x00\x00\x00\x00\x89\x00\x00\x00\x00\x00\x8B\x00\x00\x00\x00\x00\x89\x00\x00\x00\x00\x00\x8B\x00\x00\x00\x00\x00\x89\x00\x00\x00\x00\x00\xF3\x00\x00\x00\x00\x00\x00\x00\x0F\x2E\x00\x00\x00\x00\x00\x9F\xF6\xC4\x44\x7A\x2A\xF3\x00\x00\x00\x00\x00\x00\x00\x0F\x2E\x00\x00\x00\x00\x00\x9F\xF6\xC4\x44\x7A\x15\xF3", "x?????x?????x?????x?????x?????x?????x???????xx?????xxxxxxx???????xx?????xxxxxxx");
	viewAnglesAndCoordinatesOffsetPattern += 2;
	Dumper::Offsets::coordinates = *(DWORD*)viewAnglesAndCoordinatesOffsetPattern;
	std::cout << std::hex << " Coordinates found at: 0x" << Offsets::coordinates << "\n";

	viewAnglesAndCoordinatesOffsetPattern += 38;
	Dumper::Offsets::viewAngles = *(DWORD*)viewAnglesAndCoordinatesOffsetPattern;
	std::cout << std::hex << " View Angles found at: 0x" << Offsets::viewAngles << "\n";

	DWORD m_iShotsFiredOffsetPattern = Utils::FindPattern("client.dll", "\x85\xF6\x74\x51\x83\xBE\x00\x00\x00\x00\x00\x74\x0A", "xxxxxx?????xx") + 6;
	Dumper::Offsets::m_iShotsFired = *(DWORD*)m_iShotsFiredOffsetPattern;
	std::cout << std::hex << " m_iShotsFired found at: 0x" << Offsets::m_iShotsFired << "\n";

	//DWORD m_bSpottedOffsetPattern = Utils::FindPattern("client.dll", "\x83\xE0\x0F\x80\xBF\x00\x00\x00\x00\x00\x74\x15", "xxxxx?????xx") + 5;
	Dumper::Offsets::m_bSpotted = 0x93D; //*(DWORD*)m_bSpottedOffsetPattern;
	std::cout << std::hex << " m_bSpotted found at: 0x" << Offsets::m_bSpotted << "\n";

	DWORD m_iTeamOffsetPattern = Utils::FindPattern("client.dll", "\x8B\x00\x00\x00\x00\x00\xE9\x00\x00\x00\x00\xCC\xCC\xCC\xCC\xCC\x8B\x00\x00\x00\x00\x00\xC3", "x?????x????xxxxxx?????x") + 18;
	Dumper::Offsets::m_iTeam = *(DWORD*)m_iTeamOffsetPattern;
	std::cout << std::hex << " m_iTeam found at: 0x" << Offsets::m_iTeam << "\n";

	DWORD m_FlashDurationOffsetPattern = Utils::FindPattern("client.dll", "\xF3\x0F\x11\x45\xF0\xF3\x00\x00\x00\x00\x00\x00\x00\x0F\x57\xC9", "xxxxxx???????xxx") + 9;
	Dumper::Offsets::m_FlashDuration = *(DWORD*)m_FlashDurationOffsetPattern;
	std::cout << std::hex << " m_FlashDuration found at: 0x" << Offsets::m_FlashDuration << "\n";

	DWORD m_iCashOffsetPattern = Utils::FindPattern("client.dll", "\x74\x0A\x8B\x00\x00\x00\x00\x00\xEB\x04", "xxx?????xx") + 4;
	Dumper::Offsets::m_iCash = *(DWORD*)m_iCashOffsetPattern;
	std::cout << std::hex << " m_iCash found at: 0x" << Offsets::m_iCash << "\n";

	DWORD m_iCrosshairIdOffsetPattern = Utils::FindPattern("client.dll", "\x8B\xF9\x89\x7D\xD8\xC7\x87\x00\x00\x00\x00", "xxxxxxx????") + 7;
	Dumper::Offsets::m_iCrosshairId = *(DWORD*)m_iCrosshairIdOffsetPattern;
	std::cout << std::hex << " m_iCrosshairId found at: 0x" << Offsets::m_iCrosshairId << "\n";

	DWORD m_iFOVOffsetPattern = Utils::FindPattern("client.dll", "\x66\x00\x00\x00\x00\x00\x00\x00\xF3\x0F\x10\x45\xFC\x0F\x5B\xF6", "x???????xxxxxxxx") + 4;
	Dumper::Offsets::m_iFOV = *(DWORD*)m_iFOVOffsetPattern;
	std::cout << std::hex << " m_iFOV found at: 0x" << Offsets::m_iFOV << "\n";

	DWORD m_iDefaultFOVOffsetPattern = Utils::FindPattern("client.dll", "\xFF\xB7\x00\x00\x00\x00\x8B\x01\xFF\x50\x40", "xx????xxxxx") + 2;
	Dumper::Offsets::m_iDefaultFOV = *(DWORD*)m_iDefaultFOVOffsetPattern;
	std::cout << std::hex << " m_iDefaultFOV found at: 0x" << Offsets::m_iDefaultFOV << "\n";

	DWORD m_iVelocityOffsetPattern = Utils::FindPattern("client.dll", "\x9F\xF6\xC4\x44\x7A\x1F\x0F\x2E\x00\x00\x00\x00\x00\x9F", "xxxxxxxx?????x") + 9;
	Dumper::Offsets::m_iVelocity = *(DWORD*)m_iVelocityOffsetPattern;
	std::cout << std::hex << " m_iVelocity found at: 0x" << Offsets::m_iVelocity << "\n";

	DWORD dwForceShotOffsetPattern = Utils::FindPattern("client.dll", "\x8B\x00\x00\x00\x00\x00\x8B\xD6\x8B\xC1\x83\xCA\x01\x24\x03", "x?????xxxxxxxxx") + 2;
	Dumper::Offsets::dwForceShot = *(DWORD*)dwForceShotOffsetPattern;
	std::cout << std::hex << " dwForceShot found at: 0x" << Offsets::dwForceShot << "\n";

	DWORD m_fFlagsOffsetPattern = Utils::FindPattern("client.dll", "\x74\x75\xF7\x86\x00\x00\x00\x00\x00\x00\x00\x00\x75\x69", "xxxx????????xx") + 4;
	Dumper::Offsets::m_fFlags = *(DWORD*)m_fFlagsOffsetPattern;
	std::cout << std::hex << " m_fFlags found at: 0x" << Offsets::m_fFlags << "\n";

	DWORD bHasDefuserOffsetPattern = Utils::FindPattern("client.dll", "\x74\x77\x80\xBE\x00\x00\x00\x00\x00\x74\x23", "xxxx?????xx") + 4;
	Dumper::Offsets::bHasDefuser = *(DWORD*)bHasDefuserOffsetPattern;
	std::cout << std::hex << " bHasDefuser found at: 0x" << Offsets::bHasDefuser << "\n";

	DWORD dwForceJumpOffsetPattern = Utils::FindPattern("client.dll", "\x8B\x00\x00\x00\x00\x00\x8B\xD6\x8B\xC1\x83\xCA\x02", "x?????xxxxxxx") + 2;
	Dumper::Offsets::dwForceJump = *(DWORD*)dwForceJumpOffsetPattern;
	std::cout << std::hex << " dwForceJump found at: 0x" << Offsets::dwForceJump << "\n";

	DWORD writableViewAnglesOffsetPattern = Utils::FindPattern("engine.dll", "\x8B\x4D\x08\x8B\x00\x00\x00\x00\x00\x5F\x89\x01", "xxxx?????xxx") + 5;
	Dumper::Offsets::writableViewAngles = *(DWORD*)writableViewAnglesOffsetPattern;
	std::cout << std::hex << " writableViewAngles found at: 0x" << Offsets::writableViewAngles << "\n";

	DWORD m_dwBoneMatrixOffsetPattern = Utils::FindPattern("client.dll", "\x74\x0E\x57\xFF\xB6\x00\x00\x00\x00\x8B\xCE", "xxxxx????xx") + 5;
	Dumper::Offsets::m_dwBoneMatrix = *(DWORD*)m_dwBoneMatrixOffsetPattern;
	Dumper::Offsets::dwViewMatrix = 0x4DF1E74;
	std::cout << std::hex << " dwViewMatrix found at: 0x" << Offsets::dwViewMatrix << "\n";
}

// NOTE: too hardcoded
void Dumper::WriteToFile()
{
	// Ofstream
	std::ofstream file;

	// Open the file
	file.open("CSGO.hpp");

	// then just write shit w c++ syntax...
	file << "#pragma once" << "\n";
	file << "#include <Windows.h>" << "\n";
	// Padding
	file << "\n";

	// Offset namespace
	file << "namespace Offsets" << "\n";
	file << "{" << "\n";

	// Offsets
	file << std::hex << "     " << "DWORD" << " m_iHealth = 0x" << Offsets::m_iHealth << ";" << "\n";
	file << std::hex << "     " << "DWORD" << " m_iArmor = 0x" << Offsets::m_iArmor << ";" << "\n";
	file << std::hex << "     " << "DWORD" << " bDormant = 0x" << Offsets::bDormant << ";" << "\n";
	file << std::hex << "     " << "DWORD" << " viewAngles = 0x" << Offsets::viewAngles << ";" << "\n";
	file << std::hex << "     " << "DWORD" << " coordinates = 0x" << Offsets::coordinates << ";" << "\n";
	file << std::hex << "     " << "DWORD" << " m_iShotsFired = 0x" << Offsets::m_iShotsFired << ";" << "\n";
	file << std::hex << "     " << "DWORD" << " m_bSpotted = 0x" << Offsets::m_bSpotted << ";" << "\n";
	file << std::hex << "     " << "DWORD" << " m_iTeam = 0x" << Offsets::m_iTeam << ";" << "\n";
	file << std::hex << "     " << "DWORD" << " m_FlashDuration = 0x" << Offsets::m_FlashDuration << ";" << "\n";
	file << std::hex << "     " << "DWORD" << " m_iCash = 0x" << Offsets::m_iCash << ";" << "\n";
	file << std::hex << "     " << "DWORD" << " m_iCrosshairId = 0x" << Offsets::m_iCrosshairId << ";" << "\n";
	file << std::hex << "     " << "DWORD" << " m_iFOV = 0x" << Offsets::m_iFOV << ";" << "\n";
	file << std::hex << "     " << "DWORD" << " m_iDefaultFOV = 0x" << Offsets::m_iDefaultFOV << ";" << "\n";
	file << std::hex << "     " << "DWORD" << " m_iVelocity = 0x" << Offsets::m_iVelocity << ";" << "\n";
	file << std::hex << "     " << "DWORD" << " dwForceShot = 0x" << Offsets::dwForceShot << ";" << "\n";
	file << std::hex << "     " << "DWORD" << " m_fFlags = 0x" << Offsets::m_fFlags << ";" << "\n";
	file << std::hex << "     " << "DWORD" << " bHasDefuser = 0x" << Offsets::bHasDefuser << ";" << "\n";
	file << std::hex << "     " << "DWORD" << " dwForceJump = 0x" << Offsets::dwForceJump << ";" << "\n";
	file << std::hex << "     " << "DWORD" << " dwViewMatrix = 0x" << Offsets::dwViewMatrix << ";" << "\n";
	file << std::hex << "     " << "DWORD" << " m_dwBoneMatrix = 0x" << Offsets::m_dwBoneMatrix << ";" << "\n";

	file << "}" << "\n";

	// Close the file
	file.close();
}

void Dumper::Cleanup()
{
	// Filename
	std::filesystem::path file{ "CSGO.hpp" };

	// If the file exists in CSGO's directory
	if (std::filesystem::exists(file))
		// Delete it
		std::filesystem::remove(file);
}	