#include<Windows.h>
#include<vector>
#pragma comment(lib, "msimg32.lib")
namespace Rendering
{
	void initialize(HWND const& hwindow);
	void update(HWND const& hwindow, int const player_x, int const player_y,
		std::vector<POINT> const& missilepos, float const time, bool const is_printover);
	//void gameover(HWND const& hwindow, int const player_x, int const player_y,
	//	std::vector<POINT> const& missilepos);
	void destroy();
}

namespace Input
{
	//void Procedure
	//(HWND hwindow, UINT umessage, WPARAM wparameter, LPARAM lparameter, POINT& player);
	void initplayerpos();
	POINT const playerpos();
	void input();
	bool enter();
}
namespace Time
{
	void Procedure
	(HWND const , UINT const , WPARAM const , LPARAM const );
	bool isinterval();
	bool isregentime();
	bool isprinttime();
	float getdelta();
}
namespace Missile
{
	void initialize();
	void push_missile(POINT const& player);
	void move_missile();
	void delete_missile();
	std::vector<POINT> const vecpoint();
	size_t getcount();
}
namespace Collision
{
	bool Procedure
	(HWND   const hWindow, UINT   const uMessage, WPARAM const wParameter,
		LPARAM const lParameter, std::vector<POINT> const& missile, POINT const& player);
	bool iscrashed(std::vector<POINT> const& missile,
		POINT const& player);
}

namespace Engine
{
	bool isalive;
	float record_time;
	LRESULT CALLBACK Procedure
	(HWND hwindow, UINT umessage, WPARAM wparameter, LPARAM lparameter)
	{
		switch (umessage)
		{
			case WM_CREATE:
			{
				Rendering::initialize(hwindow);
				Input::initplayerpos();
				isalive =true;
				record_time=0;
				return 0;
			}
			case WM_APP:
			{
				Time::Procedure(hwindow, umessage, wparameter, lparameter);
				if(isalive)
				{
					
					if(Time::isregentime())
						Missile::push_missile(Input::playerpos());
					if(Time::isinterval())
					{
						Input::input();
						Missile::move_missile();
						Missile::delete_missile();
						isalive = !Collision::iscrashed(Missile::vecpoint(),Input::playerpos());
					}
					record_time+=Time::getdelta();
					Rendering::update(hwindow, Input::playerpos().x, Input::playerpos().y,
						Missile::vecpoint(), record_time, false);
				}
				else
				{
					if(Time::isprinttime())
						Rendering::update(hwindow, Input::playerpos().x, Input::playerpos().y,
							Missile::vecpoint(),record_time,true);
					else
						Rendering::update(hwindow, Input::playerpos().x, Input::playerpos().y,
							Missile::vecpoint(), record_time, false);
					if (Input::enter())
					{
						Missile::initialize();
						Input::initplayerpos();
						isalive = true;
						record_time = 0;
					}

				}
	

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