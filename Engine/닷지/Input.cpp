#include<Windows.h>

namespace Input
{
	void Procedure
	(HWND hwindow, UINT umessage, WPARAM wparameter, LPARAM lparameter,POINT & player)
	{
		switch (umessage)
		{
		
			case WM_KEYDOWN:
			{
				switch (wparameter)
				{
					case VK_LEFT:
					{
						player.x -= 8;
						return ;
					}
					case VK_RIGHT:
					{
						player.x += 8;
						return ;
					}
					case VK_UP:
					{
						player.y -= 8;
						return ;
					}
					case VK_DOWN:
					{
						player.y += 8;
						return ;
					}

				}
			}
		}
	}
}