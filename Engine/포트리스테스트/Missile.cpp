#include"stdafx.h"

#include "Missile.h"

Missile::Missile(Position const& pos, unsigned const width, unsigned const height):
	Object(pos, width, height),bomb_range_w(60),bomb_range_h(40)
{
}

Missile& Missile::operator=(Missile const& other_miss)
{
	assign(other_miss);
	return *this;
}

void Missile::boom(HDC const& hmapdc)
{
	HBRUSH hNewBrush = CreateSolidBrush(RGB(255,0,255));
	HPEN hNewPen = CreatePen(PS_SOLID, 2, 0xff00ff);
	HBITMAP hOldBmp = static_cast<HBITMAP>(SelectObject(hmapdc, hNewBrush));
	SelectObject(hmapdc, hNewPen);
	int const x = static_cast<int const>(pos.x);
	int const y = static_cast<int const>(pos.y);
	Ellipse(hmapdc, x-bomb_range_w, y-bomb_range_h, x+bomb_range_w, y+bomb_range_h);
	SelectObject(hmapdc, hOldBmp);
	DeleteObject(hNewBrush);
	DeleteObject(hNewPen);
}
