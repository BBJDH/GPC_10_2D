#pragma once

//공용 헤더
#include<Windows.h>
#include<math.h>
#include<time.h>
#include<chrono>


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


//충돌에 쓰일 벡터(cmath)
#include"vector.h"

//싱글톤 생성
#include"Camera.h"

//=====================================
//	## 싱글톤 추가 ##
//=====================================
#define _CAM Camera::get_singleton()


//=====================================
//	## 디파인문 ## (윈도우 초기화 셋팅)
//=====================================

//	전체화면 하고싶다면 밑에꺼 키자
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


//물리, 수학관련
#define grav_accerl 9.8f //Gravialional accerleration
#define PI 3.141592f
#define Radian (PI/180.0f)
#define SPEED 6



//===================================================
//	## 전역변수 ## (인스턴스, 윈도우핸들, 마우스좌표)
//===================================================
// 
// 나중에 사용해 보자
//extern HINSTANCE _hInstance;
//extern HWND _hWnd;
//extern POINT _ptMouse;