
#include"Camera.h"
#include"stdafx.h"

void Camera::up()
{
	pos.y -= speed;
	if(pos.y <0)
		pos.y =0;
}

void Camera::down()
{
	pos.y += speed;
	if(pos.y + WINSIZE_Y>MAPSIZE_H+UI_H)
		pos.y = MAPSIZE_H+UI_H-WINSIZE_Y;
}

void Camera::left()
{
	pos.x -= speed;
	if(pos.x <0)
		pos.x =0;
}

void Camera::right()
{
	pos.x += speed;
	if(pos.x + WINSIZE_X>MAPSIZE_W)
		pos.x = MAPSIZE_W-WINSIZE_X;
}

Camera::Camera() :pos{ 1.0f,1.0f }, speed{UI_SCREEN_SCROLL}
{}

void Camera::move(Mouse::POS_STATE state)
{
	switch (state)
	{
	case Mouse::POS_STATE::Side_Up:        
	{
		up();
		return;
	}
	case Mouse::POS_STATE::Side_Left:      
	{
		left();
		return;
	}
	case Mouse::POS_STATE::Side_Right:     
	{
		right();
		return;
	}
	case Mouse::POS_STATE::Side_Down:      
	{
		down();
		return;
	}
	case Mouse::POS_STATE::Side_LeftUP:    
	{
		left();
		up();
		return; 
	}
	case Mouse::POS_STATE::Side_RightUP:   
	{
		right();
		up();
		return; 
	}
	case Mouse::POS_STATE::Side_LeftDown:  
	{
		left();
		down();
		return; 
	}
	case Mouse::POS_STATE::Side_RightDown: 
	{
		right();
		down();
		return; 
	}
	default: return;
	}
}