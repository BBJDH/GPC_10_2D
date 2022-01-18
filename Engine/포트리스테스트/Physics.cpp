#include"stdafx.h"

struct tyCircle final
{
	float Diameter = { 0 };
	vector<2> Location = { 0,0 };
};
struct  tyRectangle
{
	vector<2> Length = { 0,0 };
	float     Angle = { 0 };
	vector<2> Location = { 0,0 };
};
struct tyPoint final
{
	vector<2> Location = { 0,0 };
};

namespace Physics
{
	//영역 지정
	float distance(long const dest_x, long const dest_y, long const src_x, long const src_y)
	{
		return static_cast<float>(sqrt(pow(static_cast<double>(dest_x)- static_cast<double>(src_x),2)+pow(static_cast<double>(dest_y)- static_cast<double>(src_y),2)));
	}

	bool iscrashed(std::vector<POINT> const& missile,
		POINT const & player)
	{
		for (size_t i = 0; i < missile.size(); i++)
		{
			if(distance(player.x,player.y,missile[i].x,missile[i].y)<12)
				return true;
		}
		return false;
	}
	bool Procedure
	(HWND   const hWindow, UINT   const uMessage, WPARAM const wParameter, 
		LPARAM const lParameter, std::vector<POINT> const& missile, POINT const& player)
	{
		switch (uMessage)
		{
			case WM_APP:
			{
				if(iscrashed(missile, player))
				{
					MessageBox(hWindow, "Crashed!", "Crashed!", MB_OK);
					return true;
				}
			}
		}
				return false;
	}
	bool Collide(tyPoint const& point, tyCircle const& circle)
	{
		return length(point.Location - circle.Location) <= (circle.Diameter / 2);
	}
	bool Collide(tyPoint const& point, tyRectangle const& rect)
	{
		if (rect.Angle != 0)
		{
			return false;
		}
		else
		{
			vector<2> const distance = point.Location - rect.Location;
			return abs(distance[0]) <= rect.Length[0] / 2 and abs(distance[1]) <= rect.Length[1] / 2;
		}


	}
	bool Collide(tyRectangle const& rect, tyCircle const& circle)
	{
		//사각형의 너비범위 혹은 높이 범위 안에 들어왔다면, 사각형너비 높이에 r만큼 더한 사각형과 원의 중점과의 충돌 판정
		//원의 중점이 사각형 중점의 x, y 좌표보다 작다면 왼쪽위 꼭지점과 원의 충돌 판정
		//원의 중점이 사각형 중점의 x좌표는 크고 y좌표는 작다면 오른쪽 꼭지점과 충돌 판정
		//원의 중점이 사각형 중점의 x좌표는 작고 y좌표는 크다면 왼쪽 아래 꼭지점과 원의 충돌판정
		//원의 중점이 사각형 중점의 x, y 좌표보다 크다면 오른쪽 아래 꼭지점과 원의 충돌 판정

		vector<2> const min = rect.Location - rect.Length / 2;
		vector<2> const max = rect.Location + rect.Length / 2;

		bool isrange_x = ((rect.Location[0] - rect.Length[0] / 2) < circle.Location[0]) && (circle.Location[0] < (rect.Location[0] + rect.Length[0] / 2));
		bool isrange_y = ((rect.Location[1] - rect.Length[1] / 2) < circle.Location[1]) && (circle.Location[1] < (rect.Location[1] + rect.Length[1] / 2));



		if (rect.Angle != 0)
		{
			return false;
		}
		else if (isrange_x || isrange_y)
		{
			//범위안이면 사각형 너비높이 +r 과 중점포인트와의 판정

			return Collide
			(
				tyPoint{ circle.Location },
				tyRectangle
				{
						   rect.Length + vector<2>(circle.Diameter,circle.Diameter),
						   rect.Angle,
						   rect.Location
				}
			);
		}
		else
		{
			if (rect.Location[0] < circle.Location[0])
			{
				if (rect.Location[1] < circle.Location[1])return Collide(tyPoint{ vector<2>(max[0],max[1]) }, circle);  //오른쪽 위
				if (circle.Location[1] < rect.Location[1])return Collide(tyPoint{ vector<2>(max[0],min[1]) }, circle); //오른쪽 아래
			}
			else
			{
				if (rect.Location[1] < circle.Location[1])return Collide(tyPoint{ vector<2>(min[0],max[1]) }, circle); //왼쪽 위
				if (circle.Location[1] < rect.Location[1])return Collide(tyPoint{ vector<2>(min[0],min[1]) }, circle); //왼쪽 아래
			}
		}

		return false;
	}
	bool Collide(HDC const hdc,int const x, int const y)
	{
		//pipeline -> 스왑체인 텍스쳐2d를 gdi로 가져와서 getpixel

		COLORREF const color = GetPixel(hdc, x, y);
		int const r = GetRValue(color);
		int const g = GetGValue(color);
		int const b = GetBValue(color);

		if(!(r==255 and g ==0 and b == 255) and y < MAPSIZE_H and x>0 and x< MAPSIZE_W)
			return true;
		return false;
	}
	float const calc_landing_angle(unsigned const start_x, unsigned const selected_y, HDC const& hmapdc)
	{
		long double leftpoint_x =start_x-2;
		long double leftpoint_y =0;
		long double rightpoint_x =static_cast<long double>(start_x)+2;
		long double rightpoint_y =0;
		bool letfpoint_isfound = false;
		bool rightpoint_isfound = false;

		for (unsigned j = selected_y-4; j < selected_y + 4; ++j)
		{
			if(!letfpoint_isfound)
			{
				if(Collide(hmapdc,static_cast<unsigned>(leftpoint_x),j))
				{
					leftpoint_y = j;
					letfpoint_isfound =true;
				}
			}
			if(!rightpoint_isfound)
			{
				if(Collide(hmapdc,static_cast<unsigned>(rightpoint_x),j))
				{
					rightpoint_y = j;
					rightpoint_isfound = true;
				}
			}
		}
		if(letfpoint_isfound and rightpoint_isfound)
		{
			long double i =atan((rightpoint_y-leftpoint_y)/(rightpoint_x-leftpoint_x));
			long double j =static_cast<float>( atan((rightpoint_y-leftpoint_y)/(rightpoint_x-leftpoint_x)));
			return static_cast<float>( atan((rightpoint_y-leftpoint_y)/(rightpoint_x-leftpoint_x)));
		}
		return 0.0f;

	}
	bool Collide_object(Object & obj, HDC const& hmapdc)
	{
		unsigned const start_x = static_cast<const unsigned>(obj.getpos().x);//이미지 가운데 x좌표
		unsigned const start_y = static_cast<const unsigned>(obj.getpos().y+obj.getheight()/2);

		for (unsigned j = start_y; j < start_y + 4; ++j) 
		{

			if(Collide(hmapdc, start_x, j))
			{
				obj.moveto({obj.getpos().x, static_cast<float>(j- obj.getheight()/2)});
				obj.stop_move(calc_landing_angle(start_x,j,hmapdc));
				return true;
			}
			
		}
		return false;
	}
	void Collide_objects(std::vector<Object>& obj, HDC const& hmapdc)
	{
		if (!obj.empty())
		{
			for (size_t i = 0; i < obj.size(); i++)
			{
				if (obj[i].is_falling())
					Collide_object(obj[i], hmapdc);
			}
		}
	}
	void Collide_objects(std::vector<Tank>& tank,std::vector<Missile>& missile, HDC const& hmapdc)
	{
		if (!tank.empty())
		{
			for (size_t i = 0; i < tank.size(); i++)
			{
				if (tank[i].is_falling())
					Collide_object(tank[i], hmapdc);
			}
		}
		if (!missile.empty())
		{
			for (size_t i = 0; i < missile.size(); i++)
			{
				if (missile[i].is_falling())
				{
					if (Collide_object(missile[i], hmapdc))
					{
						//부딪혔다면 폭발 후 제거
						missile[i].boom(hmapdc);
						missile.erase(missile.begin()+i);
					}
				}

			}
		}
	}
	void ballistics(std::vector<Tank>& tank,std::vector<Missile>& missile,float const delta)
	{
		if (!tank.empty())
		{
			for (size_t i = 0; i < tank.size(); i++)
			{
				tank[i].ballistics_equation(delta);
				if (tank[i].is_out())
				{
					tank[i].take_damage(TANK_HP);
					tank[i].stop_move(0.0f);
				}

			}
		}
		if (!missile.empty())
		{
			for (size_t i = 0; i < missile.size(); i++)
			{
				missile[i].ballistics_equation(delta);
				//화면밖으로 나가면 제거
				if(missile[i].is_out())
					missile.erase(missile.begin()+i);
				

			}
		}
	}


}
