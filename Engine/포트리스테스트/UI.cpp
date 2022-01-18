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
		if (tank.is_myturn()and !tank.is_falling())
		{
			unsigned	   stepx = static_cast<unsigned>(tank.getpos().x - 1); //�⺻ �����϶� ������ ��
			unsigned const stepy = static_cast<unsigned>(tank.getpos().y+tank.getheight()/2 - 3); 
			if (isright)
				stepx = static_cast<unsigned>(tank.getpos().x+1);

			//����/������ �ٷξ� ���� 3��° ������ �˻�
			//���� ����°������ �浹�̸� �̵��Ұ�
			//���� �Ʒ� �ι�°������ �浹������ ã�� �ű�
			//�浹������ �ϳ��� ���ٸ� ���������� ��ĭ�̵� �� ����
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
					tank.stop_move(Physics::calc_landing_angle(stepx, i, hmapdc));
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
		if (tank.is_myturn()and!tank.is_falling())
		{
			if (keyon)
				tank.plus_power();
			else
			{
				//�̻��� ����
				float const angle = -tank.getimage_angle() / Radian + tank.getangle_min() + tank.getangle();
				//60�й����� ����
				double cosval = cos(angle*Radian);
				double sinval = sin(angle*Radian); 
				int min_x = static_cast<int>(FIRE_MIN_Length * cosval );
				int min_y = static_cast<int>(FIRE_MIN_Length * sinval ); 

				missile.push_back(Missile({ tank.getpos().x+min_x,tank.getpos().y -min_y}, 31, 33));
				missile.back().ballistics_initialize(
					angle,
					static_cast<float const>(tank.getpower() * UI_POWER_MUL));
				tank.setmyturn(false);
				missile.back().setmyturn(true);
			}
		}

	}
}