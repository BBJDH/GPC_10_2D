#include"stdafx.h"

namespace Rendering
{
	namespace
	{
		HBITMAP htank_bit, hmissilebit,hbackground_bit, huibit, hmagentabit;

		HDC hmapdc;
	}//싱글톤으로 생성하여 외부 접근 못하게


	void drawbitmp(HDC const& hdc_dest,int const win_x, int const win_y,
		int const width,int const height,int const image_x, int const image_y, HBITMAP const& hbitmap)
	{
		HDC hbufferdc = CreateCompatibleDC(hdc_dest);
		HBITMAP oldbit = static_cast<HBITMAP>(SelectObject(hbufferdc, hbitmap));
		BitBlt(hdc_dest, win_x, win_y, width, height, hbufferdc, image_x, image_y, SRCCOPY);
		//윈도우에서 출력할 위치, 너비높이, 가져올 이미지의 시작점(왼쪽위)
		SelectObject(hbufferdc, oldbit);
		DeleteDC(hbufferdc);
	}
	void initialize(HWND const&  hwindow)
	{
		//HBRUSH hbrush = CreateSolidBrush(Transparent_Color);

		HDC hdc = GetDC(hwindow);
		HBITMAP hmapbit = CreateCompatibleBitmap(hdc, MAPSIZE_W, MAPSIZE_H+UI_H);
		hmapdc = CreateCompatibleDC(hdc);
		hmagentabit = CreateCompatibleBitmap(hdc, MAPSIZE_W, MAPSIZE_H+UI_H);
		htank_bit = CreateCompatibleBitmap(hdc, R_Image_SIZE, R_Image_SIZE);

		SelectObject(hmapdc, hmagentabit);

		hbackground_bit = static_cast<HBITMAP>(LoadImage
		(
			NULL,
			TEXT("./소스파일/포트리스/Asset/Background/background_800600.bmp"),
			IMAGE_BITMAP,
			0,
			0,
			LR_LOADFROMFILE | LR_DEFAULTSIZE
		));
		hmapbit = static_cast<HBITMAP>(LoadImage
		(
			NULL,
			TEXT("./소스파일/포트리스/Asset/Map/sky_M_1500800.bmp"),
			IMAGE_BITMAP,
			0,
			0,
			LR_LOADFROMFILE | LR_DEFAULTSIZE
		));
		huibit = static_cast<HBITMAP>(LoadImage
		(
			NULL,
			TEXT("./소스파일/포트리스/인터페이스_800600.bmp"),
			IMAGE_BITMAP,
			0,
			0,
			LR_LOADFROMFILE | LR_DEFAULTSIZE
		));
		htank_bit = static_cast<HBITMAP>(LoadImage
		(
			NULL,
			TEXT("./소스파일/포트리스/뉴포트리스/캐논/M_Canon_Tank_Right.bmp"),
			IMAGE_BITMAP,
			0,
			0,
			LR_LOADFROMFILE | LR_DEFAULTSIZE
		));
		//GetObject(htank_bit, sizeof(BITMAP), &fighter);
		hmissilebit = static_cast<HBITMAP>(LoadImage
		(
			NULL,
			TEXT("./소스파일/포트리스/bomb.bmp"),
			IMAGE_BITMAP,
			0,
			0,
			LR_LOADFROMFILE | LR_DEFAULTSIZE
		));
		BITMAP mapbit;
		GetObject(hmapbit, sizeof(BITMAP), &mapbit);


		drawbitmp(hmapdc, 0, 0, mapbit.bmWidth, mapbit.bmHeight, 0,0, hmapbit);			//맵 파일 그리기

		DeleteObject(hmapbit);
		ReleaseDC(hwindow, hdc);

	}
	void drawbitmp_transparent(HDC const& hdc_dest,int const x,int const y,
		BITMAP const& bit_src, HBITMAP const& hbitmp)
	{
		HDC hmemdc = CreateCompatibleDC(hdc_dest);
		HBITMAP oldbit = static_cast<HBITMAP>(SelectObject(hmemdc,hbitmp));

		TransparentBlt(hdc_dest,x,y,bit_src.bmWidth,bit_src.bmHeight, hmemdc,
			0,0, bit_src.bmWidth, bit_src.bmHeight,Transparent_Color);
		SelectObject(hmemdc,oldbit);
		DeleteDC(hmemdc);
	}

