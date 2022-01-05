#include<Windows.h>
#include<vector>
#include<string>
#include"Object.h"

namespace Rendering
{
	namespace
	{
		HBITMAP hmapbit, htank_bit, hmissilebit,hbackground_bit,hmagentabit;
		BITMAP fighter, missile, over;
		HDC hmapdc;
	}

	BITMAP const getbitmap()
	{
		return fighter;
	}

	void drawbitmp(HDC const& hdc_dest,int const x, int const y,
		int const width,int const height,HBITMAP const& hbitmap)
	{
		HDC hbufferdc = CreateCompatibleDC(hdc_dest);
		HBITMAP oldbit = static_cast<HBITMAP>(SelectObject(hbufferdc, hbitmap));
		BitBlt(hdc_dest, 0, 0, 800, 600, hbufferdc, 0, 0, SRCCOPY);
		SelectObject(hbufferdc, oldbit);
		DeleteDC(hbufferdc);
	}
	void initialize(HWND const&  hwindow)
	{
		//HBRUSH hbrush = CreateSolidBrush(RGB(255, 0, 255));

		HDC hdc = GetDC(hwindow);
		hmapdc = CreateCompatibleDC(hdc);
		hmapbit = CreateCompatibleBitmap(hdc, 800, 600);
		hmagentabit = CreateCompatibleBitmap(hdc, 800, 600);
		htank_bit = CreateCompatibleBitmap(hdc, 50, 50);

		SelectObject(hmapdc, hmagentabit);

		hmapbit = static_cast<HBITMAP>(LoadImage
		(
			NULL,
			TEXT("./소스파일/포트리스/Asset/Map/sky_M_800600.bmp"),
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
		GetObject(htank_bit, sizeof(BITMAP), &fighter);
		hmissilebit = static_cast<HBITMAP>(LoadImage
		(
			NULL,
			TEXT("./소스파일/missile.bmp"),
			IMAGE_BITMAP,
			0,
			0,
			LR_LOADFROMFILE | LR_DEFAULTSIZE
		));
		GetObject(hmissilebit, sizeof(BITMAP), &missile);
		hbackground_bit = static_cast<HBITMAP>(LoadImage
		(
			NULL,
			TEXT("./소스파일/포트리스/Asset/Background/background_800600.bmp"),
			IMAGE_BITMAP,
			0,
			0,
			LR_LOADFROMFILE | LR_DEFAULTSIZE
		));
		GetObject(hbackground_bit, sizeof(BITMAP), &over);

		drawbitmp(hmapdc, 0, 0, 800, 600, hmapbit);			//맵 파일 그리기


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

	void update(HWND const& hwindow, std::vector<Object> const & obj,bool const magenta_switch)
	{
		HDC hdc = GetDC(hwindow);
		HDC hvirtualdc = CreateCompatibleDC(hdc);
		HBITMAP hvirtualbit = CreateCompatibleBitmap(hdc, 800, 600);
		SelectObject(hvirtualdc, hvirtualbit);

		drawbitmp(hvirtualdc,0,0,800,600, hbackground_bit);			//배경 파일 그리기

		TransparentBlt(hvirtualdc, 0, 0, 800, 600, hmapdc,
			0, 0, 800, 600, RGB(255, 0, 255));
		//Rectangle(hvirtualdc,0,500,800,600);

		if (!obj.empty())								//오브젝트 그리기(개수만큼)
		{
			for (size_t i = 0; i < obj.size(); i++)
			{
				drawbitmp_transparent(hvirtualdc, static_cast<const int>(obj[i].getpos().x) - (fighter.bmWidth / 2),
					static_cast<const int>(obj[i].getpos().y) - (fighter.bmHeight / 2), fighter, htank_bit);	
			}
		}
		if(magenta_switch)
			BitBlt(hdc, 0, 0, 800, 600, hmapdc, 0, 0, SRCCOPY);					//다그린그림 옮겨그리기
		else
			BitBlt(hdc, 0, 0, 800, 600, hvirtualdc, 0, 0, SRCCOPY);					//다그린그림 옮겨그리기


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

}