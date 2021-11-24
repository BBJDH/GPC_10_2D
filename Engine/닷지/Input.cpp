#include<Windows.h>
namespace Time{float const getdelta();}
namespace Input
{
	namespace
	{
		float interval =0;
		float const speed = 0.03f;
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
	bool const isinputtime()
	{
		interval += Time::getdelta();
		if(interval>speed)
		{
			interval =0;
			return true;
		}
		return false;
	}
	void input(POINT& player)
	{
		if(isinputtime())
		{
			if((GetAsyncKeyState(VK_LEFT) & 0x8000)and(player.x>0))
				player.x -= 8;
			if((GetAsyncKeyState(VK_RIGHT) & 0x8000) and (player.x < 760))
				player.x += 8;
			if((GetAsyncKeyState(VK_UP) & 0x8000) and (player.y > 0))
				player.y -= 8;
			if((GetAsyncKeyState(VK_DOWN) & 0x8000) and (player.y < 545))
				player.y += 8;
		}
	}
}