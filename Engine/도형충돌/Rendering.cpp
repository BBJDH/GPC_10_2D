#include<Windows.h>
#include<vector>

namespace Rendering
{
	namespace 
	{
		int const size = 50;
		HBITMAP hmapbit;
		XFORM rotate;
	}
	void update(HWND const& hwindow, int const player_x, int const player_y,
		std::vector<POINT> const& rectpos,std::vector<double> const& ang)
	{
		
		HDC hdc = GetDC(hwindow);
		HDC hvirtualdc = CreateCompatibleDC(hdc);
		HBITMAP hvirtualbit = CreateCompatibleBitmap(hdc, 800, 600);
		SelectObject(hvirtualdc, hvirtualbit);
		Rectangle(hvirtualdc, player_x-size, player_y-size, player_x + size, player_y + size);
		if (!rectpos.empty())
		{
			for (size_t i = 0; i < rectpos.size(); i++)
			{
				rotate.eM11 = static_cast<float>(cos(ang[i]));
				rotate.eM12 = static_cast<float>(sin(ang[i]));
				rotate.eM21 = static_cast<float>(-sin(ang[i]));
				rotate.eM22 = static_cast<float>(cos(ang[i]));
				rotate.eDx = rectpos[i].x;
				rotate.eDy = rectpos[i].y;
				SetGraphicsMode(hvirtualdc,GM_ADVANCED);
				SetWorldTransform(hvirtualdc, &rotate);
				Rectangle(hvirtualdc, rectpos[i].x - size, rectpos[i].y - size, rectpos[i].x + size, rectpos[i].y + size);
			}

		}
		BitBlt(hdc, 0, 0, 800, 600, hvirtualdc, 0, 0, SRCCOPY);
		DeleteDC(hvirtualdc);
		DeleteObject(hvirtualbit);
		ReleaseDC(hwindow, hdc);
	}
}