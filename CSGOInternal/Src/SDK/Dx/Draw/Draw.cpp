#include "../../../Includes.h"

void DrawFilledRect(LONG x, LONG y, LONG width, LONG height, D3DCOLOR color)
{
	D3DRECT rect = { x, y, x + width, y + height };
	pDevice->Clear(1, &rect, D3DCLEAR_TARGET, color, 0, 0);
}

void DrawLine(FLOAT x1, FLOAT y1, FLOAT x2, FLOAT y2, FLOAT thickness, D3DCOLOR color)
{
	if (!g_ESP->LineL)
		D3DXCreateLine(pDevice, &g_ESP->LineL);

	D3DXVECTOR2 Line[2];
	Line[0] = D3DXVECTOR2(x1, y1);
	Line[1] = D3DXVECTOR2(x2, y2);
	g_ESP->LineL->SetWidth(thickness);
	g_ESP->LineL->Draw(Line, 2, color);
}

void DrawBox(FLOAT x, FLOAT y, FLOAT height, FLOAT width, FLOAT thickness, D3DCOLOR color)
{
	DrawLine(x, y, x + width, y, thickness, color);
	DrawLine(x, y, x, y - width, thickness, color);
	DrawLine(x + width, y, x + width, y - height, thickness, color);
	DrawLine(x, y - height, x + width, y - height, thickness, color);
}