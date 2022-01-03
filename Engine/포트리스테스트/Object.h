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
	float		   velocity;
	float		   move_time;
	float          move_angle;
	float		   image_angle;
	bool		   is_stand;

public:
	Object();
	Object(Position const pos, unsigned const width, unsigned const height);
	Position const getpos() const;
	float const gettime() const;
	unsigned const getwidth() const;
	unsigned const getheight() const;
	void moveto(Position pos);
	void ballistics_equation(float move_time);
	void ballistics_initialize(float const move_angle, float const velocity);
	void stop_move();
};

