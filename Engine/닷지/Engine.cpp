#include<Windows.h>
#pragma comment(lib, "msimg32.lib")
void update_player(HWND const& hwindow, HBITMAP const& hfighterbit,
	BITMAP const& fighter, HBITMAP const& hmapbit, int player_x, int player_y);

namespace Input
{
	void Procedure
	(HWND hwindow, UINT umessage, WPARAM wparameter, LPARAM lparameter, POINT& player);
}
namespace Time
{
	void Procedure
	(HWND   const hWindow, UINT   const uMessage, WPARAM const wParameter, LPARAM const lParameter);
}

namespace Engine
{
	namespace
	{
		POINT player_pos;
		HBITMAP hmapbit, hfighterbit, hmissilebit;
		BITMAP fighter, missile;
	}

	LRESULT CALLBACK Procedure
	(HWND hwindow, UINT umessage, WPARAM wparameter, LPARAM lparameter)
	{
		



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
					TEXT("./家胶颇老/Stars-background/starfield_alpha.bmp"),
					IMAGE_BITMAP,
					0,
					0,
					LR_LOADFROMFILE|LR_DEFAULTSIZE
				));
				hfighterbit = static_cast<HBITMAP>(LoadImage
				(
					NULL,
					TEXT("./家胶颇老/spaceshipset32x32/player_ship.bmp"),
					IMAGE_BITMAP,
					0,
					0,
					LR_LOADFROMFILE | LR_DEFAULTSIZE
				));
				GetObject(hfighterbit,sizeof(BITMAP),&fighter);
				hmissilebit = static_cast<HBITMAP>(LoadImage
				(
					NULL,
					TEXT("./家胶颇老/missile.bmp"),
					IMAGE_BITMAP,
					0,
					0,
					LR_LOADFROMFILE | LR_DEFAULTSIZE
				));
				GetObject(hmissilebit, sizeof(BITMAP), &missile);

				player_pos.x =350;
				player_pos.y =300;

				ReleaseDC(hwindow,hdc);
				return 0;
			}
			case WM_APP:
			{
				update_player(hwindow, hfighterbit, fighter, hmapbit, player_pos.x, player_pos.y);
				Time::Procedure(hwindow, umessage, wparameter, lparameter);

				return 0;
			}
			case WM_MOUSEWHEEL:   case WM_MOUSEHWHEEL: case WM_MOUSEMOVE:
			case WM_SYSKEYDOWN:   case WM_LBUTTONDOWN: case WM_LBUTTONUP:
			case WM_SYSKEYUP:     case WM_RBUTTONDOWN: case WM_RBUTTONUP:
			case WM_KEYDOWN:      case WM_MBUTTONDOWN: case WM_MBUTTONUP:
			case WM_KEYUP:        case WM_XBUTTONDOWN: case WM_XBUTTONUP:
			{
				Input::Procedure
				(hwindow, umessage, wparameter, lparameter, player_pos);
				return 0;
			}

			case WM_DESTROY:
			{
				DeleteObject(hmapbit);
				DeleteObject(hfighterbit);
				DeleteObject(hmissilebit);

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
	HDC hvirtualdc = CreateCompatibleDC(hdc);
	HDC hbufferdc = CreateCompatibleDC(hdc);
	HBITMAP hvirtualbit = CreateCompatibleBitmap(hdc,800,600);
	SelectObject(hvirtualdc, hvirtualbit);

	HBITMAP oldbit = static_cast<HBITMAP>(SelectObject(hbufferdc,hmapbit));
	BitBlt(hvirtualdc,0,0,800,600, hbufferdc,0,0,SRCCOPY);
	SelectObject(hbufferdc,hfighterbit);

	TransparentBlt(hvirtualdc,player_x,player_y,fighter.bmWidth,fighter.bmHeight,
		hbufferdc,0,0, fighter.bmWidth, fighter.bmHeight,RGB(255,255,255));
	BitBlt(hdc, 0, 0, 800, 600, hvirtualdc, 0, 0, SRCCOPY);
	SelectObject(hbufferdc,oldbit);
	DeleteDC(hbufferdc);
	DeleteDC(hvirtualdc);
	DeleteObject(hvirtualbit);
	ReleaseDC(hwindow,hdc);


}

//(2,0) - (8,4) = (6,4) =>(3,2)
//0001000000
// 000000000
// 000000000
// 000000001
// 000000000
//