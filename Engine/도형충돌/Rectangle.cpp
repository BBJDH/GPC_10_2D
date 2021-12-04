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
		std::vector<POINT*> rect_pos; //{중점}{왼쪽위}{오른쪽위}{왼쪽아래}{오른쪽아래점}
		std::vector<double*> rect_ang; //{향하는각도}{회전하는각도}
		//사각형은 가로세로 100으로
		LONG halfwidth_size = 50; 
		double const speed = 4; //중심좌표의 이동량과 회전각도
	}


	void setrectpos(LONG& x, LONG& y) //각 사이드별 랜덤 위치로 사각형의 중점을 할당
	{
		size_t const side = rand() % 4;
		switch (side)
		{
			case Top: //화면 위
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
	{//플레이어를 향한 각도 계산
		angle = atan2(static_cast<double>(player.y) - y,
			static_cast<double>(player.x) - x);
	}
	void push_rect(POINT const& player)
	{//사각형 생성
		rect_pos.push_back(new POINT[5]{});
		rect_ang.push_back(new double[2]{});
	


		//사각형의 중점 지정
		setrectpos(rect_pos[rect_pos.size() - 1][0].x, rect_pos[rect_pos.size() - 1][0].y);

		//중점을 입력받아 player로 향하는 각도 계산
		setrectang(rect_pos[rect_pos.size() - 1][0].x, rect_pos[rect_pos.size() - 1][0].y,
					rect_ang[rect_pos.size() - 1][0], player);
	}
	void move_rect()
	{
		
		for (size_t i = 0; i < rect_pos.size(); i++)
		{
			//player를 향해 이동할 양을 계산
			LONG movex = static_cast<LONG>(speed * cos(rect_ang[i][0]));
			LONG movey = static_cast<LONG>(speed * sin(rect_ang[i][0]));

			//중점 이동
			rect_pos[i][0].x += movex;
			rect_pos[i][0].y += movey;

			//사각형 각도 회전
			rect_ang[i][1]   += degree * speed;

			LONG centerx = rect_pos[i][0].x;
			LONG centery = rect_pos[i][0].y;

			float costheta = static_cast<float>(cos(rect_ang[i][1]));
			float sintheta = static_cast<float>(sin(rect_ang[i][1]));

			//정사각형 rect의 각 꼭지점까지의 거리
			LONG size = static_cast<long>(halfwidth_size * sqrt(2));

			//각 점의 회전
			rect_pos[i][1].x = centerx + static_cast<long>((-size * sintheta));
			rect_pos[i][1].y = centery + static_cast<long>((-size * costheta));
			rect_pos[i][2].x = centerx + static_cast<long>(( size * costheta));
			rect_pos[i][2].y = centery + static_cast<long>((-size * sintheta));
			rect_pos[i][3].x = centerx + static_cast<long>((-size * costheta));
			rect_pos[i][3].y = centery + static_cast<long>(( size * sintheta));
			rect_pos[i][4].x = centerx + static_cast<long>(( size * sintheta));
			rect_pos[i][4].y = centery + static_cast<long>(( size * costheta));
		}
	}
	std::vector<POINT*> const vecpoint()
	{
		return rect_pos;
	}
	std::vector<double*> const vecang()
	{
		return rect_ang;
	}

}