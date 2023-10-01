#include "../../Includes.h"

bool Player::IsInGame()
{
	if (this != NULL)
		return true;

	return false;
}

bool Player::IsDormant()
{
	if (*(bool*)(this + Dumper::Offsets::bDormant))
		return true;

	return false;
}

bool Player::IsAlive()
{
	if (*(int*)(this + Dumper::Offsets::m_iHealth) > 0)
		return true;

	return false;
}

bool Player::IsWearingArmor()
{
	if (*(int*)(this + Dumper::Offsets::m_iArmor) > 0)
		return true;

	return false;
}

bool Player::IsCarryingDefuser()
{
	if (*(bool*)(this + Dumper::Offsets::bHasDefuser))
		return true;

	return false;
}

bool Player::EntityIsFlashed()
{
	if (*(int*)(this + Dumper::Offsets::m_FlashDuration) > 0)
		return true;

	return false;
}

bool Player::EntityIsSpotted()
{
	if (*(bool*)(this + Dumper::Offsets::m_bSpotted))
		return true;

	return false;
}

bool Player::EntityIsOnTheGround()
{
	if (*(int*)(this + Dumper::Offsets::m_fFlags) & isOnGround)
		return true;

	return false;
}

bool Player::EntityIsDucking()
{
	if (*(int*)(this + Dumper::Offsets::m_fFlags) & isDucking)
		return true;

	return false;
}

bool Player::EntityIsMoving()
{
	if (*(int*)(this + Dumper::Offsets::m_iVelocity) > 0)
		return true;

	return false;
}