	bool sizeup_and_draw_r_a(HDC const hdc, HBITMAP const hBmp, unsigned const window_x,unsigned const window_y, POINT const * vertex, unsigned const size=3)
	{

		// 1. 가상의 도화지를 만들고(100X100) 전체를 마젠타로 칠하고
		// 2. 받은 정점만큼 이미지를 회전해서 출력하고
		// 3. 최종 그려질 윈도우 좌표에 마젠타를 지우고 가져다 놓는다
		HDC hMemdc;
		HDC himagedc;
		HBITMAP hOldBmp,tempbmp;
		BITMAP    bitmap;
		GetObject(hBmp, sizeof(BITMAP), &bitmap);

		hMemdc = CreateCompatibleDC(hdc);
		himagedc = CreateCompatibleDC(hdc);
		tempbmp = CreateCompatibleBitmap(hdc, R_Image_SIZE, R_Image_SIZE);
		SelectObject(hMemdc, tempbmp);

		HBRUSH brush = CreateSolidBrush(Transparent_Color);
		hOldBmp = static_cast<HBITMAP>(SelectObject(hMemdc, brush));
		PatBlt(hMemdc, 0, 0, R_Image_SIZE , R_Image_SIZE , PATCOPY);	//마젠타로 100X100 도화지 전체 칠하기
		SelectObject(hMemdc, hOldBmp);
		DeleteObject(tempbmp);
		DeleteObject(brush);

		hOldBmp = static_cast<HBITMAP>(SelectObject(himagedc, hBmp));
		bool result = PlgBlt(hMemdc, vertex, himagedc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, 0, 0, 0);		//정점만큼 이미지 회전
		GdiTransparentBlt(hdc, window_x- bitmap.bmWidth, window_y- bitmap.bmHeight, R_Image_SIZE, R_Image_SIZE,		//마젠타 지우고 지정된 좌표에 출력
			hMemdc, 0, 0, R_Image_SIZE, R_Image_SIZE,  Transparent_Color);

		SelectObject(himagedc, hOldBmp);
		DeleteObject(hOldBmp);
		DeleteDC(hMemdc);
		DeleteDC(himagedc);

		return result;
	}

	bool drawbitmp_rotate_alpha(HDC const hdc, HBITMAP const hbmp,double const angle,
		float const half_width, float const half_height,float const window_x, float const window_y)
	{
		POINT     vertex[3]    = { 0 };
		double	  half_w  = static_cast<double>(half_width);
		double	  half_h  = static_cast<double>(half_height);
		//double	  radius  = sqrt( pow(half_w,2)+pow(half_h,2));
		double x, y, dest_x, dest_y, cosVal, sinVal;
		cosVal = cos(angle*Radian), sinVal = sin(angle*Radian);

		// 1. 중점을 기준으로 상대좌표를 구하고(3개 왼위 오위 왼아래)
		// 2. 회전된좌표(상대좌표)를 얻은 후 
		// 3. 가상의 도화지 중점에 상대좌표를 더해 그리는 함수에게 전달(sizeup_and_draw_r_a)
 		for (size_t i = 0; i < 3; i++)
		{
			if (i == 0) { x = -half_w, y = -half_h; }    // left up  꼭지점 부분(윈도우 좌표계)
			else if (i == 1) { x = half_w, y = -half_h; }  // right up 꼭지점 부분(윈도우 좌표계)
			else if (i == 2) { x = -half_w, y = half_h; } // left low 꼭지점 부분(윈도우 좌표계)
			dest_x = x * cosVal - y * sinVal;
			dest_y = x * sinVal + y * cosVal; //회전한 좌표 구하기


			vertex[i].x = R_Image_SIZE/2 + static_cast<long>(dest_x);
			vertex[i].y = R_Image_SIZE/2 + static_cast<long>(dest_y); // 이미지중점에서 회전한 좌표 더함
		}
		bool result = sizeup_and_draw_r_a(hdc,hbmp,static_cast<int const>(window_x),static_cast<int const>(window_y),vertex);

		return result;
	}
	void draw_object(HDC const hdc, Object const& obj) //카메라만큼 밀어서 출력
	{
		int const camx = static_cast<int const>(_CAM->pos.x);
		int const camy = static_cast<int const>(_CAM->pos.y);
		drawbitmp_rotate_alpha
		(
			hdc,htank_bit,
			obj.getimage_angle(),
			obj.getwidth()/2.0f,
			obj.getheight() /2.0f,
			obj.getpos().x-camx,
			obj.getpos().y-camy
		);
	}
	void draw_tanks(HDC const hdc,std::vector<Tank> const & tank)
	{

		if (!tank.empty())								//오브젝트 그리기(개수만큼)
		{
			for (size_t i = 0; i < tank.size(); i++)
			{
				draw_object(hdc,tank[i]);
			}
		}
	}
	void draw_missiles(HDC const hdc,std::vector<Missile> const & missile)
	{

		if (!missile.empty())								//오브젝트 그리기(개수만큼)
		{
			for (size_t i = 0; i < missile.size(); i++)
			{
				draw_object(hdc,missile[i]);
			}
		}
	}
	void ui_angle_line(HDC const hdc, float const angle)
	{
		unsigned min_x = UI_ANGLE_MIN_Length;
		unsigned min_y = UI_ANGLE_CENTER_Y;
		unsigned max_x = UI_ANGLE_MAX_Length;
		unsigned max_y = UI_ANGLE_CENTER_Y;

		MoveToEx(hdc, UI_ANGLE_CENTER_X+UI_ANGLE_MIN_Length, UI_ANGLE_CENTER_Y, NULL);
		LineTo(hdc, UI_ANGLE_CENTER_X+UI_ANGLE_MAX_Length,UI_ANGLE_CENTER_Y);
	}

