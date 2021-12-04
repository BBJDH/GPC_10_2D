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
		std::vector<POINT*> rect_pos; //{����}{������}{��������}{���ʾƷ�}{�����ʾƷ���}
		std::vector<double*> rect_ang; //{���ϴ°���}{ȸ���ϴ°���}
		//�簢���� ���μ��� 100����
		LONG halfwidth_size = 50; 
		double const speed = 4; //�߽���ǥ�� �̵����� ȸ������
	}


	void setrectpos(LONG& x, LONG& y) //�� ���̵庰 ���� ��ġ�� �簢���� ������ �Ҵ�
	{
		size_t const side = rand() % 4;
		switch (side)
		{
			case Top: //ȭ�� ��
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
	{//�÷��̾ ���� ���� ���
		angle = atan2(static_cast<double>(player.y) - y,
			static_cast<double>(player.x) - x);
	}
	void push_rect(POINT const& player)
	{//�簢�� ����
		rect_pos.push_back(new POINT[5]{});
		rect_ang.push_back(new double[2]{});
	


		//�簢���� ���� ����
		setrectpos(rect_pos[rect_pos.size() - 1][0].x, rect_pos[rect_pos.size() - 1][0].y);

		//������ �Է¹޾� player�� ���ϴ� ���� ���
		setrectang(rect_pos[rect_pos.size() - 1][0].x, rect_pos[rect_pos.size() - 1][0].y,
					rect_ang[rect_pos.size() - 1][0], player);
	}
	void move_rect()
	{
		
		for (size_t i = 0; i < rect_pos.size(); i++)
		{
			//player�� ���� �̵��� ���� ���
			LONG movex = static_cast<LONG>(speed * cos(rect_ang[i][0]));
			LONG movey = static_cast<LONG>(speed * sin(rect_ang[i][0]));

			//���� �̵�
			rect_pos[i][0].x += movex;
			rect_pos[i][0].y += movey;

			//�簢�� ���� ȸ��
			rect_ang[i][1]   += degree * speed;

			LONG centerx = rect_pos[i][0].x;
			LONG centery = rect_pos[i][0].y;

			float costheta = static_cast<float>(cos(rect_ang[i][1]));
			float sintheta = static_cast<float>(sin(rect_ang[i][1]));

			//���簢�� rect�� �� ������������ �Ÿ�
			LONG size = static_cast<long>(halfwidth_size * sqrt(2));

			//�� ���� ȸ��
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