#include<Windows.h>
#include<vector>
#include"Object.h"

#pragma comment(lib, "msimg32.lib")
namespace Rendering
{
	void initialize(HWND const& hwindow);
	void update(HWND const& hwindow, float const player_x, float const player_y,
		 float const time);

	void destroy();
}

namespace Input
{
	bool Procedure
	(HWND hwindow, UINT umessage, WPARAM wparameter, LPARAM lparameter, bool ispause);


}
namespace Time
{
	void Procedure
	(HWND const , UINT const , WPARAM const , LPARAM const );
	float getdelta();
}
namespace Missile
{

}
namespace Collision
{

}

namespace Engine
{
	bool isalive, ispaused;
	float record_time;
	Object tank = Object();
	LRESULT CALLBACK Procedure
	(HWND hwindow, UINT umessage, WPARAM wparameter, LPARAM lparameter)
	{
		switch (umessage)
		{
			case WM_CREATE:
			{
				Rendering::initialize(hwindow);
				tank.ballistics_initialize(1, 100);
				
				return 0;
			}
			case WM_APP:
			{
				Rendering::update(hwindow, tank.getpos().x, tank.getpos().y, tank.gettime());
				Time::Procedure(hwindow, umessage, wparameter, lparameter);
				tank.ballistics_equation(Time::getdelta());
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
			case WM_KEYDOWN:
			{

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


//(2,0) - (8,4) = (6,4) =>(3,2)
//0001000000
// 000000000
// 000000000
// 000000001
// 000000000
//