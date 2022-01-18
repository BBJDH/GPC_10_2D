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
	State		    state;
	unsigned	    hp;
	unsigned	    stamina;
	float const		fire_angle_min;
	float const		fire_angle_max;
	float		    fire_angle;
	float		    fire_velocity;


public:

	Tank(Position const& pos, unsigned const width, unsigned const height);
	Tank & operator=(Tank const & other_tank);
	unsigned const gethp() const;
	int const getpower()const;
	int const getangle()const;
	int const getangle_min()const;
	int const getangle_max()const;
	bool is_dead()const;
	void take_damage(unsigned const damage);
	void input_key(WPARAM const wparam);
	void setstate(State const state);
	void plus_angle(int angle);
	void plus_power();
	void turn_setting();

	
};