	void draw_ui(HDC const hdc,std::vector<Tank> const & tank)
	{
		BITMAP bmp;
		GetObject(huibit, sizeof(BITMAP), &bmp);
		drawbitmp_transparent(hdc, 0, 0, bmp, huibit);	



		HBRUSH hNewBrush = CreateSolidBrush(Power_Color);
		HPEN hNewPen = CreatePen(PS_SOLID, 2, Power_Color);
		HBITMAP hOldBmp = static_cast<HBITMAP>(SelectObject(hdc, hNewBrush));
		SelectObject(hdc, hNewPen);

		Rectangle(hdc, UI_POWER_X, UI_POWER_Y,
			UI_POWER_X +tank[_Turn->whosturn()].getpower()* UI_POWER_MUL, UI_POWER_Y+ UI_POWER_H); //파워게이지
		//Rectangle(hdc,92,  535, 92+10,535+10);
		//UI_angle(hdc, tank[_Turn->whosturn()]);

		SelectObject(hdc, hOldBmp);
		DeleteObject(hNewBrush);
		DeleteObject(hNewPen);


	}
	void update(HWND const& hwindow, std::vector<Tank> const & tank,bool const magenta_switch)
	{
		HDC hdc = GetDC(hwindow);
		HDC hvirtualdc = CreateCompatibleDC(hdc);
		HBITMAP hvirtualbit = CreateCompatibleBitmap(hdc, WINSIZE_X, WINSIZE_Y);
		BITMAP bmp;
		int const camx = static_cast<int const>(_CAM->pos.x);
		int const camy = static_cast<int const>(_CAM->pos.y);

		SelectObject(hvirtualdc, hvirtualbit);

		drawbitmp(hvirtualdc,0, 0, WINSIZE_X, WINSIZE_Y,
			0,0, hbackground_bit);								//배경 파일 그리기

		GetObject(hmagentabit, sizeof(BITMAP), &bmp);
		TransparentBlt(hvirtualdc, 0, 0, WINSIZE_X, WINSIZE_Y,
			hmapdc,camx, camy, WINSIZE_X, WINSIZE_Y,
			Transparent_Color);									//맵 그리기
		draw_tanks(hvirtualdc,tank);							//탱크들 그리기	

																//미사일들 그리기
		draw_ui(hvirtualdc,tank);								//UI 그리기




#pragma region 그래픽 디버깅

		if (!tank.empty())																	// 좌표디버깅							
		{
			SetBkMode(hvirtualdc, TRANSPARENT);
			SetTextColor(hvirtualdc, RGB(255, 255, 255));


			//std::string temp = "m_x :" + std::to_string(_Mouse->x + _CAM->pos.x);			//마우스x좌표
			std::string temp = "w_x :" + std::to_string(_Mouse->x);							//마우스스크린x좌표
			TextOut(hvirtualdc, 0, 0, temp.c_str(), static_cast<int>(temp.size()));
			//temp = "m_y :" + std::to_string(_Mouse->y + _CAM->pos.y);						//마우스y좌표
			temp = "w_y :" + std::to_string(_Mouse->y);										//마우스스크린y좌표
			TextOut(hvirtualdc, 150, 0, temp.c_str(), static_cast<int>(temp.size()));
			temp = "tank_x :" + std::to_string(tank[_Turn->whosturn()].getpos().x);			//탱크x좌표
			TextOut(hvirtualdc, 370, 0, temp.c_str(), static_cast<int>(temp.size()));
			temp = "tank_y :" + std::to_string(tank[_Turn->whosturn()].getpos().y);			//탱크y좌표
			TextOut(hvirtualdc, 520, 0, temp.c_str(), static_cast<int>(temp.size()));
			temp = "power :" + std::to_string(tank[_Turn->whosturn()].getpower());					//자세각도
			//temp = "angle :" + std::to_string(tank.back().getimage_angle());					//자세각도
			//temp = "turn :" + std::to_string(_Turn->whosturn());					//턴
			TextOut(hvirtualdc, 680, 0, temp.c_str(), static_cast<int>(temp.size()));
		}

		if (magenta_switch)																	// 충돌디버깅
			BitBlt(hdc, 0, 0, WINSIZE_X, WINSIZE_Y, hmapdc, camx, camy, SRCCOPY);
		else
			BitBlt(hdc, 0, 0, WINSIZE_X, WINSIZE_Y, hvirtualdc, 0, 0, SRCCOPY);

#pragma endregion

		DeleteDC(hvirtualdc);
		DeleteObject(hvirtualbit);
		ReleaseDC(hwindow, hdc);
	}

