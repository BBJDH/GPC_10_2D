#include<Windows.h>
#include<vector>

namespace Rendering
{
	namespace 
	{
		int const player_size = 50;
		HBITMAP hmapbit;
		XFORM rotate;
	}
	void update(HWND const& hwindow, int const player_x, int const player_y,
		std::vector<POINT*> const& rectpos, std::vector<double*> const& ang)
	{
		
		HDC hdc = GetDC(hwindow);
		HDC hvirtualdc = CreateCompatibleDC(hdc);
		HBITMAP hvirtualbit = CreateCompatibleBitmap(hdc, 800, 600);
		SelectObject(hvirtualdc, hvirtualbit);
		Rectangle(hvirtualdc, player_x- player_size, player_y- player_size, player_x + player_size, player_y + player_size);
		if (!rectpos.empty())
		{
			for (size_t i = 0; i < rectpos.size(); i++)
			{
				POINT rect[5] = 
				{	
					{rectpos[i][1].x,rectpos[i][1].y}, //오른쪽위
					{rectpos[i][2].x,rectpos[i][2].y}, //왼쪽위점
					{rectpos[i][3].x,rectpos[i][3].y}, //왼쪽아래점
					{rectpos[i][4].x,rectpos[i][4].y}, //오른쪽아래점
					{rectpos[i][1].x,rectpos[i][1].y}  //왼쪽위점
				};
				Polygon(hvirtualdc, rect,5 );
			}
		}
		BitBlt(hdc, 0, 0, 800, 600, hvirtualdc, 0, 0, SRCCOPY);
		DeleteDC(hvirtualdc);
		DeleteObject(hvirtualbit);
		ReleaseDC(hwindow, hdc);
	}
}