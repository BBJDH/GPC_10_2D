#include<Windows.h>
#include<vector>
#include"Object.h"


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
	bool Collide(HDC const hdc,int const x, int const y)
	{
		//pipeline -> 스왑체인 텍스쳐2d를 gdi로 가져와서 getpixel

		COLORREF const color = GetPixel(hdc, x, y);
		int const r = GetRValue(color);
		int const g = GetRValue(color);
		int const b = GetRValue(color);


		//if (y > 510)
		//	int i = 0;

		//if(!(r==255 and g ==0 and b == 255))
		if(r==255 and g ==255 and b == 255)
			return true;
		return false;
	}
	void Collide_object(HWND const& hwindow, Object & obj, HDC const& hmapdc)
	{
		//HDC hdc = GetDC(hwindow);
		//HBITMAP oldbit = static_cast<HBITMAP>(SelectObject(hmapdc, hmapdc));

		unsigned const start_x = static_cast<const unsigned>(obj.getpos().x-2);//이미지 x가운데에서 2만큼왼쪽
		unsigned const start_y = static_cast<const unsigned>(obj.getpos().y+obj.getheight());
		//이미지 맨아래 y좌표

		for (unsigned i = start_y; i < start_y + 4; ++i) 
		{
			for (unsigned  j = start_x; j < start_x + 4; ++j) //중점에서 
			{
				if(Collide(hmapdc, j, i))
				{
					obj.moveto({obj.getpos().x,static_cast<float>(i- obj.getheight())});
					obj.stop_move();
					//ReleaseDC(hwindow, hdc);
					return;
				}
			}
		}
		//SelectObject(hdc, oldbit);
		//ReleaseDC(hwindow, hdc);

	}
	void Collide_objects(HWND const& hwindow, std::vector<Object> & obj, HDC const & hmapdc)
	{
		if (!obj.empty())
		{
			for (size_t i = 0; i < obj.size(); i++)
			{
				Collide_object(hwindow,obj[i], hmapdc);
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