#include<Windows.h>
#include<vector>
#include<string>

namespace Rendering
{
	namespace
	{
		HBITMAP hmapbit, hfighterbit, hmissilebit,hgameoverbit;
		BITMAP fighter, missile, over;
	}
	void initialize(HWND const&  hwindow)
	{
		HDC hdc = GetDC(hwindow);
		hmapbit = CreateCompatibleBitmap(hdc, 800, 600);
		hfighterbit = CreateCompatibleBitmap(hdc, 50, 50);
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
			TEXT("./소스파일/포트리스/캐논_오른쪽.bmp"),
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

	void update(HWND const& hwindow, float const player_x, float const player_y,
		 float const time)
	{
		HDC hdc = GetDC(hwindow);
		HDC hvirtualdc = CreateCompatibleDC(hdc);
		HBITMAP hvirtualbit = CreateCompatibleBitmap(hdc, 800, 600);
		SelectObject(hvirtualdc, hvirtualbit);

		//drawbitmp(hvirtualdc,0,0,800,600,hmapbit);			//맵 파일 그리기
		Rectangle(hvirtualdc,0,500,800,600);
		drawbitmp_transparent(hvirtualdc, static_cast<const int>(player_x) - (fighter.bmWidth/2),
			static_cast<const int>(player_y) - (fighter.bmHeight/2),fighter,hfighterbit);	//비행기 그리기
		

		SetBkMode(hvirtualdc, TRANSPARENT);					
		SetTextColor(hvirtualdc,RGB(255,255,255));
		std::string temp = "Time :" + std::to_string(time);		//운동시간 텍스트
		
		TextOut(hvirtualdc, 680, 0, temp.c_str(), static_cast<int>(temp.size()));

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

}