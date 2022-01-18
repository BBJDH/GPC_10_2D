#include"stdafx.h"

namespace UI
{
	void find_nextstep(HDC const& hmapdc, Tank& tank, bool const isright);
	void fire(Tank& tank, std::vector<Missile>& missile, bool const keyon);
}

namespace Input
{
	void Procedure
	(HWND hwindow, UINT umessage, WPARAM wparameter, LPARAM lparameter, 
		std::vector<Tank> & tank,std::vector<Missile> & missile, HDC const& hmapdc, bool &magenta_switch)
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

				//float x = static_cast<float>(_Mouse->x)+_CAM->pos.x;
				//float y = static_cast<float>(_Mouse->y)+_CAM->pos.y;
				//tank.push_back
				//(
				//	Tank
				//	(
				//		{
				//			x,
				//			y
				//		},
				//		49,
				//		42
				//	)
				//);
				//tank.back().ballistics_initialize(0, 0);
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
					//UI::find_nextstep(hmapdc, tank[_Turn->whosturn()], false);
					//tank.front().input_key(wparameter); 
					return; 
				}
				case VK_RIGHT:
				{
					//UI::find_nextstep(hmapdc, tank[_Turn->whosturn()], true);
					//tank.front().input_key(wparameter);
					return;
				}
				case VK_UP:
				{
					//if(tank[_Turn->whosturn()].is_myturn())
					//	tank[_Turn->whosturn()].plus_angle(1);
					return;
				}
				case VK_DOWN:
				{
					//if(tank[_Turn->whosturn()].is_myturn())
					//	tank[_Turn->whosturn()].plus_angle(-1);
					return;
				}
				case VK_SPACE:
				{
					//UI::fire(tank[_Turn->whosturn()],missile,true);
					return;
				}
					
				}
			}
			case WM_KEYUP: 
			{
				switch (wparameter)
				{
				
				case VK_SPACE:
				{
					UI::fire(tank[_Turn->whosturn()],missile,false);

					return;
				}

				}
			}

			return;

		}


	}
	void input(std::vector<Tank> & tank,std::vector<Missile> & missile, HDC const& hmapdc, bool &magenta_switch)
	{
		unsigned keycode = 0;
		if ((GetAsyncKeyState(VK_LEFT) & 0x8000))
			UI::find_nextstep(hmapdc, tank[_Turn->whosturn()], false);
		if ((GetAsyncKeyState(VK_RIGHT) & 0x8000))
			UI::find_nextstep(hmapdc, tank[_Turn->whosturn()], true);
		if ((GetAsyncKeyState(VK_UP) & 0x8000))
		{
			if(tank[_Turn->whosturn()].is_myturn() and !tank[_Turn->whosturn()].is_dead())
				tank[_Turn->whosturn()].plus_angle(1);
		}
		if ((GetAsyncKeyState(VK_DOWN) & 0x8000))
		{
			if(tank[_Turn->whosturn()].is_myturn()and !tank[_Turn->whosturn()].is_dead())
				tank[_Turn->whosturn()].plus_angle(-1);
		}
		if ((GetAsyncKeyState(VK_SPACE) & 0x8000))
			UI::fire(tank[_Turn->whosturn()],missile,true);

		return ;
	}

}