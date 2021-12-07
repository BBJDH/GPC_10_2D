#include<Windows.h>
#include<vector>
enum Shape_name
{
	circle=1, rect,
};

namespace Rendering
{
	namespace 
	{
		int const player_size = 50;
		HBITMAP hmapbit;
		XFORM rotate;
	}
	void update(HWND const& hwindow, int const player_x, int const player_y,
		std::vector<int*> const& Shapepos, std::vector<double*> const& ang)
	{
		
		HDC hdc = GetDC(hwindow);
		HDC hvirtualdc = CreateCompatibleDC(hdc);
		HBITMAP hvirtualbit = CreateCompatibleBitmap(hdc, 800, 600);
		SelectObject(hvirtualdc, hvirtualbit);
		//Rectangle(hvirtualdc, player_x- player_size, player_y- player_size, player_x + player_size, player_y + player_size);
		//Ellipse(hvirtualdc, player_x - player_size, player_y - player_size, player_x + player_size, player_y + player_size);
		if (!Shapepos.empty())
		{
			for (size_t i = 0; i < Shapepos.size(); i++)
			{

				switch (Shapepos[i][1])
				{
				case circle:
				{
					Ellipse(hvirtualdc, Shapepos[i][2] - Shapepos[i][4], Shapepos[i][3] - Shapepos[i][5],
										Shapepos[i][2] + Shapepos[i][4], Shapepos[i][3] + Shapepos[i][5]);
					break;
				}
				case rect:
				{
					Rectangle(hvirtualdc, Shapepos[i][2] - Shapepos[i][4], Shapepos[i][3] - Shapepos[i][5],
										  Shapepos[i][2] + Shapepos[i][4], Shapepos[i][3] + Shapepos[i][5]);
					break;
				}	
				
				}

				
			}
		}
		Ellipse(hvirtualdc, player_x - 2, player_y - 2, player_x + 2, player_y + 2);

		BitBlt(hdc, 0, 0, 800, 600, hvirtualdc, 0, 0, SRCCOPY);
		DeleteDC(hvirtualdc);
		DeleteObject(hvirtualbit);
		ReleaseDC(hwindow, hdc);
	}
}