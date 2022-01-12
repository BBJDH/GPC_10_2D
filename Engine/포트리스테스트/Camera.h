#pragma once
#include "stdafx.h"
#include"SingletonT.h"


class Camera :public SingletonT<Camera>
{
public:

	Position pos;
public:

	Camera();
	~Camera() {};

	void move(Mouse::POS_STATE state);
};


Camera::Camera() :pos{0.0f,0.0f}
{}

void Camera::move(Mouse::POS_STATE state)
{
	switch (state)
	{
		case Mouse::POS_STATE::Side_Left:      {pos.x--;		 return;}
		case Mouse::POS_STATE::Side_Right:	   {pos.x++;		 return;}
		case Mouse::POS_STATE::Side_Up:		   {pos.y--;		 return;}
		case Mouse::POS_STATE::Side_Down:	   {pos.y++;		 return;}
		case Mouse::POS_STATE::Side_LeftUP:	   {pos.x--;pos.y--; return;}
		case Mouse::POS_STATE::Side_RightUP:   {pos.x++;pos.y--; return;}
		case Mouse::POS_STATE::Side_LeftDown:  {pos.x--;pos.y++; return;}
		case Mouse::POS_STATE::Side_RightDown: {pos.x++;pos.y++; return;}
		default: return;
	}
}