	void destroy()
	{
		DeleteObject(huibit);
		DeleteObject(hmissilebit);
		DeleteObject(htank_bit);
		DeleteObject(hmagentabit);
		DeleteObject(hbackground_bit);
	}


	//TODO: 마젠타 맵 싱글톤으로 만들기
	HDC  getmapdc()
	{
		return hmapdc;
	}
	HBITMAP getmapbit()
	{
		return hmagentabit;
	}



	//https://doggyfoot.tistory.com/52
	//스타크래프트 리소스
	// 
	// 
	//삽질..(도화지 크게 그려서 몽땅 그려놓고 옮겨옴)
	//void update(HWND const& hwindow, std::vector<Tank> const & obj,bool const magenta_switch)
	//{
	//	HDC hdc = GetDC(hwindow);
	//	HDC hvirtualdc = CreateCompatibleDC(hdc);
	//	HBITMAP hvirtualbit = CreateCompatibleBitmap(hdc, MAPSIZE_W, MAPSIZE_H+UI_H);
	//	BITMAP bmp;

	//	SelectObject(hvirtualdc, hvirtualbit);

	//	drawbitmp(hvirtualdc,static_cast<int const>(_CAM->pos.x), static_cast<int const>(_CAM->pos.y), WINSIZE_X, WINSIZE_Y,
	//		0,0, hbackground_bit);			//배경 파일 그리기
	//	GetObject(hmagentabit, sizeof(BITMAP), &bmp);

	//	TransparentBlt(hvirtualdc, 0, 0, MAPSIZE_W, MAPSIZE_H, hmapdc,
	//		0, 0, MAPSIZE_W, MAPSIZE_H, Transparent_Color);
	//	////Rectangle(hvirtualdc,0,500,WINSIZE_X,WINSIZE_Y);

