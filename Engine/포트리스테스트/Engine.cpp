#include<Windows.h>
#include<vector>
#include"Object.h"
#include"Tank.h"
#pragma comment(lib, "msimg32.lib")

namespace Rendering
{
	void initialize(HWND const& hwindow);
	void update(HWND const& hwindow, std::vector<Tank> const& obj, bool const magenta_switch);
	BITMAP const getbitmap();
	void destroy();
	HDC getmapdc();
	HBITMAP getmapbit();
}

namespace Input
{
	void Procedure
	(HWND hwindow, UINT umessage, WPARAM wparameter, LPARAM lparameter, std::vector<Tank>& obj, HDC const& hmapdc, bool& magenta_switch);
}
namespace Time
{
	void Procedure
	(HWND const , UINT const , WPARAM const , LPARAM const );
	float const getdelta();
}

namespace Physics
{
	void Collide_objects(std::vector<Tank>& obj, HDC const& hmapdc);
	void ballistics(std::vector<Tank>& obj, float const delta);
}

namespace Engine
{
	bool magenta_switch;

	std::vector<Tank> tank;
	std::vector<Object> obj;
	
	LRESULT CALLBACK Procedure
	(HWND hwindow, UINT umessage, WPARAM wparameter, LPARAM lparameter)
	{
		switch (umessage)
		{
			case WM_CREATE:
			{
				Rendering::initialize(hwindow);

				tank.push_back(Tank({ 100,100 }, 49, 42));
				tank.back().ballistics_initialize(0, 0);

				magenta_switch = false;
				return 0;
			}
			case WM_APP:
			{
				Time::Procedure(hwindow, umessage, wparameter, lparameter);
				Rendering::update(hwindow,tank,/*true*/magenta_switch);
				Physics::ballistics(tank,Time::getdelta());
				Physics::Collide_objects(tank, Rendering::getmapdc());
				return 0;
			}
			case WM_MOUSEWHEEL:   case WM_MOUSEHWHEEL: case WM_MOUSEMOVE:
			case WM_SYSKEYDOWN:   case WM_LBUTTONDOWN: case WM_LBUTTONUP:
			case WM_SYSKEYUP:     case WM_RBUTTONDOWN: case WM_RBUTTONUP:
			case WM_KEYDOWN:      case WM_MBUTTONDOWN: case WM_MBUTTONUP:
			case WM_KEYUP:        case WM_XBUTTONDOWN: case WM_XBUTTONUP:
			{
				Input::Procedure
				(hwindow, umessage, wparameter, lparameter, tank, Rendering::getmapdc(), magenta_switch);
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