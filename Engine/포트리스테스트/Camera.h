#pragma once
#include "SingletonT.h"

class Camera :public SingletonT<Camera>
{
public:

	Position Pos;

	Camera();
	~Camera() {};

};


Camera::Camera() :Pos{0.0f,0.0f}
{}