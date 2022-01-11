#include "Object.h"

Object::Object() :pos{ 400.0f,0.0f }, pos0{ 0.0f,0.0f }, velocity0{ 0.0f,0.0f }, width{ 0 }, height{ 0 },
velocity{ 0.0f }, moving_time{ 0.0f }, moving_angle{ 0.0f }, image_angle{ 0.0f }, falling{true},
/*test*/ support_point{0.0f,0.0f}
{
}

Object::Object(Position const & pos, unsigned const width, unsigned const height) : pos{ pos }, pos0{ 0.0f,0.0f }, velocity0{ 0.0f,0.0f }, width{ width }, height{ height },
velocity{ 0.0f }, moving_time{ 0.0f }, moving_angle{ 0.0f }, image_angle{ 0.0f }, falling{ true },
/*test*/ support_point{ 0.0f,0.0f }
{
}

void Object::moveto(Position const & pos)
{
	this->pos.x = pos.x;
	this->pos.y = pos.y;
}

void Object::ballistics_initialize(float const moving_angle, float const velocity)
{
	this->moving_angle = moving_angle*Radian;
	this->velocity0.x = velocity*static_cast<float>(cos(this->moving_angle));
	this->velocity0.y = velocity*static_cast<float>(sin(this->moving_angle));
	this->pos0 = pos;
	this->falling = true;
}
//OOP
Position const Object::getpos() const
{
	return this->pos;
}

float const Object::gettime() const
{
	return moving_time;
}

unsigned const Object::getwidth() const
{
	return this->width;
}

unsigned const Object::getheight() const
{
	return this->height;
}

float const Object::getimage_angle() const
{
	return image_angle;
}

bool Object::is_falling()
{
	return falling;
}

void Object::stop_move(float const thetha)
{
	this->image_angle = thetha;
	this->falling = false;
	this->moving_time = 0.0f;
	this->pos0 = this->pos;
}

Position const Object::getsup_pos() const
{
	return support_point;
}

void Object::setsup_pos(Position const& pos)
{
	this->support_point = pos;
}

void Object::ballistics_equation(float const delta)
{
	if (falling)
	{
		this->moving_time += delta* SPEED;
		this->pos.x = this->pos0.x + velocity0.x * moving_time;
		this->pos.y = this->pos0.y - velocity0.y * moving_time
					  +(grav_accerl*static_cast<float>(pow(moving_time,2)))/2;
	}
}


