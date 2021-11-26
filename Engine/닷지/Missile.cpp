#include<Windows.h>
#include<vector>
#include<math.h>

namespace Missile
{
	namespace
	{
		enum Side
		{
			Top,Bottom,Left,Right
		};
		//double PI = 3.1415926;

		std::vector<POINT> missle_pos;
		std::vector<double> missile_ang;

		float const speed = 8;
	}

	void setmissilepos(LONG & x, LONG & y)
	{
		size_t const side = rand()%4;
		switch (side)
		{
			case Top: //È­¸é À§
			{
				x = rand() % 800;
				y = 0;
				return;
			}
			case Bottom:
			{
				x = rand() % 800;
				y = 600;
				return;

			}
			case Left:
			{
				x = 0;
				y = rand() %600;
				return;

			}
			case Right:
			{
				x = 800;
				y = rand() % 600;
				return;

			}
		}
	}
	void setmissileang(LONG & x, LONG & y, double &angle, POINT const& player)
	{
		angle = atan2(player.y-y,
			player.x-x);
	}
	void push_missile(POINT const& player)
	{
		missle_pos.push_back({0,0});
		missile_ang.push_back(0);

		setmissilepos(missle_pos[missle_pos.size()-1].x,missle_pos[missle_pos.size() - 1].y);
		setmissileang(missle_pos[missle_pos.size() - 1].x, missle_pos[missle_pos.size() - 1].y,
			missile_ang[missle_pos.size() - 1], player);
	}
	void move_missile()
	{
		for (size_t i = 0; i < missle_pos.size(); i++)
		{
			missle_pos[i].x += static_cast<LONG>(speed * cos(missile_ang[i]));
			missle_pos[i].y += static_cast<LONG>(speed * sin(missile_ang[i]));
		}
	}
	bool const isout(POINT const& point)
	{
		if((point.x<0) or (point.x>800))
			return true;
		if((point.y<0) or (point.y>600))
			return true;
		return false;
	}
	void delete_missile()
	{

		for (size_t i = 0; i < missle_pos.size(); i++)
		{
			if(isout(missle_pos[i]))
			{
				missle_pos.erase(missle_pos.begin() + i);
				missile_ang.erase(missile_ang.begin()+i);
			}
		}

	}
	std::vector<POINT> const vecpoint()
	{
		return missle_pos;
	}
	size_t getcount()
	{
		return missle_pos.size();
	}

}