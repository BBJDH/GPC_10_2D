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
	(HWND hwindow, UINT umessage, WPARAM wparameter, LPARAM lparameter, std::vector<Object> & obj, HDC const& hmapdc)
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
						24,
						21
					)
				);
				obj.back().ballistics_initialize(0, 0);
				return;
			}
			case WM_RBUTTONDOWN:
			{
				unsigned x = LOWORD(lparameter);
				unsigned y = HIWORD(lparameter);

				HBRUSH hNewBrush = CreateSolidBrush(RGB(0,0,0));
				SelectObject(hmapdc, hNewBrush);

				Ellipse(hmapdc, x-20, y-20, x+20, y+20);

				return;
			}
			return;

		}


	}

}