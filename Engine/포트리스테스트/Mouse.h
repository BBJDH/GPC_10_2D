#pragma once
//#include"stdafx.h"
#include"SingletonT.h"

class Mouse : public SingletonT<Mouse>
{
public:

	enum class POS_STATE 
	{
		Side_Left, Side_Right, Side_Up, Side_Down, 
		Side_LeftUP, Side_RightUP, Side_LeftDown, Side_RightDown, In_Window
	};
	LONG x;
	LONG y;
public:
	Mouse();
	~Mouse() {};
	POS_STATE getpos();

};

