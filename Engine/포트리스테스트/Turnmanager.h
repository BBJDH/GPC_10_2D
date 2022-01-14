#pragma once
#include"SingletonT.h"
#include"Random.h"
class Turnmanager :public SingletonT<Turnmanager>
{
private:
	Random rand;

public:
	//각 플레이어와 미사일의 턴이 꺼져있으면 
	//다음플레이어의 턴을 켜준다
	Turnmanager();
	~Turnmanager();

};
