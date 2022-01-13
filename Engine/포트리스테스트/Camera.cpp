
#include"Camera.h"
#include"stdafx.h"

Camera::Camera() :pos{ 1.0f,11.0f }, speed{3}
{}

void Camera::move(Mouse::POS_STATE state)
{
	switch (state)
	{
	case Mouse::POS_STATE::Side_Up:        
	{
		if(pos.y>0)pos.y-=speed;
		return; 
	}
	case Mouse::POS_STATE::Side_Left:      
	{
		if(pos.x>0)pos.x-=speed;
		return; 
	}
	case Mouse::POS_STATE::Side_Right:     
	{
		if(pos.x+WINSIZE_X<MAPSIZE_W)pos.x+=speed;
		return; 
	}
	case Mouse::POS_STATE::Side_Down:      
	{
		if(pos.y+WINSIZE_Y<MAPSIZE_H+UI_H)pos.y+=speed;
		return; 
	}
	case Mouse::POS_STATE::Side_LeftUP:    
	{
		if (pos.x > 0 and pos.y > 0)
		{
			pos.x-=speed; pos.y-=speed;
		}
		return; 
	}
	case Mouse::POS_STATE::Side_RightUP:   
	{
		if (pos.x + WINSIZE_X < MAPSIZE_W and pos.y>0)
		{
			pos.x+=speed; pos.y-=speed;
		}
		return; 
	}
	case Mouse::POS_STATE::Side_LeftDown:  
	{
		if (pos.x > 0 and pos.y + WINSIZE_Y < MAPSIZE_H+UI_H)
		{
			pos.x-=speed; pos.y+=speed;
		}
		return; 
	}
	case Mouse::POS_STATE::Side_RightDown: 
	{
		if (pos.x + WINSIZE_X < MAPSIZE_W and pos.y + WINSIZE_Y < MAPSIZE_H+UI_H)
		{
			pos.x+=speed; pos.y+=speed;
		}
		return; 
	}
	default: return;
	}
}