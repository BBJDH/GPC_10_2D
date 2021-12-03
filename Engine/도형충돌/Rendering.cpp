#include<Windows.h>

namespace Rendering
{
	HBITMAP hmapbit;
	void update(HWND const& hwindow, int const rec_x, int const rec_y, int const width, int const height)
	{
		HDC hdc = GetDC(hwindow);
		HDC hvirtualdc = CreateCompatibleDC(hdc);
		HBITMAP hvirtualbit = CreateCompatibleBitmap(hdc, 800, 600);
		SelectObject(hvirtualdc, hvirtualbit);

		Rectangle(hvirtualdc, rec_x, rec_y, rec_x + width, rec_y + height);

		BitBlt(hdc, 0, 0, 800, 600, hvirtualdc, 0, 0, SRCCOPY);
		DeleteDC(hvirtualdc);
		DeleteObject(hvirtualbit);
		ReleaseDC(hwindow, hdc);
	}
}