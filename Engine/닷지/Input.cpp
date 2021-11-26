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

	void input()
	{
		
		if ((GetAsyncKeyState(VK_LEFT) & 0x8000) and (player.x > 0))
			player.x -= speed;
		if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) and (player.x < 800))
			player.x += speed;
		if ((GetAsyncKeyState(VK_UP) & 0x8000) and (player.y > 0))
			player.y -= speed;
		if ((GetAsyncKeyState(VK_DOWN) & 0x8000) and (player.y < 600))
			player.y += speed;
	}
	bool enter()
	{
		if(GetAsyncKeyState(VK_RETURN) & 0x8000)
			return true;
		return false;
	}
	//void Procedure
	//(HWND hwindow, UINT umessage, WPARAM wparameter, LPARAM lparameter,POINT & player)
	//{
	//	switch (umessage)
	//	{
	//		case WM_KEYDOWN:
	//		{
	//			switch (wparameter)
	//			{
	//				case VK_LEFT:
	//				{
	//					player.x -= 8;
	//					return ;
	//				}
	//				case VK_RIGHT:
	//				{
	//					player.x += 8;
	//					return ;
	//				}
	//				case VK_UP:
	//				{
	//					player.y -= 8;
	//					return ;
	//				}
	//				case VK_DOWN:
	//				{
	//					player.y += 8;
	//					return ;
	//				}
	//			}
	//		}
	//	}
	//}

}