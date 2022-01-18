#include "Object.h"
#include"stdafx.h"

Tank::Tank(Position const& pos, unsigned const width, unsigned const height)
	:Object(pos, width, height), hp{ TANK_HP }, stamina{50},
	fire_angle_min{35}, fire_angle_max{65},
	fire_angle{ 0 }, fire_velocity{ 0.0f }, state{State::Nomal_right}
{
}
Tank& Tank::operator=(Tank const& other_tank)
{
	assign(other_tank);
	this->state          = other_tank.state;
	this->hp             = other_tank.hp;
	this->stamina        = other_tank.stamina;
	this->fire_angle     = other_tank.fire_angle;
	this->fire_velocity  = other_tank.fire_velocity;
	return *this;
}
//namespace Physics
//{
//	bool Collide(HDC const hdc, int const x, int const y)
//}
unsigned const Tank::gethp() const
{
	return this->hp;
}

int const Tank::getpower() const
{
	return static_cast<int const>(fire_velocity);
}

int const Tank::getangle() const
{
	return static_cast<int const>(fire_angle);
}

int const Tank::getangle_min() const
{
	return static_cast<int const>(fire_angle_min);
}

int const Tank::getangle_max() const
{
	return static_cast<int const>(fire_angle_max);
}

bool Tank::is_dead() const
{
	if(this->hp==0)
		return true;
	return false;
}

void Tank::plus_power()
{
	fire_velocity++;
}

void Tank::turn_setting()
{
	this->stamina = 50;
	this->fire_velocity = 0;
}

void Tank::take_damage(unsigned const damage)
{
	if (damage >= this->hp)
	{
		this->hp =0;
		return;
	}
	this->hp -= damage;
}

void Tank::input_key(WPARAM const wparam)
{
	if (wparam == VK_RIGHT )
	{
		if (this->state == Tank::State::Nomal_right)
			this->stamina++;
		else
			this->state = Tank::State::Nomal_right;
	}
	else if (wparam == VK_LEFT)
	{
		if(this->state == Tank::State::Nomal_left)
			this->stamina++; //TODO:이동테스트종료후 --로
		else
		{
			this->state = Tank::State::Nomal_left;
		}

	}
}

void Tank::setstate(State const state)
{
	this->state = state;
}

void Tank::plus_angle(int angle)
{
	this->fire_angle += angle;
	if(fire_angle >fire_angle_max-fire_angle_min or fire_angle<0)
		this->fire_angle -= angle;

}

