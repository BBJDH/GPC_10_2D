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
	//���� ����
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
		//�簢���� �ʺ���� Ȥ�� ���� ���� �ȿ� ���Դٸ�, �簢���ʺ� ���̿� r��ŭ ���� �簢���� ���� �������� �浹 ����
		//���� ������ �簢�� ������ x, y ��ǥ���� �۴ٸ� ������ �������� ���� �浹 ����
		//���� ������ �簢�� ������ x��ǥ�� ũ�� y��ǥ�� �۴ٸ� ������ �������� �浹 ����
		//���� ������ �簢�� ������ x��ǥ�� �۰� y��ǥ�� ũ�ٸ� ���� �Ʒ� �������� ���� �浹����
		//���� ������ �簢�� ������ x, y ��ǥ���� ũ�ٸ� ������ �Ʒ� �������� ���� �浹 ����

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
			//�������̸� �簢�� �ʺ���� +r �� ��������Ʈ���� ����

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
				if (rect.Location[1] < circle.Location[1])return Collide(tyPoint{ vector<2>(max[0],max[1]) }, circle);  //������ ��
				if (circle.Location[1] < rect.Location[1])return Collide(tyPoint{ vector<2>(max[0],min[1]) }, circle); //������ �Ʒ�
			}
			else
			{
				if (rect.Location[1] < circle.Location[1])return Collide(tyPoint{ vector<2>(min[0],max[1]) }, circle); //���� ��
				if (circle.Location[1] < rect.Location[1])return Collide(tyPoint{ vector<2>(min[0],min[1]) }, circle); //���� �Ʒ�
			}
		}

		return false;
	}
	bool Collide(HDC const hdc,int const x, int const y)
	{
		//pipeline -> ����ü�� �ؽ���2d�� gdi�� �����ͼ� getpixel

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
		unsigned const start_x = static_cast<const unsigned>(obj.getpos().x);//�̹��� ��� x��ǥ
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
						//�ε����ٸ� ���� �� ����
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
				//ȭ������� ������ ����
				if(missile[i].is_out())
					missile.erase(missile.begin()+i);
				

			}
		}
	}


}
