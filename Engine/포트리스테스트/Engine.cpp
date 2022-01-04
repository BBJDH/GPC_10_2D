#include<Windows.h>
#include<vector>
#include"Object.h"

#pragma comment(lib, "msimg32.lib")
namespace Rendering
{
	void initialize(HWND const& hwindow);
	void update(HWND const& hwindow, std::vector<Object> const& obj);
	BITMAP const getbitmap();
	void destroy();
	HDC getmapdc();
	HBITMAP getmapbit();
}

namespace Input
{
	void Procedure
	(HWND hwindow, UINT umessage, WPARAM wparameter, LPARAM lparameter, std::vector<Object>& obj, HDC const& hmapdc);

}
namespace Time
{
	void Procedure
	(HWND const , UINT const , WPARAM const , LPARAM const );
	float const getdelta();
}
namespace Missile
{

}
namespace Physics
{
	void Collide_objects(HWND const& hwindow, std::vector<Object>& obj, HDC const& hmapdc);
	void Move(std::vector<Object>& obj, float const delta);
}

namespace Engine
{
	bool isalive, ispaused;
	float record_time;

	std::vector<Object> tank;
	std::vector<Object> missile;
	
	LRESULT CALLBACK Procedure
	(HWND hwindow, UINT umessage, WPARAM wparameter, LPARAM lparameter)
	{
		switch (umessage)
		{
			case WM_CREATE:
			{
				Rendering::initialize(hwindow);

				
				return 0;
			}
			case WM_APP:
			{
				Time::Procedure(hwindow, umessage, wparameter, lparameter);
				Rendering::update(hwindow, tank);
				Physics::Move(tank,Time::getdelta());
				Physics::Collide_objects(hwindow , tank, Rendering::getmapdc());
				return 0;
			}
			case WM_MOUSEWHEEL:   case WM_MOUSEHWHEEL: case WM_MOUSEMOVE:
			case WM_SYSKEYDOWN:   case WM_LBUTTONDOWN: case WM_LBUTTONUP:
			case WM_SYSKEYUP:     case WM_RBUTTONDOWN: case WM_RBUTTONUP:
			case WM_KEYDOWN:      case WM_MBUTTONDOWN: case WM_MBUTTONUP:
			case WM_KEYUP:        case WM_XBUTTONDOWN: case WM_XBUTTONUP:
			{
				Input::Procedure
				(hwindow, umessage, wparameter, lparameter, tank, Rendering::getmapdc());
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