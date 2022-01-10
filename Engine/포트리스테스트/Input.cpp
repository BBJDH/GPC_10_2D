#include<Windows.h>
#include<vector>
#include"Object.h"
namespace Input
{
	namespace
	{
		int const speed =8;
	}

	void Procedure
	(HWND hwindow, UINT umessage, WPARAM wparameter, LPARAM lparameter, std::vector<Object> & obj, HDC const& hmapdc, bool &magenta_switch)
	{
		switch (umessage)
		{
			case WM_LBUTTONDOWN:
			{
				obj.push_back
				(
					Object
					(
						{
							static_cast<float>(LOWORD(lparameter)),
							static_cast<float>(HIWORD(lparameter))
						},
						49,
						42
					)
				);
				obj.back().ballistics_initialize(0, 0);
				return;
			}
			case WM_RBUTTONDOWN:
			{
				unsigned x = LOWORD(lparameter);
				unsigned y = HIWORD(lparameter);

				HBRUSH hNewBrush = CreateSolidBrush(RGB(255,0,255));
				HPEN hNewPen = CreatePen(PS_SOLID, 2, 0xff00ff);
				SelectObject(hmapdc, hNewBrush);
				SelectObject(hmapdc, hNewPen);

				Ellipse(hmapdc, x-20, y-20, x+20, y+20);
				//if (magenta_switch)
				//{
				//	magenta_switch = false;
				//	return;
				//}
				//magenta_switch = true;
				return;
			}

			return;

		}


	}

}