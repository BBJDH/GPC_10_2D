#pragma once
#include"SingletonT.h"
#include"Random.h"
class Turnmanager :public SingletonT<Turnmanager>
{
private:
	Random rand;

public:
	//�� �÷��̾�� �̻����� ���� ���������� 
	//�����÷��̾��� ���� ���ش�
	Turnmanager();
	~Turnmanager();

};
