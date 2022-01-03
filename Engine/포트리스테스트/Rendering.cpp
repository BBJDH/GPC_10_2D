#include<Windows.h>
#include<vector>
#include<string>
#include"Object.h"

namespace Rendering
{
	namespace
	{
		HBITMAP hmapbit, hfighterbit, hmissilebit,hgameoverbit;
		BITMAP fighter, missile, over;
		HDC hmapdc;
	}

	BITMAP const getbitmap()
	{
		return fighter;
	}

	void initialize(HWND const&  hwindow)
	{
		HDC hdc = GetDC(hwindow);
		hmapbit = CreateCompatibleBitmap(hdc, 800, 600);
		hfighterbit = CreateCompatibleBitmap(hdc, 50, 50);
		
		//
		//hmapdc = CreateCompatibleDC(hdc);
		//HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 255));
		//HBRUSH oldBrush = (HBRUSH)SelectObject(hmapdc, myBrush);

		//HBITMAP hvirtualbit = CreateCompatibleBitmap(hmapdc, 800, 600);
		//SelectObject(hmapdc, hvirtualbit);

		//Rectangle(hmapdc, 0, 0, 800, 600);


		hmapbit = static_cast<HBITMAP>(LoadImage
		(
			NULL,
			TEXT("./소스파일/Stars-background/starfield_alpha.bmp"),
			IMAGE_BITMAP,
			0,
			0,
			LR_LOADFROMFILE | LR_DEFAULTSIZE
		));
		hfighterbit = static_cast<HBITMAP>(LoadImage
		(
			NULL,
			TEXT("./소스파일/포트리스/Asset/뉴포트리스/탱크3 2픽셀.bmp"),
			IMAGE_BITMAP,
			0,
			0,
			LR_LOADFROMFILE | LR_DEFAULTSIZE
		));
		GetObject(hfighterbit, sizeof(BITMAP), &fighter);
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
		hgameoverbit = static_cast<HBITMAP>(LoadImage
		(
			NULL,
			TEXT("./소스파일/ckwlghd12/GameOver2.bmp"),
			IMAGE_BITMAP,
			0,
			0,
			LR_LOADFROMFILE | LR_DEFAULTSIZE
		));
		GetObject(hgameoverbit, sizeof(BITMAP), &over);

		//DeleteObject(hvirtualbit);
		//SelectObject(hmapdc, oldBrush);
		//DeleteObject(myBrush);
		ReleaseDC(hwindow, hdc);

	}
	void drawbitmp_transparent(HDC const& hdc_dest,int const x,int const y,
		BITMAP const& bit_src, HBITMAP const& hbitmp)
	{
		HDC hmemdc = CreateCompatibleDC(hdc_dest);
		HBITMAP oldbit = static_cast<HBITMAP>(SelectObject(hmemdc,hbitmp));

		TransparentBlt(hdc_dest,x,y,bit_src.bmWidth,bit_src.bmHeight, hmemdc,0,0, bit_src.bmWidth, bit_src.bmHeight,RGB(255,255,255));
		SelectObject(hmemdc,oldbit);
		DeleteDC(hmemdc);

	}
	void drawbitmp(HDC const& hdc_dest,int const x, int const y,
		int const width,int const height,HBITMAP const& hbitmap)
	{
		HDC hbufferdc = CreateCompatibleDC(hdc_dest);
		HBITMAP oldbit = static_cast<HBITMAP>(SelectObject(hbufferdc, hmapbit));
		BitBlt(hdc_dest, 0, 0, 800, 600, hbufferdc, 0, 0, SRCCOPY);
		SelectObject(hbufferdc, oldbit);
		DeleteDC(hbufferdc);
	}

	void update(HWND const& hwindow, std::vector<Object> const & obj)
	{
		HDC hdc = GetDC(hwindow);
		HDC hvirtualdc = CreateCompatibleDC(hdc);
		HBITMAP hvirtualbit = CreateCompatibleBitmap(hdc, 800, 600);
		SelectObject(hvirtualdc, hvirtualbit);

		//drawbitmp(hvirtualdc,0,0,800,600,hmapbit);			//맵 파일 그리기
		//Rectangle(hvirtualdc,0,500,800,600);
		Ellipse(hvirtualdc, 0, 500, 250, 600);
		Ellipse(hvirtualdc, 250, 500, 500, 600);
		Ellipse(hvirtualdc, 500, 500, 800, 600);
		if (!obj.empty())								//미사일 그리기(개수만큼)
		{
			for (size_t i = 0; i < obj.size(); i++)
			{
				drawbitmp_transparent(hvirtualdc, static_cast<const int>(obj[i].getpos().x) - (fighter.bmWidth / 2),
					static_cast<const int>(obj[i].getpos().y) - (fighter.bmHeight / 2), fighter, hfighterbit);	//비행기 그리기
			}
		}
		BitBlt(hdc, 0, 0, 800, 600, hvirtualdc, 0, 0, SRCCOPY);					//다그린그림 옮겨그리기



		DeleteDC(hvirtualdc);
		DeleteObject(hvirtualbit);
		ReleaseDC(hwindow, hdc);
	}

	void destroy()
	{
		DeleteObject(hmapbit);
		DeleteObject(hfighterbit);
		DeleteObject(hmissilebit);
		DeleteObject(hgameoverbit);
	}
	HDC getdc()
	{
		return hmapdc;
	}

}