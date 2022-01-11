#include "Tank.h"

Tank::Tank(Position const& pos, unsigned const width, unsigned const height)
	:Object(pos, width, height), hp{ 1000 }, stamina{50},
	fire_angle{ 0.0f }, fire_velocity{0.0f},state{State::Nomal_right}
{
}
//namespace Physics
//{
//	bool Collide(HDC const hdc, int const x, int const y)
//}
unsigned const Tank::gethp() const
{
	return this->hp;
}

void Tank::take_damage(unsigned const damage)
{
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
