#include<Windows.h>
#pragma comment(lib, "msimg32.lib")
namespace Rendering
{
void update_player(HWND const& hwindow, HBITMAP const& hfighterbit,
	BITMAP const& fighter, HBITMAP const& hmapbit, int player_x, int player_y);
}

namespace Input
{
	void Procedure
	(HWND hwindow, UINT umessage, WPARAM wparameter, LPARAM lparameter, POINT& player);
	void input(POINT &player);
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
				Time::Procedure(hwindow, umessage, wparameter, lparameter);
				Input::input(player_pos);
				Rendering::update_player(hwindow, hfighterbit, fighter, hmapbit, player_pos.x, player_pos.y);

				return 0;
			}
			//case WM_MOUSEWHEEL:   case WM_MOUSEHWHEEL: case WM_MOUSEMOVE:
			//case WM_SYSKEYDOWN:   case WM_LBUTTONDOWN: case WM_LBUTTONUP:
			//case WM_SYSKEYUP:     case WM_RBUTTONDOWN: case WM_RBUTTONUP:
			//case WM_KEYDOWN:      case WM_MBUTTONDOWN: case WM_MBUTTONUP:
			//case WM_KEYUP:        case WM_XBUTTONDOWN: case WM_XBUTTONUP:
			//{
			//	Input::Procedure
			//	(hwindow, umessage, wparameter, lparameter, player_pos);
			//	return 0;
			//}

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


//(2,0) - (8,4) = (6,4) =>(3,2)
//0001000000
// 000000000
// 000000000
// 000000001
// 000000000
//