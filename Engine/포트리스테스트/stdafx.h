#pragma once

//공용 헤더
#include<Windows.h>
#include<math.h>
#include<time.h>
#include<chrono>
#include<cassert>


//STL
#include<vector>
#include<string>

//=====================================
//	## 내가 만든 구조체 이곳에 추가 ##
//=====================================

//구조체
struct Position
{
	float x;
	float y;
};

//=====================================
//	## 내가 만든 헤더파일 이곳에 추가 ##
//=====================================



//게임안 보여질 객체들
#include"Tank.h"
#include"Missile.h"



//충돌에 쓰일 벡터(cmath)
#include"vector.h"
//랜덤추출함수
#include"Random.h"

//싱글톤 생성
#include"Mouse.h"
#include"Camera.h"
#include"Turnmanager.h"

//=====================================
//	## 싱글톤 추가 ##
//=====================================
#define _Mouse Mouse::get_singleton()
#define _CAM Camera::get_singleton()
#define _Turn Turnmanager::get_singleton()

//=====================================
//	## 디파인문 ## (윈도우 초기화 셋팅)
//=====================================

//	전체화면 하고싶다면 밑에꺼 키자
//#define FULLSCREEN

//#ifdef FULLSCREEN
//#define WINSTARTX 0
//#define WINSTARTY 0
//#define WINSIZE_X GetSystemMetrics(SM_CXSCREEN)
//#define WINSIZE_Y GetSystemMetrics(SM_CYSCREEN)
//#else 
//#define WINSTARTX 100
//#define WINSTARTY 0
#define WINSIZE_X 800  //1280
#define WINSIZE_Y 600  //760
//#endif // FULLSCREEN


//게임 세팅
#define R_Image_SIZE 100
#define MAPSIZE_W	 1500
#define MAPSIZE_H	 800
#define PLAYERS		 8
#define TANK_HP		 1000
#define OUT_RANGE	 100
#define FIRE_MIN_Length	 15



//UI 세팅
#define UI_SCREEN_SCROLL	30
#define UI_H				110
#define UI_POWER_X			282
#define UI_POWER_Y			550
#define UI_POWER_H			 15
#define UI_POWER_MUL		 4
#define UI_ANGLE_CENTER_X		92
#define UI_ANGLE_CENTER_Y		534
#define UI_ANGLE_MIN_Length		8
#define UI_ANGLE_MAX_Length		 60



//물리, 수학관련
#define grav_accerl 9.8f //Gravialional accerleration
#define PI 3.141592f
#define Radian (PI/180.0f)
#define SPEED 6

//색상관련
#define Transparent_Color RGB(255, 0, 255)
#define Power_Color RGB(255, 0, 0)
#define GUIDE_ANGLE_Color RGB(255, 212, 0)



//===================================================
//	## 전역변수 ## (인스턴스, 윈도우핸들, 마우스좌표)
//===================================================
// 
// 나중에 사용해 보자
//extern HINSTANCE _hInstance;
//extern HWND _hWnd;

