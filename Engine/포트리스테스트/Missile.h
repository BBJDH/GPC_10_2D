#pragma once

class Missile : public Object
{
	//enum class Type 
	//{
	//	Circle, Ellipse
	//};
private:

	//Type     explosion_type;

public:
	Missile(Position const& pos, unsigned const width, unsigned const height);

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