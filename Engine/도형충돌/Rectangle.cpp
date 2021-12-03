#include<Windows.h>
#include<vector>
#include<math.h>

namespace Rect
{
	namespace
	{
		enum Side
		{
			Top, Bottom, Left, Right
		};
		double const PI = 3.1415926;
		double const degree = PI/180;
		std::vector<POINT> rect_pos;
		std::vector<double> rect_ang;
		std::vector<double> ang_toplayer;

		float const speed = 4;
	}
	void initialize()
	{
		rect_pos.clear();
		ang_toplayer.clear();
	}

	void setrectpos(LONG& x, LONG& y)
	{
		size_t const side = rand() % 4;
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
				y = rand() % 600;
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
	void setrectang(LONG& x, LONG& y, double& angle, POINT const& player)
	{
		angle = atan2(static_cast<double>(player.y) - y,
			static_cast<double>(player.x) - x);
	}
	void push_rect(POINT const& player)
	{
		rect_pos.push_back({ 0,0 });
		rect_ang.push_back(0);
		ang_toplayer.push_back(0);

		setrectpos(rect_pos[rect_pos.size() - 1].x, rect_pos[rect_pos.size() - 1].y);
		setrectang(rect_pos[rect_pos.size() - 1].x, rect_pos[rect_pos.size() - 1].y,
			ang_toplayer[rect_pos.size() - 1], player);
	}
	void move_rect()
	{
		for (size_t i = 0; i < rect_pos.size(); i++)
		{
			rect_pos[i].x += static_cast<LONG>(speed * cos(ang_toplayer[i]));
			rect_pos[i].y += static_cast<LONG>(speed * sin(ang_toplayer[i]));
			rect_ang[i]   += degree * speed;
		}
	}
	bool const isout(POINT const& point)
	{
		if ((point.x < 0) or (point.x > 800))
			return true;
		if ((point.y < 0) or (point.y > 600))
			return true;
		return false;
	}
	void delete_rect()
	{
		for (size_t i = 0; i < rect_pos.size(); i++)
		{
			if (isout(rect_pos[i]))
			{
				rect_pos.erase(rect_pos.begin() + i);
				ang_toplayer.erase(ang_toplayer.begin() + i);
			}
		}
	}
	std::vector<POINT> const vecpoint()
	{
		return rect_pos;
	}
	std::vector<double> const vecang()
	{
		return rect_ang;
	}
	size_t getcount()
	{
		return rect_pos.size();
	}
}