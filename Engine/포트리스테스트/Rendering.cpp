

#include"stdafx.h"

namespace Rendering
{
	namespace
	{
		HBITMAP hmapbit, htank_bit, hmissilebit,hbackground_bit, huibit, hmagentabit;

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
		//HBRUSH hbrush = CreateSolidBrush(RGB(255, 0, 255));

		HDC hdc = GetDC(hwindow);
		hmapdc = CreateCompatibleDC(hdc);
		hmapbit = CreateCompatibleBitmap(hdc, MAPSIZE_W, MAPSIZE_H);
		hmagentabit = CreateCompatibleBitmap(hdc, MAPSIZE_W, MAPSIZE_H);
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
			TEXT("./소스파일/missile.bmp"),
			IMAGE_BITMAP,
			0,
			0,
			LR_LOADFROMFILE | LR_DEFAULTSIZE
		));
		BITMAP mapbit;
		GetObject(hmapbit, sizeof(BITMAP), &mapbit);


		drawbitmp(hmapdc, 0, 0, mapbit.bmWidth, mapbit.bmHeight, 0,0, hmapbit);			//맵 파일 그리기


		ReleaseDC(hwindow, hdc);

	}
	void drawbitmp_transparent(HDC const& hdc_dest,int const x,int const y,
		BITMAP const& bit_src, HBITMAP const& hbitmp)
	{
		HDC hmemdc = CreateCompatibleDC(hdc_dest);
		HBITMAP oldbit = static_cast<HBITMAP>(SelectObject(hmemdc,hbitmp));

		TransparentBlt(hdc_dest,x,y,bit_src.bmWidth,bit_src.bmHeight, hmemdc,
			0,0, bit_src.bmWidth, bit_src.bmHeight,RGB(255,0,255));
		SelectObject(hmemdc,oldbit);
		DeleteDC(hmemdc);
	}

	BOOL RotateSizingImage(HDC const hdc, HBITMAP const hBmp,
		double const dblAngle,
		int    const ixRotateAxis, int const iyRotateAxis,
		int    const ixDisplay,    int const iyDisplay)
	{
		BITMAP    bitmap;
		POINT     vertex[3]    = { 0 };
		GetObject(hBmp, sizeof(BITMAP), &bitmap);
		double	  bmpwidth  = static_cast<double>(bitmap.bmWidth);
		double	  bmpheight = static_cast<double>(bitmap.bmHeight);
		double	  ixRotate  = static_cast<double>(ixRotateAxis);
		double	  iyRotate  = static_cast<double>(iyRotateAxis);
		double dblx, dbly, dest_x, dest_y, cosVal, sinVal;
		cosVal = cos(-dblAngle*Radian), sinVal = sin(-dblAngle*Radian);

		// 1. 회전축을 기준으로 상대좌표를 구하고
		// 2. 회전후 위치좌표(상대좌표)를 얻은 후
		// 3. 얻은 값을 원래의 좌표에 적용.
 		for (size_t i = 0; i < 3; i++)
		{
			if (i == 0) { dblx = -ixRotate, dbly = -iyRotate; }    // left up  꼭지점 부분
			else if (i == 1) { dblx = bmpwidth - ixRotate, dbly = -iyRotate; }  // right up 꼭지점 부분
			else if (i == 2) { dblx = -ixRotate, dbly = bmpheight - iyRotate; } // left low 꼭지점 부분
			dest_x = dblx * cosVal - dbly * sinVal;
			dest_y = dblx * sinVal + dbly * cosVal;
			dest_x += ixRotate, dest_y += iyRotate;
			vertex[i].x = 50 - static_cast<long>(ixRotate) + static_cast<long>(dest_x);
			vertex[i].y = 50 - static_cast<long>(iyRotate) + static_cast<long>(dest_y);
		}

		HDC hMemdc;
		HDC himagedc;
		HBITMAP hOldBmp,tempbmp;
		hMemdc = CreateCompatibleDC(hdc);
		himagedc = CreateCompatibleDC(hdc);
		tempbmp = CreateCompatibleBitmap(hdc, R_Image_SIZE, R_Image_SIZE);
		SelectObject(hMemdc, tempbmp);

		HBRUSH brush = CreateSolidBrush(RGB(255, 0, 255));
		hOldBmp = static_cast<HBITMAP>(SelectObject(hMemdc, brush));
		PatBlt(hMemdc, 0, 0, R_Image_SIZE , R_Image_SIZE , PATCOPY);
		SelectObject(hMemdc, hOldBmp);
		DeleteObject(brush);


		hOldBmp = static_cast<HBITMAP>(SelectObject(himagedc, hBmp));
		BOOL result = PlgBlt(hMemdc, vertex, himagedc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, 0, 0, 0);
		GdiTransparentBlt(hdc, ixDisplay- bitmap.bmWidth, iyDisplay- bitmap.bmHeight, R_Image_SIZE, R_Image_SIZE,
			hMemdc, 0, 0, R_Image_SIZE, R_Image_SIZE,  RGB(255, 0, 255));

		SelectObject(himagedc, hOldBmp);
		DeleteObject(tempbmp);
		DeleteObject(hOldBmp);
		DeleteDC(hMemdc);
		DeleteDC(himagedc);
		return result;
	}

	void update(HWND const& hwindow, std::vector<Tank> const & obj,bool const magenta_switch)
	{
		HDC hdc = GetDC(hwindow);
		HDC hvirtualdc = CreateCompatibleDC(hdc);
		HBITMAP hvirtualbit = CreateCompatibleBitmap(hdc, MAPSIZE_W, MAPSIZE_H+UI_H);
		BITMAP bmp;

		SelectObject(hvirtualdc, hvirtualbit);

		drawbitmp(hvirtualdc,static_cast<int const>(_CAM->pos.x), static_cast<int const>(_CAM->pos.y), WINSIZE_X, WINSIZE_Y,
			0,0, hbackground_bit);			//배경 파일 그리기
		GetObject(hmagentabit, sizeof(BITMAP), &bmp);

		TransparentBlt(hvirtualdc, 0, 0, MAPSIZE_W, MAPSIZE_H, hmapdc,
			0, 0, MAPSIZE_W, MAPSIZE_H, RGB(255, 0, 255));
		////Rectangle(hvirtualdc,0,500,WINSIZE_X,WINSIZE_Y);

		if (!obj.empty())								//오브젝트 그리기(개수만큼)
		{
			for (size_t i = 0; i < obj.size(); i++)
			{
				//drawbitmp_transparent(hvirtualdc, static_cast<const int>(obj[i].getpos().x) - (fighter.bmWidth / 2),
				//	static_cast<const int>(obj[i].getpos().y) - (fighter.bmHeight / 2), fighter, htank_bit);	
				RotateSizingImage(hvirtualdc,htank_bit,obj[i].getimage_angle(),obj[i].getwidth()/2, obj[i].getheight() /2,
					static_cast<const int>(obj[i].getpos().x),
					static_cast<const int>(obj[i].getpos().y));
				Ellipse(hvirtualdc, 
					static_cast<const int>(obj[i].getpos().x - 2),
					static_cast<const int>(obj[i].getpos().y+ obj[i].getheight() / 2 - 2),
					static_cast<const int>(obj[i].getpos().x + 2),
					static_cast<const int>(obj[i].getpos().y+ obj[i].getheight() / 2 + 2));
			}
		}
		GetObject(huibit, sizeof(BITMAP), &bmp);
		drawbitmp_transparent(hvirtualdc, static_cast<int const>(_CAM->pos.x), static_cast<int const>(_CAM->pos.y), bmp, huibit);

		if (!obj.empty())								//오브젝트 그리기(개수만큼)
		{
			SetBkMode(hvirtualdc, TRANSPARENT);
			SetTextColor(hvirtualdc, RGB(255, 255, 255));
			//std::string temp = "x :" + std::to_string(_CAM->pos.x);		//마우스x좌표
			//TextOut(hvirtualdc, 0, 0, temp.c_str(), static_cast<int>(temp.size()));
			//temp = "y :" + std::to_string(_CAM->pos.y);					//마우스y좌표
			//TextOut(hvirtualdc, 100, 0, temp.c_str(), static_cast<int>(temp.size()));

			std::string temp = "m_x :" + std::to_string(_Mouse->x+_CAM->pos.x);					//마우스y좌표
			TextOut(hvirtualdc, static_cast<int const>(_CAM->pos.x)+0, static_cast<int const>(_CAM->pos.y), temp.c_str(), static_cast<int>(temp.size()));
			temp = "m_y :" + std::to_string(_Mouse->y+_CAM->pos.y);					//마우스y좌표
			TextOut(hvirtualdc, static_cast<int const>(_CAM->pos.x)+150, static_cast<int const>(_CAM->pos.y), temp.c_str(), static_cast<int>(temp.size()));

			temp = "tank_x :" + std::to_string(obj.back().getpos().x);		//탱크x좌표
			TextOut(hvirtualdc, static_cast<int const>(_CAM->pos.x)+370, static_cast<int const>(_CAM->pos.y), temp.c_str(), static_cast<int>(temp.size()));
			temp = "tank_y :" + std::to_string(obj.back().getpos().y);		//탱크y좌표
			TextOut(hvirtualdc, static_cast<int const>(_CAM->pos.x)+520, static_cast<int const>(_CAM->pos.y), temp.c_str(), static_cast<int>(temp.size()));
			temp = "angle :" + std::to_string(obj.back().getimage_angle());									//버틴시간 텍스트
			TextOut(hvirtualdc, static_cast<int const>(_CAM->pos.x)+680, static_cast<int const>(_CAM->pos.y), temp.c_str(), static_cast<int>(temp.size()));
		}

		if(magenta_switch)
			BitBlt(hdc, 0,0, WINSIZE_X, WINSIZE_Y, hmapdc, static_cast<int const>(_CAM->pos.x), static_cast<int const>(_CAM->pos.y), SRCCOPY);
		else
			BitBlt(hdc, 0,0, WINSIZE_X, WINSIZE_Y, hvirtualdc,static_cast<int const>(_CAM->pos.x), static_cast<int const>(_CAM->pos.y), SRCCOPY);


		DeleteDC(hvirtualdc);
		DeleteObject(hvirtualbit);
		ReleaseDC(hwindow, hdc);
	}

	void destroy()
	{
		DeleteObject(hmagentabit);
		DeleteObject(hmapbit);
		DeleteObject(htank_bit);
		DeleteObject(hmissilebit);
		DeleteObject(hbackground_bit);
	}

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

}