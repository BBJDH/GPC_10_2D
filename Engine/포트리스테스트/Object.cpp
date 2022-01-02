#include "Object.h"

Object::Object() :pos{ 400.0f,0.0f }, pos0{ 0.0f,0.0f }, velocity0{ 0.0f,0.0f }, width{ 0 }, height{ 0 },
move_time{ 0.0f }, move_angle{ 45.0f }, image_angle{0.0f}
{
}

void Object::moveto(Position pos)
{
	this->pos.x = pos.x;
	this->pos.y = pos.y;
}

void Object::ballistics_initialize(float const move_angle, Position const velocity0)
{
	this->move_angle = move_angle;
	this->velocity0 = velocity0;
	this->pos0 = pos;
}

Position const Object::getpos() const
{
	return this->pos;
}

float const Object::gettime() const
{
	return move_time;
}

void Object::ballistics_equation(float delta)
{
	this->move_time += delta* SPEED;
	this->pos.x = this->pos0.x + velocity0.x * move_time;
	this->pos.y = this->pos0.y - velocity0.y * move_time
				  +(grav_accerl*static_cast<float>(pow(move_time,2)))/2;
}


