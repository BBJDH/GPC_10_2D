
#include"Camera.h"
#include"stdafx.h"

Camera::Camera() :pos{ 1.0f,11.0f }, speed{4}
{}

void Camera::move(Mouse::POS_STATE state)
{
	switch (state)
	{
	case Mouse::POS_STATE::Side_Up:        
	{
		if (pos.y > speed)
		{
			pos.y -= speed;
		}
			return;
	}
	case Mouse::POS_STATE::Side_Left:      
	{
		if (pos.x > speed)
		{
			pos.x -= speed;
		}
			return;
	}
	case Mouse::POS_STATE::Side_Right:     
	{
		if (pos.x + WINSIZE_X+speed < MAPSIZE_W)
		{
			pos.x += speed;
		}
			return;
	}
	case Mouse::POS_STATE::Side_Down:      
	{
		if (pos.y + WINSIZE_Y+speed < MAPSIZE_H+UI_H)
		{
			pos.y += speed;
		}
			return;
	}
	case Mouse::POS_STATE::Side_LeftUP:    
	{
		if (pos.x > speed and pos.y > speed)
		{
			pos.x-=speed; pos.y-=speed;
		}
		return; 
	}
	case Mouse::POS_STATE::Side_RightUP:   
	{
		if (pos.x + WINSIZE_X+speed < MAPSIZE_W and pos.y>speed)
		{
			pos.x+=speed; pos.y-=speed;
		}
		return; 
	}
	case Mouse::POS_STATE::Side_LeftDown:  
	{
		if (pos.x > speed and pos.y + WINSIZE_Y+speed < MAPSIZE_H+UI_H)
		{
			pos.x-=speed; pos.y+=speed;
		}
		return; 
	}
	case Mouse::POS_STATE::Side_RightDown: 
	{
		if (pos.x + WINSIZE_X+speed < MAPSIZE_W and pos.y + WINSIZE_Y+speed < MAPSIZE_H+UI_H)
		{
			pos.x+=speed; pos.y+=speed;
		}
		return; 
	}
	default: return;
	}
}