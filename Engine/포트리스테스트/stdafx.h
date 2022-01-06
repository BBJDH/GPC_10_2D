#pragma once
#include<math.h>
#define grav_accerl 9.8f //Gravialional accerleration
#define PI 3.141592f
#define Radian (PI/180.0f)
#define SPEED 6



struct Position
{
	float x;
	float y;
};


#include<d3d11.h>
#include<D3DX10math.h>
#include<D3DX11async.h> //À©µµ 

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")
