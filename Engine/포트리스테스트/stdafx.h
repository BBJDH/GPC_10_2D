#pragma once

//���� ���
#include<Windows.h>
#include<math.h>
#include<time.h>
#include<chrono>


//STL
#include<vector>
#include<string>

//=====================================
//	## ���� ���� ����ü �̰��� �߰� ##
//=====================================

//����ü
struct Position
{
	float x;
	float y;
};

//=====================================
//	## ���� ���� ������� �̰��� �߰� ##
//=====================================



//���Ӿ� ������ ��ü��
#include"Tank.h"


//�浹�� ���� ����(cmath)
#include"vector.h"

//�̱��� ����
#include"Camera.h"

//=====================================
//	## �̱��� �߰� ##
//=====================================
#define _CAM Camera::get_singleton()


//=====================================
//	## �����ι� ## (������ �ʱ�ȭ ����)
//=====================================

//	��üȭ�� �ϰ�ʹٸ� �ؿ��� Ű��
//#define FULLSCREEN

//#ifdef FULLSCREEN
//#define WINSTARTX 0
//#define WINSTARTY 0
//#define WINSIZEX GetSystemMetrics(SM_CXSCREEN)
//#define WINSIZEY GetSystemMetrics(SM_CYSCREEN)
//#else 
//#define WINSTARTX 100
//#define WINSTARTY 0
#define WINSIZEX 800
#define WINSIZEY 600
//#endif // FULLSCREEN


//����, ���а���
#define grav_accerl 9.8f //Gravialional accerleration
#define PI 3.141592f
#define Radian (PI/180.0f)
#define SPEED 6



//===================================================
//	## �������� ## (�ν��Ͻ�, �������ڵ�, ���콺��ǥ)
//===================================================
// 
// ���߿� ����� ����
//extern HINSTANCE _hInstance;
//extern HWND _hWnd;
//extern POINT _ptMouse;