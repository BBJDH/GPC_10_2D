#include"stdafx.h"

namespace Physics
{
	void find_nextstep(HDC const& hmapdc, Tank& tank, bool const isright);
}

namespace Input
{
	void Procedure
	(HWND hwindow, UINT umessage, WPARAM wparameter, LPARAM lparameter, std::vector<Tank> & tank, HDC const& hmapdc, bool &magenta_switch)
	{
		switch (umessage)
		{
			case WM_MOUSEMOVE:
			{
				RECT Clip;
				GetClientRect(hwindow, &Clip);
				ClientToScreen(hwindow, (LPPOINT)&Clip);
				ClientToScreen(hwindow, (LPPOINT)(&Clip.right));
				ClipCursor(&Clip);
				_Mouse->x = LOWORD(lparameter);
				_Mouse->y = HIWORD(lparameter);
				return;
			}
			case WM_LBUTTONDOWN:
			{

				float x = static_cast<float>(_Mouse->x)+_CAM->pos.x;
				float y = static_cast<float>(_Mouse->y)+_CAM->pos.y;
				tank.push_back
				(
					Tank
					(
						{
							x,
							y
						},
						49,
						42
					)
				);
				tank.back().ballistics_initialize(0, 0);
				return;
			}
			case WM_RBUTTONDOWN:
			{

				unsigned x = _Mouse->x+static_cast<unsigned>(_CAM->pos.x);
				unsigned y = _Mouse->y+static_cast<unsigned>(_CAM->pos.y);

				HBRUSH hNewBrush = CreateSolidBrush(RGB(255,0,255));
				HPEN hNewPen = CreatePen(PS_SOLID, 2, 0xff00ff);
				HBITMAP hOldBmp = static_cast<HBITMAP>(SelectObject(hmapdc, hNewBrush));
				SelectObject(hmapdc, hNewPen);

				Ellipse(hmapdc, x-20, y-20, x+20, y+20);
				SelectObject(hmapdc, hOldBmp);
				DeleteObject(hNewBrush);
				DeleteObject(hNewPen);

				//if (magenta_switch)
				//{
				//	magenta_switch = false;
				//	return;
				//}
				//magenta_switch = true;
				return;
			}
			case WM_KEYDOWN: 
			{
				switch (wparameter)
				{
				case VK_LEFT:
				{
					Physics::find_nextstep(hmapdc, tank.front(), false);
					//tank.front().input_key(wparameter); 
					return; 
				}
				case VK_RIGHT:
				{
					Physics::find_nextstep(hmapdc, tank.front(), true);
					//tank.front().input_key(wparameter);
					return;
				}
					
				}
			}

			return;

		}


	}

}