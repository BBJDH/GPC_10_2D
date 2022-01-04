#include "Object.h"

Object::Object() :pos{ 400.0f,0.0f }, pos0{ 0.0f,0.0f }, velocity0{ 0.0f,0.0f }, width{ 0 }, height{ 0 },
velocity{ 0.0f }, move_time{ 0.0f }, move_angle{ 0.0f }, image_angle{ 0.0f }, is_stand{true}
{
}

Object::Object(Position const & pos, unsigned const width, unsigned const height) : pos{ pos }, pos0{ 0.0f,0.0f }, velocity0{ 0.0f,0.0f }, width{ width }, height{ height },
velocity{ 0.0f }, move_time{ 0.0f }, move_angle{ 0.0f }, image_angle{ 0.0f }, is_stand{ true }
{
}

void Object::moveto(Position const & pos)
{
	this->pos.x = pos.x;
	this->pos.y = pos.y;
}

void Object::ballistics_initialize(float const move_angle, float const velocity)
{
	this->move_angle = move_angle*Radian;
	this->velocity0.x = velocity*static_cast<float>(cos(this->move_angle));
	this->velocity0.y = velocity*static_cast<float>(sin(this->move_angle));
	this->pos0 = pos;
	this->is_stand = false;
}

Position const Object::getpos() const
{
	return this->pos;
}

float const Object::gettime() const
{
	return move_time;
}

unsigned const Object::getwidth() const
{
	return this->width;
}

unsigned const Object::getheight() const
{
	return this->height;
}

void Object::stop_move()
{
	this->is_stand = true;
}

void Object::ballistics_equation(float const delta)
{
	if (!is_stand)
	{
		this->move_time += delta* SPEED;
		this->pos.x = this->pos0.x + velocity0.x * move_time;
		this->pos.y = this->pos0.y - velocity0.y * move_time
					  +(grav_accerl*static_cast<float>(pow(move_time,2)))/2;
	}
}


