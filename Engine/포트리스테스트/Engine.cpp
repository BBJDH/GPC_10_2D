#include"stdafx.h"


#pragma comment(lib, "msimg32.lib")

namespace Rendering
{
	void initialize(HWND const& hwindow);
	void update(HWND const& hwindow, std::vector<Tank> const& obj, bool const magenta_switch);
	void destroy();
	HDC getmapdc();
	HBITMAP getmapbit();
}

namespace Input
{
	void Procedure
	(HWND hwindow, UINT umessage, WPARAM wparameter, LPARAM lparameter, 
		std::vector<Tank> & tank,std::vector<Missile> & missile, HDC const& hmapdc, bool &magenta_switch);
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
	std::vector<Missile> missile;
	Random rand_turn;

	LRESULT CALLBACK Procedure
	(HWND hwindow, UINT umessage, WPARAM wparameter, LPARAM lparameter)
	{
		switch (umessage)
		{
			case WM_CREATE:
			{
				srand(static_cast<unsigned>(time(NULL)));
				Random r(10,MAPSIZE_W-10,PLAYERS);
				Rendering::initialize(hwindow);
				for (unsigned i = 0; i < PLAYERS; i++)
				{
					tank.push_back(Tank({ static_cast<float>(r.GetResult(i)),0 }, 49, 42));
					tank.back().ballistics_initialize(0, 0);
				}
				magenta_switch = false;
				
				return 0;
			}

			case WM_APP:
			{
				Time::Procedure(hwindow, umessage, wparameter, lparameter);//�ð����
				_Turn->checkturn(tank,missile);	//��üũ�� ������ �ο�
				_CAM->move(_Mouse->getpos()); //���콺 ��ġ�� ���� ī�޶� �̵�
				Physics::ballistics(tank,Time::getdelta()); //���ϰ� ���� ��ũ�� ������ǥ ��� 
				Physics::Collide_objects(tank, Rendering::getmapdc());	//������ ��ũ �浹�˻�
				Rendering::update(hwindow,tank,/*true*/ magenta_switch);	//�׸���
				return 0;
			}
			case WM_MOUSEWHEEL:   case WM_MOUSEHWHEEL: case WM_MOUSEMOVE:
			case WM_SYSKEYDOWN:   case WM_LBUTTONDOWN: case WM_LBUTTONUP:
			case WM_SYSKEYUP:     case WM_RBUTTONDOWN: case WM_RBUTTONUP:
			case WM_KEYDOWN:      case WM_MBUTTONDOWN: case WM_MBUTTONUP:
			case WM_KEYUP:        case WM_XBUTTONDOWN: case WM_XBUTTONUP:
			{
				Input::Procedure
				(hwindow, umessage, wparameter, lparameter, tank,missile, Rendering::getmapdc(), magenta_switch);
				return 0;
			}

			case WM_DESTROY:
			{
				rand_turn.~Random();
				Rendering::destroy();
				_CAM->release_singleton();
				_Mouse->release_singleton();
				ExitProcess(0);
				return 0;
			}
			default:
				return DefWindowProc(hwindow,umessage,wparameter,lparameter);
		}
	}
}

