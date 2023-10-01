#include "../../Includes.h"

void ESP::Draw()
{
	// Loop through entity list
	for (int i = 1; i < 64; ++i)
	{
		// Get the current entity
		DWORD entity = *(DWORD*)(*(DWORD*)(Dumper::Pointers::entityListPtr) + i * 0x10);

		if (entity == localPlayer)
			continue;

		if (!CSGO::EntityIsInGame(entity))
			continue;

		if (!CSGO::EntityIsAlive(entity))
			continue;

		if (CSGO::EntityIsDormant(entity))
			continue;

		D3DCOLOR color;
		D3DCOLOR fillColor;
		if (CSGO::EntityIsEnemy(entity))
		{
			color = D3DCOLOR_ARGB(255, 255, 61, 61);
			fillColor = D3DCOLOR_ARGB(50, 255, 0, 0);
		}
		else
		{
			color = D3DCOLOR_ARGB(255, 4, 0, 255);
			fillColor = D3DCOLOR_ARGB(50, 0, 166, 255);
		}

		// fucked up position values
		Vector3 headPos = CSGO::GetBonePos(entity, head);
		headPos.z += 8;

		Vector2 screenPosTop, screenPosBottom, screenPosNeck;;
		if (Math::WorldToScreen(*(Vector3*)(entity + Dumper::Offsets::coordinates), screenPosBottom, matrix, windowWidth, windowHeight))
		{
			if (Math::WorldToScreen(headPos, screenPosTop, matrix, windowWidth, windowHeight))
			{
				DrawBoxESP(screenPosTop, screenPosBottom, 1.f, color, fillColor);
				//DrawHealthESP(entity, screenPosTop, screenPosBottom, 2.f);
				//DrawArmorESP(entity, screenPosTop, screenPosBottom, 2.f);
			}

			DrawSnapline({ screenPosTop.x,screenPosBottom.y }, 1.f, color);
		}
		
		// Reveal the entity on the radar
		*(bool*)(entity + Dumper::Offsets::m_bSpotted) = true;
	}
}

void ESP::DrawBoxESP(Vector2 top, Vector2 bottom, float thickness, D3DCOLOR color, D3DCOLOR fillColor)
{
	float height = abs(top.y - bottom.y);
	float width = height / 4;

	Vector2 topLeft, topRight;
	topLeft.x = top.x - width;
	topRight.x = top.x + width;
	topLeft.y = top.y;
	topRight.y = top.y;

	Vector2 bottomLeft, bottomRight;
	bottomLeft.x = top.x - width;
	bottomRight.x = top.x + width;
	bottomLeft.y = bottom.y;
	bottomRight.y = bottom.y;

	// Draws a line froom top left to top right
	DrawLine(topLeft.x, topLeft.y, topRight.x, topRight.y, thickness, color);
	// Draws a line from bottom left to bottom right
	DrawLine(bottomLeft.x, bottomLeft.y, bottomRight.x, bottomRight.y, thickness, color);
	// Draws a line from top left to bottom left
	DrawLine(topLeft.x, topLeft.y, bottomLeft.x, bottomLeft.y, thickness, color);
	// Draws a line frop top right to bottom right
	DrawLine(topRight.x, topRight.y, bottomRight.x, bottomRight.y, thickness, color);

	// Draws a box fill
	// Lags?
	DrawLine(top.x, bottomLeft.y, top.x, topLeft.y, width * 2, fillColor);
}

void ESP::DrawHealthESP(DWORD entity, Vector2 top, Vector2 bottom, float thickness)
{
	float height = abs(top.y - bottom.y);
	float width = height / 4;

	int currEntHealth = *(int*)(entity + Dumper::Offsets::m_iHealth);
	float healthPercent = currEntHealth / 100.f;
	float healthHeight = height * healthPercent;

	D3DCOLOR color;
	if (currEntHealth >= 75)
		color = D3DCOLOR_ARGB(255, 3, 252, 36);
	else if (currEntHealth >= 50)
		color = D3DCOLOR_ARGB(255, 255, 247, 0);
	else if (currEntHealth >= 25)
		color = D3DCOLOR_ARGB(255, 255, 77, 0);
	else
		color = D3DCOLOR_ARGB(255, 255, 0, 0);

	Vector2 healthBarPosBottom;
	healthBarPosBottom.x = (top.x - width) - (thickness + 1);
	healthBarPosBottom.y = bottom.y;

	Vector2 healthBarPosTop;
	healthBarPosTop.x = (top.x - width) - (thickness + 1);
	healthBarPosTop.y = top.y + height - healthHeight;

	DrawLine(healthBarPosBottom.x, healthBarPosBottom.y, healthBarPosTop.x, healthBarPosTop.y, thickness, color);
}

void ESP::DrawArmorESP(DWORD entity, Vector2 top, Vector2 bottom, float thickness)
{
	float height = abs(top.y - bottom.y);
	float width = height / 4;

	int currEntArmor = *(int*)(entity + Dumper::Offsets::m_iArmor);
	float armorPercent = currEntArmor / 100.f;
	float armorHeight = height * armorPercent;

	Vector2 armorBarPosBottom;
	armorBarPosBottom.x = (top.x - width) - (thickness + 1) * 2;
	armorBarPosBottom.y = bottom.y;

	Vector2 armorBarPosTop;
	armorBarPosTop.x = (top.x - width) - (thickness + 1) * 2;
	armorBarPosTop.y = top.y + height - armorHeight;

	DrawLine(armorBarPosBottom.x, armorBarPosBottom.y, armorBarPosTop.x, armorBarPosTop.y, thickness, D3DCOLOR_ARGB(255, 242, 255, 0));
}

void ESP::DrawSkeletonESP(DWORD entity, float thickness)
{

}

void ESP::DrawSnapline(Vector2 screenPos, float thickness, D3DCOLOR color)
{
	DrawLine(windowWidth / 2.f, windowHeight, screenPos.x, screenPos.y, thickness, color);
}
ESP* g_ESP;