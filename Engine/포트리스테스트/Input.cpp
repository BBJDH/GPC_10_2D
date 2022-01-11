#include<Windows.h>
#include<vector>
#include"Tank.h"
namespace Input
{
	void Procedure
	(HWND hwindow, UINT umessage, WPARAM wparameter, LPARAM lparameter, std::vector<Tank> & tank, HDC const& hmapdc, bool &magenta_switch)
	{
		switch (umessage)
		{
			case WM_LBUTTONDOWN:
			{
				//obj.push_back
				//(
				//	Tank
				//	(
				//		{
				//			static_cast<float>(LOWORD(lparameter)),
				//			static_cast<float>(HIWORD(lparameter))
				//		},
				//		49,
				//		42
				//	)
				//);
				//obj.back().ballistics_initialize(0, 0);
				return;
			}
			case WM_RBUTTONDOWN:
			{
				unsigned x = LOWORD(lparameter);
				unsigned y = HIWORD(lparameter);

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
			case WM_KEYDOWN: { tank.front().input_key(wparameter); return; }

			return;

		}


	}

}