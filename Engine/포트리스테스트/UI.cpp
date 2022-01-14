#include"stdafx.h"

namespace Physics
{
	bool Collide(HDC const hdc,int const x, int const y);
	float const calc_landing_angle(unsigned const start_x, unsigned const selected_y, HDC const& hmapdc);

}

namespace UI
{
	void find_nextstep(HDC const& hmapdc,  Tank & tank,  bool const isright)
	{
		if (tank.is_myturn())
		{
			unsigned	   stepx = static_cast<unsigned>(tank.getpos().x - 1); //기본 왼쪽일때 시작할 점
			unsigned const stepy = static_cast<unsigned>(tank.getpos().y+tank.getheight()/2 - 3); 
			if (isright)
				stepx = static_cast<unsigned>(tank.getpos().x+1);

			//왼쪽/오른쪽 바로앞 위로 3번째 점부터 검사
			//위에 세번째점에서 충돌이면 이동불가
			//이후 아래 두번째점까지 충돌지점을 찾아 옮김
			//충돌지점이 하나도 없다면 오른쪽으로 한칸이동 후 낙하
			for (unsigned i = stepy; i < stepy+7; i++)
			{
				if ( i == stepy)
				{
					if (Physics::Collide(hmapdc, stepx, i))
					{
						tank.setstate(Tank::State::Stop_right);
						return;
					}
				}
				if (Physics::Collide(hmapdc, stepx, i))
				{
					tank.moveto({ static_cast<float>(stepx) ,static_cast<float>(i-tank.getheight()/2)});
					tank.stop_move(-Physics::calc_landing_angle(stepx, i, hmapdc) / Radian);
					return;
				}
			}
			tank.moveto({ static_cast<float>(stepx) ,tank.getpos().y });
			tank.ballistics_initialize(0,0);
			return;
		}
	}
	void fire(Tank& tank, std::vector<Missile>& missile, bool const keyon)
	{
		if(keyon)
			tank.plus_power();
		else
		{
			//미사일 생성
			tank.setmyturn(false);
		}

	}
}