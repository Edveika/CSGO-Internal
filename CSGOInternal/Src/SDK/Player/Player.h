#pragma once

class Player
{
public:
	bool IsInGame();
	bool IsDormant();
	bool IsAlive();
	bool IsWearingArmor();
	bool IsCarryingDefuser();
	bool EntityIsFlashed();
	bool EntityIsSpotted();
	bool EntityIsOnTheGround();
	bool EntityIsDucking();
	bool EntityIsMoving();
};