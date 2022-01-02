#pragma once
#include"stdafx.h"

class Object 
{
private:
	Position	   pos;
	Position	   pos0;
	Position	   velocity0;
	unsigned const width;
	unsigned const height;
	float		   move_time;
	float          move_angle;
	float		   image_angle;

public:
	Object();
	void moveto(Position pos);
	void ballistics_equation(float move_time);
	void ballistics_initialize(float const move_angle, Position const velocity0);
	Position const getpos() const;
	float const gettime() const;
};

