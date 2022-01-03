#include "Object.h"

Object::Object() :pos{ 10.0f,500.0f }, pos0{ 0.0f,0.0f }, velocity0{ 0.0f,0.0f }, width{ 0 }, height{ 0 },
velocity{0.0f}, move_time{ 0.0f }, move_angle{ 45.0f }, image_angle{ 0.0f }
{
}

void Object::moveto(Position pos)
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


