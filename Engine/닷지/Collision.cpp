#include<Windows.h>
#include<vector>


namespace Collision
{

	float distance(long dest_x, long dest_y, long src_x, long src_y)
	{
		return static_cast<float>(sqrt(pow(dest_x-src_x,2)+pow(dest_y-src_y,2)));
	}

	bool iscrashed(std::vector<POINT> const& missile,
		POINT const & player)
	{
		for (size_t i = 0; i < missile.size(); i++)
		{
			if(distance(player.x,player.y,missile[i].x,missile[i].y)<10)
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
	//충돌판정 로직
	//점대점
	//플레이어 - 미사일 간격이 15px 이하면 충돌

}