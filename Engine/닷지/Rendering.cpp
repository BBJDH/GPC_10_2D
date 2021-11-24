#include<Windows.h>

namespace Rendering
{
	namespace
	{
		HBITMAP hmapbit, hfighterbit, hmissilebit;
		BITMAP fighter, missile;
	}
	void update_player(HWND const& hwindow, HBITMAP const& hfighterbit,
		BITMAP const& fighter, HBITMAP const& hmapbit, int player_x, int player_y)
	{
		HDC hdc = GetDC(hwindow);
		HDC hvirtualdc = CreateCompatibleDC(hdc);
		HDC hbufferdc = CreateCompatibleDC(hdc);
		HBITMAP hvirtualbit = CreateCompatibleBitmap(hdc, 800, 600);
		SelectObject(hvirtualdc, hvirtualbit);

		HBITMAP oldbit = static_cast<HBITMAP>(SelectObject(hbufferdc, hmapbit));
		BitBlt(hvirtualdc, 0, 0, 800, 600, hbufferdc, 0, 0, SRCCOPY);
		SelectObject(hbufferdc, hfighterbit);

		TransparentBlt(hvirtualdc, player_x, player_y, fighter.bmWidth, fighter.bmHeight,
			hbufferdc, 0, 0, fighter.bmWidth, fighter.bmHeight, RGB(255, 255, 255));
		BitBlt(hdc, 0, 0, 800, 600, hvirtualdc, 0, 0, SRCCOPY);
		SelectObject(hbufferdc, oldbit);
		DeleteDC(hbufferdc);
		DeleteDC(hvirtualdc);
		DeleteObject(hvirtualbit);
		ReleaseDC(hwindow, hdc);
	}
}