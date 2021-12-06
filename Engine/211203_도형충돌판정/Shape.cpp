 #include<Windows.h>
#include<vector>
#include<math.h>

enum Shape_name
{
	circle = 1, rect,
};

namespace Shape
{
	namespace
	{
		enum Side
		{
			Top, Bottom, Left, Right
		};
		double const PI = 3.1415926;
		double const degree = PI/180;
		std::vector<int*> Shape_pos; //{ 충돌플래그, 도형타입, x좌표, y좌표, 사이즈1,사이즈2, } 
		std::vector<double*> Shape_ang; //{향하는각도}{회전하는각도 0}
		int size = 50; 
		double const speed = 6; //중심좌표의 이동량과 회전각도
	}

	void setpos(int& x, int& y) //각 사이드별 랜덤 위치로 도형의 중점을 할당
	{
		size_t const side = rand() % 4;
		switch (side)
		{
			case Top: //화면 위에서 등장 (화면 800X600)
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
	void setang(int const & x, int const& y, double& angle, POINT const& player)
	{//플레이어를 향한 각도 계산
		angle = atan2(static_cast<double>(player.y) - y,
			static_cast<double>(player.x) - x);
	}
	void push(POINT const& player)
	{	
		//도형 생성
		Shape_pos.push_back(new int[6]{}); 
		Shape_ang.push_back(new double[2]{});

		{
			Shape_pos[Shape_pos.size() - 1][1] = Shape_name::rect; // 1.원 2.사각형
			Shape_pos[Shape_pos.size() - 1][4] = 50; //너비
			Shape_pos[Shape_pos.size() - 1][5] = 50; //높이

		}


		//도형의 중점 지정
		setpos(Shape_pos[Shape_pos.size() - 1][2], Shape_pos[Shape_pos.size() - 1][3]);


		//중점을 입력받아 player로 향하는 각도 계산
		setang(Shape_pos[Shape_pos.size() - 1][2], Shape_pos[Shape_pos.size() - 1][3],
					Shape_ang[Shape_pos.size() - 1][0], player);
	}
	void move()
	{
		
		for (size_t i = 0; i < Shape_pos.size(); i++)
		{
			if (Shape_pos[i][0]==0)
			{
				//player를 향해 이동할 양을 계산
				LONG movex = static_cast<LONG>(speed * cos(Shape_ang[i][0]));
				LONG movey = static_cast<LONG>(speed * sin(Shape_ang[i][0]));
				//중점 이동
				Shape_pos[i][2] += movex;
				Shape_pos[i][3] += movey;
			}

		}
	}
	std::vector<int*> const vecpoint()
	{
		return Shape_pos;
	}
	std::vector<double*> const vecang()
	{
		return Shape_ang;
	}

}