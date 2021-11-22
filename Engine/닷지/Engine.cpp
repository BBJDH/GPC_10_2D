#include<Windows.h>
#pragma comment(lib, "msimg32.lib")
void update_player(HWND const& hwindow, HBITMAP const& hfighterbit,
	BITMAP const& fighter, HBITMAP const& hmapbit, int player_x, int player_y);

namespace Engine
{
	LRESULT CALLBACK Procedure
	(HWND hwindow, UINT umessage, WPARAM wparameter, LPARAM lparameter)
	{

		static int pos_x = 350;
		static int pos_y = 300;
		static HBITMAP hmapbit, hfighterbit,hmissilebit;
		static BITMAP fighter, missile;


		update_player(hwindow,hfighterbit,fighter,hmapbit,pos_x,pos_y);

		switch (umessage)
		{
			case WM_CREATE:
			{
				HDC hdc = GetDC(hwindow);
				hmapbit = CreateCompatibleBitmap(hdc,800,600);
				hfighterbit = CreateCompatibleBitmap(hdc,50,50);
				hmapbit =  static_cast<HBITMAP>(LoadImage
				(
					NULL,
					TEXT("./소스파일/Stars-background/starfield_alpha.bmp"),
					IMAGE_BITMAP,
					0,
					0,
					LR_LOADFROMFILE|LR_DEFAULTSIZE
				));
				hfighterbit = static_cast<HBITMAP>(LoadImage
				(
					NULL,
					TEXT("./소스파일/spaceshipset32x32/player_ship.bmp"),
					IMAGE_BITMAP,
					0,
					0,
					LR_LOADFROMFILE | LR_DEFAULTSIZE
				));
				GetObject(hfighterbit,sizeof(BITMAP),&fighter);
				hmissilebit = static_cast<HBITMAP>(LoadImage
				(
					NULL,
					TEXT("./소스파일/missile.bmp"),
					IMAGE_BITMAP,
					0,
					0,
					LR_LOADFROMFILE | LR_DEFAULTSIZE
				));
				GetObject(hmissilebit, sizeof(BITMAP), &missile);


				//BitBlt(hdc,0,0,800,600,hmemdc,0,0,SRCCOPY);

				//SelectObject(hdc,oldbit);
				//DeleteDC(hmemdc);
				ReleaseDC(hwindow,hdc);
				return 0;
			}
			case WM_APP:
			{
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hwindow,&ps);
				HDC hmemdc = CreateCompatibleDC(hdc);

				HBITMAP oldbit = 
					static_cast<HBITMAP>(SelectObject(hmemdc,hmapbit));
				BitBlt(hdc,0,0,800,600,hmemdc,0,0,SRCCOPY);

				SelectObject(hmemdc, hfighterbit);
				//BitBlt(hdc, pos_x, pos_y, 50, 50, hmemdc, 0, 0, SRCCOPY); //투명화안됨
				TransparentBlt(hdc,pos_x,pos_y,fighter.bmWidth,fighter.bmHeight,hmemdc,0,0, fighter.bmWidth, fighter.bmHeight,RGB(255,255,255));
				
				//SelectObject(hmemdc, hmissilebit);
				//TransparentBlt(hdc, 150, 150, missile.bmWidth, missile.bmHeight, hmemdc, 0, 0, missile.bmWidth, missile.bmHeight, RGB(255, 255, 255));


				SelectObject(hmemdc,oldbit);

				DeleteDC(hmemdc);
				EndPaint(hwindow,&ps);

				return 0;
			}
			case WM_KEYDOWN:
			{
				switch (wparameter)
				{
					case VK_LEFT:
					{
						pos_x -= 8;
						return 0;
					}
					case VK_RIGHT:
					{
						pos_x += 8;
						return 0;
					}
					case VK_UP:
					{
						pos_y -= 8;
						return 0;
					}
					case VK_DOWN:
					{
						pos_y += 8;
						return 0;
					}
					
				}
				return 0;
			}

			case WM_DESTROY:
			{
				ExitProcess(0);
				return 0;
			}
			default:
				return DefWindowProc(hwindow,umessage,wparameter,lparameter);
		}
	}
}

void update_player(HWND const& hwindow, HBITMAP const& hfighterbit,
	BITMAP const& fighter, HBITMAP const& hmapbit,int player_x,int player_y) 
{
	HDC hdc = GetDC(hwindow);
	HDC hmemdc = CreateCompatibleDC(hdc);
	HBITMAP oldbit = static_cast<HBITMAP>(SelectObject(hmemdc,hmapbit));
	BitBlt(hdc,0,0,800,600,hmemdc,0,0,SRCCOPY);
	SelectObject(hmemdc,hfighterbit);

	TransparentBlt(hdc,player_x,player_y,fighter.bmWidth,fighter.bmHeight,
		hmemdc,0,0, fighter.bmWidth, fighter.bmHeight,RGB(255,255,255));
	SelectObject(hmemdc,oldbit);
	DeleteDC(hmemdc);
	ReleaseDC(hwindow,hdc);


}

//(2,0) - (8,4) = (6,4) =>(3,2)
//0001000000
// 000000000
// 000000000
// 000000001
// 000000000
//