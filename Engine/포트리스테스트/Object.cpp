#include "Object.h"
#include"stdafx.h"




Object::Object() :pos{ 400.0f,0.0f }, pos0{ 0.0f,0.0f }, velocity0{ 0.0f,0.0f }, width{ 0 }, height{ 0 },
velocity{ 0.0f }, moving_time{ 0.0f }, moving_angle{ 0.0f }, image_angle{ 0.0f }, falling{true},myturn{false},
out{false},/*test*/ support_point{ 0.0f,0.0f }
{
}

Object::Object(Position const & pos, unsigned const width, unsigned const height) : pos{ pos }, pos0{ 0.0f,0.0f }, velocity0{ 0.0f,0.0f }, width{ width }, height{ height },
velocity{ 0.0f }, moving_time{ 0.0f }, moving_angle{ 0.0f }, image_angle{ 0.0f }, falling{ true },myturn{false},
out{false},/*test*/ support_point{ 0.0f,0.0f }
{
}

Object::Object(Object const& obj):pos{ obj.pos }, pos0{ obj.pos0 }, velocity0{ obj.velocity0 }, width{ obj.width }, height{ obj.height },
velocity{ obj.velocity }, moving_time{ obj.moving_time }, moving_angle{ obj.moving_angle }, image_angle{ obj.image_angle }, falling{obj.falling},myturn{obj.myturn},
out{obj.out},/*test*/ support_point{obj.support_point }

{
}
void Object::asign(Object const& other_obj)
{
	this->pos0          = other_obj.pos0         ;
	this->velocity0     = other_obj.velocity0    ;
	this->moving_time   = other_obj.moving_time  ;
	this->pos           = other_obj.pos          ;
	this->velocity      = other_obj.velocity     ;
	this->moving_angle  = other_obj.moving_angle ;
	this->image_angle   = other_obj.image_angle  ;
	this->falling       = other_obj.falling      ;
	this->myturn        = other_obj.myturn       ;
	this->out           = other_obj.out          ;
	this->support_point = other_obj.support_point;
}

Object& Object::operator=(Object const& other_obj)
{
	asign(other_obj);
	return *this;
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

float const Object::getimage_angle() const //Radian ¹ÝÈ¯ (-PIE/2 ~ PIE/2)
{
	return image_angle;
}

bool Object::is_falling() const
{
	return falling;
}

bool Object::is_myturn() const
{
	return myturn;
}

bool Object::is_out() const
{
	return out;
}

void Object::stop_move(float const thetha)
{
	this->image_angle = thetha;
	this->falling = false;
	this->moving_time = 0.0f;
	this->pos0 = this->pos;
}

void Object::setmyturn(bool myturn)
{
	this->myturn = myturn;
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
	if(this->pos.y>MAPSIZE_H or this->pos.x >MAPSIZE_W or this->pos.x<0)
		this->out = true;
}


