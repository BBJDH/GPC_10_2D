#pragma once
#include "Object.h"


class Tank : public Object
{
public:
	enum class State
	{
		Nomal_right, Nomal_left, Fire_right, Fire_left, Stop_right, Stop_left, //...
	};

private:
	State		   state;
	unsigned	   hp;
	unsigned	   stamina;
	float		   fire_angle;
	float		   fire_velocity;


public:



	Tank(Position const& pos, unsigned const width, unsigned const height);
	unsigned const gethp() const;
	void take_damage(unsigned const damage);
	void input_key(WPARAM const wparam);
	void setstate(State const state);

	
};


