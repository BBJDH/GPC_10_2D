#pragma once




class Object 
{
protected:
	//가속도 계산시 사용
	Position	   pos0;
	Position	   velocity0;
	float		   moving_time;

	//평시 사용
	Position	   pos;
	unsigned const width;
	unsigned const height;
	float		   velocity;
	float          moving_angle;
	float		   image_angle;
	bool		   falling;

	//for test
	Position	   support_point;


public:
	Object();
	Object(Position const & pos, unsigned const width, unsigned const height);
	Position const getpos() const;
	unsigned const getwidth() const;
	unsigned const getheight() const;
	float const gettime() const;
	float const getimage_angle()const;
	bool is_falling();
	void moveto(Position const & pos);
	void ballistics_equation(float const moving_time);
	void ballistics_initialize(float const moving_angle, float const velocity);
	void stop_move(float const thetha);

	//for test
	Position const getsup_pos() const;
	void setsup_pos(Position const& pos);

};

