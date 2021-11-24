#include<Windows.h>
#include<vector>
#pragma comment(lib, "msimg32.lib")
namespace Rendering
{
	void initialize(HWND const& hwindow);
	void update(HWND const& hwindow, int player_x, int player_y,
		std::vector<POINT> const& missilepos);
	void destroy();
}

namespace Input
{
	//void Procedure
	//(HWND hwindow, UINT umessage, WPARAM wparameter, LPARAM lparameter, POINT& player);
	void initplayerpos();
	POINT const playerpos();
	void input();
}
namespace Time
{
	void Procedure
	(HWND const , UINT const , WPARAM const , LPARAM const );
	bool const isinterval();
	bool const isregentime();
}
namespace Missile
{
	void push_missile(POINT const& player);
	void move_missile();
	void delete_missile();
	std::vector<POINT> const vecpoint();
}

namespace Engine
{


	LRESULT CALLBACK Procedure
	(HWND hwindow, UINT umessage, WPARAM wparameter, LPARAM lparameter)
	{
		switch (umessage)
		{
			case WM_CREATE:
			{
				Rendering::initialize(hwindow);
				Input::initplayerpos();
				return 0;
			}
			case WM_APP:
			{
				Time::Procedure(hwindow, umessage, wparameter, lparameter);
				
				if(Time::isregentime())
					Missile::push_missile(Input::playerpos());
				if(Time::isinterval())
				{
					Input::input();
					Missile::move_missile();
					Missile::delete_missile();
				}
				Rendering::update(hwindow, Input::playerpos().x, Input::playerpos().y,
					Missile::vecpoint());

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

				Rendering::destroy();
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