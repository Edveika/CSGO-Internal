#pragma once

class ESP
{
public:
	float* matrix = (float*)(clientBase + 0x4DECC84);
	ID3DXLine* LineL;
public:
	void Draw();

	void DrawBoxESP(Vector2 top, Vector2 bottom, float thickness, D3DCOLOR color, D3DCOLOR fillColor);
	void DrawHealthESP(DWORD entity, Vector2 top, Vector2 bottom, float thickness);
	void DrawArmorESP(DWORD entity, Vector2 top, Vector2 bottom, float thickness);
	void DrawSkeletonESP(DWORD entity, float thickness);
	void DrawSnapline(Vector2 screenPos, float thickness, D3DCOLOR color);
};
extern ESP* g_ESP;