#include "../../Includes.h"

bool CSGO::EntityIsInGame(DWORD entity)
{
	// If entity not is NULL
	if (entity != NULL)
		// Player is in game
		return true;

	// If entity is NULL, there is no entity
	return false;
}

bool CSGO::EntityIsEnemy(DWORD entity)
{
	int entTeam = *(int*)(entity + Dumper::Offsets::m_iTeam);
	int localTeam = *(int*)(localPlayer + Dumper::Offsets::m_iTeam);

	// check if ent is alive
	if (EntityIsAlive(entity))
		// If entity's m_iTeam value is not equal to local player's
		if (entTeam != localTeam)
			// Entity is enemy
			return true;

	// If its equal, entity is friendly
	return false;
}

bool CSGO::EntityIsDormant(DWORD entity)
{
	// If entity's bDormant value is true
	if (*(bool*)(entity + Dumper::Offsets::bDormant))
		// Entity is dormant :OO
		return true;

	// If its not true, entity is not dormant
	return false;
}

bool CSGO::EntityIsAlive(DWORD entity)
{
	// If entity's health is more then 0
	if (*(int*)(entity + Dumper::Offsets::m_iHealth) > 0)
		// Entity is alive
		return true;

	// If its 0 or less(somehow), entity is dead
	return false;
}

bool CSGO::EntityHasArmor(DWORD entity)
{
	// If armor value is more then 0
	if (*(int*)(entity + Dumper::Offsets::m_iArmor) > 0)
		// Entity has armor O.o
		return true;

	// Otherwise it doesnt...
	return false;
}

bool CSGO::EntityHasDefuser(DWORD entity)
{
	// If the entity has a defuser
	if (*(bool*)(entity + Dumper::Offsets::bHasDefuser))
		// Entity has a defuser :)
		return true;

	// Otherwise entity does not have a defuser
	return false;
}

bool CSGO::EntityIsTarget(DWORD entity)
{
	// Well, basically if the entity is alive, not dormant and in game
	if (EntityIsAlive(entity) && !EntityIsDormant(entity) && EntityIsInGame(entity))
		// Hes a target
		return true;

	// Otherwise...
	return false;
}

bool CSGO::EntityIsFlashed(DWORD entity)
{
	// If entity's flash duration is more then 0
	if (*(int*)(entity + Dumper::Offsets::m_FlashDuration) > 0)
		// Entity is flashed
		return true;

	// If not, entity is not flashed
	return false;
}

bool CSGO::EntityIsSpotted(DWORD entity)
{
	// If entity is spotted
	if (*(bool*)(entity + Dumper::Offsets::m_bSpotted))
		// Entity is spotted :P
		return true;

	// Entity not spotted
	return false;
}

bool CSGO::EntityIsOnTheGround(DWORD entity)
{
	// If m_fFlags and isOnGround are "the same"
	if (*(int*)(entity + Dumper::Offsets::m_fFlags) & isOnGround)
		// Entity is on the ground
		return true;

	// Otherwise entity is in the air
	return false;
}

bool CSGO::EntityIsDucking(DWORD entity)
{
	// If m_fFlags and isDucking are "the same"
	if (*(int*)(entity + Dumper::Offsets::m_fFlags) & isDucking)
		// Entity is ducking
		return true;

	//Otherwise hes not ducking...
	return false;
}

bool CSGO::EntityIsMoving(DWORD entity)
{
	// If velocity is more then 0
	if (*(int*)(entity + Dumper::Offsets::m_iVelocity) > 0)
		// Entity is moving
		return true;

	// Else entity is standing still
	return false;
}

Vector3 CSGO::GetBonePos(DWORD entity, int boneID)
{
	// Bone position/result variable
	Vector3 bonePos;
	// Get the bone base address of the selected entity
	DWORD boneBase = *(DWORD*)(entity + 0x26A8);

	// Get the value x value of the selected bone 
	bonePos.x = *(float*)(boneBase + 0x30 * boneID + 0x0C);
	// Get the value y value of the selected bone 
	bonePos.y = *(float*)(boneBase + 0x30 * boneID + 0x1C);
	// Get the value z value of the selected bone 
	bonePos.z = *(float*)(boneBase + 0x30 * boneID + 0x2C);

	// Return the bone pos a.k.a. the result :)
	return bonePos;
}