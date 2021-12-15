#include<Windows.h>
namespace Input
{
	namespace
	{
		POINT player;
		int const speed =8;
		
	}
	void initplayerpos()
	{
		player.x = 400;
		player.y = 300;

	}
	POINT const playerpos()
	{
		return player;
	}

	int input()
	{
		unsigned keycode = 0;
		if ((GetAsyncKeyState(VK_LEFT) & 0x8000) and (player.x > 0))
			player.x -= speed;
		if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) and (player.x < 800))
			player.x += speed;
		if ((GetAsyncKeyState(VK_UP) & 0x8000) and (player.y > 0))
			player.y -= speed;
		if ((GetAsyncKeyState(VK_DOWN) & 0x8000) and (player.y < 600))
			player.y += speed;

		return 0;
	}
	bool enter()
	{
		if(GetAsyncKeyState(VK_RETURN) & 0x8000)
			return true;
		return false;
	}

	bool Procedure
	(HWND hwindow, UINT umessage, WPARAM wparameter, LPARAM lparameter, bool ispause)
	{
		switch (umessage)
		{
		case WM_KEYDOWN:
		{
			switch (wparameter)
			{
				case 'P':
				{
					if (!ispause)
						return true;
					return false;
				}
			}
		}
		}
		if (ispause)
			return true;
		return false;
	}
}