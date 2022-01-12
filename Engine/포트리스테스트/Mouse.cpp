#include "stdafx.h"
#include "Mouse.h"

Mouse::Mouse() :x{ 0 }, y{0}
{
}

Mouse::POS_STATE Mouse::getpos()
{
	if (x == 0 and y == 0) //����
		return POS_STATE::Side_LeftUP;
	else if (x == WINSIZE_X and y == 0)//������
		return POS_STATE::Side_RightUP;
	else if (x == 0 and y == WINSIZE_Y)//�޾Ʒ�
		return POS_STATE::Side_LeftDown;
	else if (x == WINSIZE_X and y == WINSIZE_Y)//�����Ʒ�
		return POS_STATE::Side_RightDown;
	else if (x == 0)
		return POS_STATE::Side_Left;
	else if (x == WINSIZE_X)
		return POS_STATE::Side_Right;
	else if (y == 0)
		return POS_STATE::Side_LeftUP;
	else if (y == WINSIZE_X)
		return POS_STATE::Side_Down;
	return POS_STATE::In_Window;


}
