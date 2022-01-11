#include "Tank.h"

Tank::Tank(Position const& pos, unsigned const width, unsigned const height)
	:Object(pos, width, height), hp{ 1000 }, fire_angle{ 0.0f }, fire_velocity{0.0f}
{
}

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
	if (wparam == VK_RIGHT)
	{
		this->pos.x++;
	}
	else if (wparam == VK_LEFT)
	{
		this->pos.x--;

	}
}