	//	if (!obj.empty())								//오브젝트 그리기(개수만큼)
	//	{
	//		for (size_t i = 0; i < obj.size(); i++)
	//		{
	//			//drawbitmp_transparent(hvirtualdc, static_cast<const int>(obj[i].getpos().x) - (fighter.bmWidth / 2),
	//			//	static_cast<const int>(obj[i].getpos().y) - (fighter.bmHeight / 2), fighter, htank_bit);	
	//			RotateSizingImage(hvirtualdc,htank_bit,obj[i].getimage_angle(),obj[i].getwidth()/2, obj[i].getheight() /2,
	//				static_cast<const int>(obj[i].getpos().x),
	//				static_cast<const int>(obj[i].getpos().y));
	//			Ellipse(hvirtualdc, 
	//				static_cast<const int>(obj[i].getpos().x - 2),
	//				static_cast<const int>(obj[i].getpos().y+ obj[i].getheight() / 2 - 2),
	//				static_cast<const int>(obj[i].getpos().x + 2),
	//				static_cast<const int>(obj[i].getpos().y+ obj[i].getheight() / 2 + 2));
	//		}
	//	}
	//	GetObject(huibit, sizeof(BITMAP), &bmp);
	//	drawbitmp_transparent(hvirtualdc, static_cast<int const>(_CAM->pos.x), static_cast<int const>(_CAM->pos.y), bmp, huibit);

	//	if (!obj.empty())								//오브젝트 그리기(개수만큼)
	//	{
	//		SetBkMode(hvirtualdc, TRANSPARENT);
	//		SetTextColor(hvirtualdc, RGB(255, 255, 255));
	//		//std::string temp = "x :" + std::to_string(_CAM->pos.x);		//마우스x좌표
	//		//TextOut(hvirtualdc, 0, 0, temp.c_str(), static_cast<int>(temp.size()));
	//		//temp = "y :" + std::to_string(_CAM->pos.y);					//마우스y좌표
	//		//TextOut(hvirtualdc, 100, 0, temp.c_str(), static_cast<int>(temp.size()));

	//		std::string temp = "m_x :" + std::to_string(_Mouse->x+_CAM->pos.x);					//마우스y좌표
	//		TextOut(hvirtualdc, static_cast<int const>(_CAM->pos.x)+0, static_cast<int const>(_CAM->pos.y), temp.c_str(), static_cast<int>(temp.size()));
	//		temp = "m_y :" + std::to_string(_Mouse->y+_CAM->pos.y);					//마우스y좌표
	//		TextOut(hvirtualdc, static_cast<int const>(_CAM->pos.x)+150, static_cast<int const>(_CAM->pos.y), temp.c_str(), static_cast<int>(temp.size()));

	//		temp = "tank_x :" + std::to_string(obj.back().getpos().x);		//탱크x좌표
	//		TextOut(hvirtualdc, static_cast<int const>(_CAM->pos.x)+370, static_cast<int const>(_CAM->pos.y), temp.c_str(), static_cast<int>(temp.size()));
	//		temp = "tank_y :" + std::to_string(obj.back().getpos().y);		//탱크y좌표
	//		TextOut(hvirtualdc, static_cast<int const>(_CAM->pos.x)+520, static_cast<int const>(_CAM->pos.y), temp.c_str(), static_cast<int>(temp.size()));
	//		temp = "angle :" + std::to_string(obj.back().getimage_angle());									//버틴시간 텍스트
	//		TextOut(hvirtualdc, static_cast<int const>(_CAM->pos.x)+680, static_cast<int const>(_CAM->pos.y), temp.c_str(), static_cast<int>(temp.size()));
	//	}

	//	if(magenta_switch)
	//		BitBlt(hdc, 0,0, WINSIZE_X, WINSIZE_Y, hmapdc, static_cast<int const>(_CAM->pos.x), static_cast<int const>(_CAM->pos.y), SRCCOPY);
	//	else
	//		BitBlt(hdc, 0,0, WINSIZE_X, WINSIZE_Y, hvirtualdc,static_cast<int const>(_CAM->pos.x), static_cast<int const>(_CAM->pos.y), SRCCOPY);


	//	DeleteDC(hvirtualdc);
	//	DeleteObject(hvirtualbit);
	//	ReleaseDC(hwindow, hdc);
	//}


}
//Ellipse함수 - 설정한 박스영역에 맞는 원을 그려줌
//Arc함수 - 설정된 영역에 그리기 시작좌표(x, y)에서 종료지점(x, y)까지 원호를 그려줌
//Chord함수 - 현을 그려줌
//Pie함수 - 부채꼴을 그려줌


