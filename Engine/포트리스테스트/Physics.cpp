#include<Windows.h>
#include<vector>
#include"Object.h"
#include"vector.h"

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

		if(!(r==255 and g ==0 and b == 255))
			return true;
		return false;
	}
	Position find_secondpixel(unsigned const start_x, unsigned const selected_x, unsigned const selected_y, HDC const& hmapdc)
	{
		for (unsigned j = selected_y; j < selected_y + 4; ++j)
		{
			for (unsigned i = start_x; i < start_x + 4; ++i)
			{
				if ((i <= selected_x and j == selected_y) or  //�̹� �˻��Ѻκ� ����
					(i == selected_x))			//ó�� �浹�� �ȼ��� y���� �ٽð˻��� �ʿ� ����
					break;
				if (Collide(hmapdc, i, j))
				{
					return Position{ static_cast<float>(i), static_cast<float>(j) };
				}
			}
		}
		return Position({ static_cast<float>(selected_x), static_cast<float>(selected_y)	});
	}
	void Collide_object(Object & obj, HDC const& hmapdc)
	{


		unsigned const start_x = static_cast<const unsigned>(obj.getpos().x-2);//�̹��� x������� 2��ŭ����
		unsigned const start_y = static_cast<const unsigned>(obj.getpos().y+obj.getheight());
		//�̹��� �ǾƷ� y��ǥ
		Position first_point{}, second_point{};
		

		for (unsigned j = start_y; j < start_y + 4; ++j) 
		{
			for (unsigned  i = start_x; i < start_x + 4; ++i) //�������� 
			{
				if(Collide(hmapdc, i, j))
				{
					first_point = { static_cast<float>(i),static_cast<float>(j) };

					second_point = find_secondpixel(start_x, i, j, hmapdc);
					obj.setsup_pos(second_point);
					if (first_point.x > second_point.x)
					{
						Position temp = first_point;
						first_point = second_point;
						second_point = temp;
					}
					//unsigned fx = static_cast<unsigned>(first_point.x);
					//unsigned fy = static_cast<unsigned>(first_point.y);
					//unsigned sx = static_cast<unsigned>(second_point.x);
					//unsigned sy = static_cast<unsigned>(second_point.y);
					//Ellipse(hmapdc, fx - 20, fy - 20, fx + 20, fy + 20);
					//Ellipse(hmapdc, sx - 20, sy - 20, sx + 20, sy + 20);

					float const thetha = static_cast<const float>(atan2(
						static_cast<long double>(second_point.y - first_point.y),
						static_cast<long double>(second_point.x - first_point.x)));
					obj.moveto({obj.getpos().x, static_cast<float>(j- obj.getheight())});
					obj.stop_move(thetha/Radian);
					float c = thetha / Radian;
					return;

				}
			}
		}
		//SelectObject(hdc, oldbit);
		//ReleaseDC(hwindow, hdc);

	}
	void Collide_objects(std::vector<Object> & obj, HDC const & hmapdc)
	{
		if (!obj.empty())
		{
			for (size_t i = 0; i < obj.size(); i++)
			{
				if(!obj[i].is_stand())
					Collide_object(obj[i], hmapdc);
			}
		}
	}
	void Move(std::vector<Object>& obj,float const delta)
	{

		if (!obj.empty())
		{
			for (size_t i = 0; i < obj.size(); i++)
			{
				obj[i].ballistics_equation(delta);
			}
		}
	}

}

///
//
//    ----
//          -
//    ---- -
//      ----
// 
// 
// 
// 
//