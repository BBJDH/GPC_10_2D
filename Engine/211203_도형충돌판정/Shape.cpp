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
		std::vector<int*> Shape_pos; //{ �浹�÷���, ����Ÿ��, x��ǥ, y��ǥ, ������1,������2, } 
		std::vector<double*> Shape_ang; //{���ϴ°���}{ȸ���ϴ°��� 0}
		int size = 50; 
		double const speed = 6; //�߽���ǥ�� �̵����� ȸ������
	}

	void setpos(int& x, int& y) //�� ���̵庰 ���� ��ġ�� ������ ������ �Ҵ�
	{
		size_t const side = rand() % 4;
		switch (side)
		{
			case Top: //ȭ�� ������ ���� (ȭ�� 800X600)
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
	{//�÷��̾ ���� ���� ���
		angle = atan2(static_cast<double>(player.y) - y,
			static_cast<double>(player.x) - x);
	}
	void push(POINT const& player)
	{	
		//���� ����
		Shape_pos.push_back(new int[6]{}); 
		Shape_ang.push_back(new double[2]{});

		{
			Shape_pos[Shape_pos.size() - 1][1] = Shape_name::rect; // 1.�� 2.�簢��
			Shape_pos[Shape_pos.size() - 1][4] = 50; //�ʺ�
			Shape_pos[Shape_pos.size() - 1][5] = 50; //����

		}


		//������ ���� ����
		setpos(Shape_pos[Shape_pos.size() - 1][2], Shape_pos[Shape_pos.size() - 1][3]);


		//������ �Է¹޾� player�� ���ϴ� ���� ���
		setang(Shape_pos[Shape_pos.size() - 1][2], Shape_pos[Shape_pos.size() - 1][3],
					Shape_ang[Shape_pos.size() - 1][0], player);
	}
	void move()
	{
		
		for (size_t i = 0; i < Shape_pos.size(); i++)
		{
			if (Shape_pos[i][0]==0)
			{
				//player�� ���� �̵��� ���� ���
				LONG movex = static_cast<LONG>(speed * cos(Shape_ang[i][0]));
				LONG movey = static_cast<LONG>(speed * sin(Shape_ang[i][0]));
				//���� �̵�
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