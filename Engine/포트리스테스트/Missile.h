#pragma once
#include"stdafx.h"
class Missile
{
	enum class Type 
	{
		Circle, Ellipse
	};
private:
	Position pos;
	Type     explosion_type;
	unsigned width;
	unsigned height;
	unsigned damage;
	float    move_angle;
	float    move_speed;
};
//
//�̻��� Ŭ����
//{
//	private:
//	��ǥ
//	����Ÿ��(�� Ÿ�� �ٴ���Ʈ ������Ÿ���� �����α���)
//	���� �ݰ� �ʺ����
//	������
//	�̵�����
//	�߻�ӵ�(�߻� �Ŀ�(��)������, �߷°��ӵ��� ���� ����)
//
//	public:
//	�̵��Լ�(�̵��� ��ǥ)
//	�̵�����Լ�()
//	- ���� �̵��� ��ǥ�� ���, �浹�����̶�� ������ġ�� �̵��� ��ǥ�̸� �̵��Լ� ȣ�� �� �����Լ��� ȣ��
//	�����Լ�(ĳ����Ŭ���� �迭, ĳ���ͼ�)
//	- �浹�� ĳ���͵��� �������Լ� ȣ��, ���������Լ�ȣ��
//
//}