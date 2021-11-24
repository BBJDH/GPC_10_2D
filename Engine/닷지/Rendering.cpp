#include<Windows.h>
#include<vector>


namespace Rendering
{
	namespace
	{
		HBITMAP hmapbit, hfighterbit, hmissilebit;
		BITMAP fighter, missile;
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
			TEXT("./소스파일/spaceshipset32x32/player_ship.bmp"),
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

	void update(HWND const& hwindow, int const player_x, int const player_y,
		std::vector<POINT> const& missilepos)
	{
		HDC hdc = GetDC(hwindow);
		HDC hvirtualdc = CreateCompatibleDC(hdc);
		HBITMAP hvirtualbit = CreateCompatibleBitmap(hdc, 800, 600);
		SelectObject(hvirtualdc, hvirtualbit);

		drawbitmp(hvirtualdc,0,0,800,600,hmapbit);
		drawbitmp_transparent(hvirtualdc,player_x - (fighter.bmWidth/2),
			player_y - (fighter.bmHeight/2),fighter,hfighterbit);
		
		//TODO: 설정된 미사일들 출력
		if(!missilepos.empty())
		{

			for (size_t i = 0; i < missilepos.size(); i++)
			{
				drawbitmp_transparent(hvirtualdc, missilepos[i].x - (missile.bmWidth / 2),
					missilepos[i].y - (missile.bmHeight / 2), missile, hmissilebit);
			}

		}

		BitBlt(hdc, 0, 0, 800, 600, hvirtualdc, 0, 0, SRCCOPY);
		DeleteDC(hvirtualdc);
		DeleteObject(hvirtualbit);
		ReleaseDC(hwindow, hdc);
	}

	void destroy()
	{
		DeleteObject(hmapbit);
		DeleteObject(hfighterbit);
		DeleteObject(hmissilebit);
	}

}