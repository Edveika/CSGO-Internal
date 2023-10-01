#include "../../Includes.h"

DWORD GetBestTarget()
{
	DWORD target = NULL;
	float oldDistance = FLT_MAX;
	float newDistance = 0;

	DWORD viewAngleBaseAddy = *(DWORD*)(Dumper::Pointers::writableViewAnglesBase);
	DWORD viewAngleAddy = (viewAngleBaseAddy + Dumper::Offsets::writableViewAngles);
	Vector3 viewAngles = *(Vector3*)(viewAngleAddy);

	for (int i = 0; i < 64; ++i)
	{
		DWORD entity = *(DWORD*)(*(DWORD*)(Dumper::Pointers::entityListPtr) + i * 0x10);

		if (entity == localPlayer)
			continue;

		if (!CSGO::EntityIsInGame(entity))
			continue;

		if (CSGO::EntityIsDormant(entity))
			continue;

		if (!CSGO::EntityIsAlive(entity))
			continue;

		if (!CSGO::EntityIsEnemy(entity))
			continue;

		Vector3 src = *(Vector3*)(localPlayer + Dumper::Offsets::coordinates);
		Vector3 dst = *(Vector3*)(entity + Dumper::Offsets::coordinates);

		Vector3 angleTo;
		angleTo.x = -asin((dst.z - src.z) / Math::Distance(src, dst)) * (180.0f / PI);
		angleTo.y = atan2(dst.y - src.y, dst.x - src.x) * (180.0f / PI);
		angleTo.z = 0.0f;

		newDistance = Math::Distance(viewAngles, angleTo);

		if (newDistance < oldDistance)
		{
			oldDistance = newDistance;
			target = entity;
		}
	}

	return target;
}

void Aimbot::Run()
{
	if (!GetAsyncKeyState(VK_XBUTTON1))
		return;

	DWORD target = GetBestTarget();

	if (target == localPlayer)
		return;

	if (!CSGO::EntityIsInGame(target))
		return;

	if (CSGO::EntityIsDormant(target))
		return;

	if (!CSGO::EntityIsAlive(target))
		return;

	DWORD viewAngleAddress = (*(DWORD*)(Dumper::Pointers::writableViewAnglesBase)) + Dumper::Offsets::writableViewAngles;
	Vector3* viewAngles = (Vector3*)(viewAngleAddress);

	Vector3 src = CSGO::GetBonePos(localPlayer, head);
	Vector3 dst = CSGO::GetBonePos(target, head);
	Vector3 toAim = Math::CalcAngle(src, dst);

	if (toAim.x >= -89.f && toAim.x <= 89.f && toAim.y >= -180.f && toAim.y <= 180.f)
	{
		viewAngles->x = toAim.x;
		viewAngles->y = toAim.y;
	}
}
Aimbot* g_Aimbot;