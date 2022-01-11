#include<Windows.h>
#include<vector>
#include<string>
#include"Object.h"
#include"Tank.h"
#include"stdafx.h"

namespace Rendering
{
	namespace
	{
		HBITMAP hmapbit, htank_bit, hmissilebit,hbackground_bit,hmagentabit;
		BITMAP fighter, missile, over;
		HDC hmapdc;
	}//�̱������� �����Ͽ� �ܺ� ���� ���ϰ�

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
			TEXT("./�ҽ�����/��Ʈ����/Asset/Map/sky_M_800600.bmp"),
			IMAGE_BITMAP,
			0,
			0,
			LR_LOADFROMFILE | LR_DEFAULTSIZE
		));
		htank_bit = static_cast<HBITMAP>(LoadImage
		(
			NULL,
			TEXT("./�ҽ�����/��Ʈ����/����Ʈ����/ĳ��/M_Canon_Tank_Right.bmp"),
			IMAGE_BITMAP,
			0,
			0,
			LR_LOADFROMFILE | LR_DEFAULTSIZE
		));
		GetObject(htank_bit, sizeof(BITMAP), &fighter);
		hmissilebit = static_cast<HBITMAP>(LoadImage
		(
			NULL,
			TEXT("./�ҽ�����/missile.bmp"),
			IMAGE_BITMAP,
			0,
			0,
			LR_LOADFROMFILE | LR_DEFAULTSIZE
		));
		GetObject(hmissilebit, sizeof(BITMAP), &missile);
		hbackground_bit = static_cast<HBITMAP>(LoadImage
		(
			NULL,
			TEXT("./�ҽ�����/��Ʈ����/Asset/Background/background_800600.bmp"),
			IMAGE_BITMAP,
			0,
			0,
			LR_LOADFROMFILE | LR_DEFAULTSIZE
		));
		GetObject(hbackground_bit, sizeof(BITMAP), &over);

		drawbitmp(hmapdc, 0, 0, 800, 600, hmapbit);			//�� ���� �׸���


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

		// 1. ȸ������ �������� �����ǥ�� ���ϰ�
		// 2. ȸ���� ��ġ��ǥ(�����ǥ)�� ���� ��
		// 3. ���� ���� ������ ��ǥ�� ����.
 		for (size_t i = 0; i < 3; i++)
		{
			if (i == 0) { dblx = -ixRotate, dbly = -iyRotate; }    // left up  ������ �κ�
			else if (i == 1) { dblx = bmpwidth - ixRotate, dbly = -iyRotate; }  // right up ������ �κ�
			else if (i == 2) { dblx = -ixRotate, dbly = bmpheight - iyRotate; } // left low ������ �κ�
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
		tempbmp = CreateCompatibleBitmap(hdc, 100, 100);
		SelectObject(hMemdc, tempbmp);

		HBRUSH brush = CreateSolidBrush(RGB(255, 0, 255));
		hOldBmp = static_cast<HBITMAP>(SelectObject(hMemdc, brush));
		PatBlt(hMemdc, 0, 0, 100 , 100 , PATCOPY);
		SelectObject(hMemdc, hOldBmp);
		DeleteObject(brush);


		hOldBmp = static_cast<HBITMAP>(SelectObject(himagedc, hBmp));
		BOOL result = PlgBlt(hMemdc, vertex, himagedc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, 0, 0, 0);
		GdiTransparentBlt(hdc, ixDisplay- bitmap.bmWidth, iyDisplay- bitmap.bmHeight, 100, 100,
			hMemdc, 0, 0, 100, 100,  RGB(255, 0, 255));

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
		HBITMAP hvirtualbit = CreateCompatibleBitmap(hdc, 800, 600);
		SelectObject(hvirtualdc, hvirtualbit);

		drawbitmp(hvirtualdc,0,0,800,600, hbackground_bit);			//��� ���� �׸���

		TransparentBlt(hvirtualdc, 0, 0, 800, 600, hmapdc,
			0, 0, 800, 600, RGB(255, 0, 255));
		//Rectangle(hvirtualdc,0,500,800,600);

		if (!obj.empty())								//������Ʈ �׸���(������ŭ)
		{
			for (size_t i = 0; i < obj.size(); i++)
			{
				//drawbitmp_transparent(hvirtualdc, static_cast<const int>(obj[i].getpos().x) - (fighter.bmWidth / 2),
				//	static_cast<const int>(obj[i].getpos().y) - (fighter.bmHeight / 2), fighter, htank_bit);	
				RotateSizingImage(hvirtualdc,htank_bit,obj[i].getimage_angle(),fighter.bmWidth/2,fighter.bmHeight/2,
					static_cast<const int>(obj[i].getpos().x),
					static_cast<const int>(obj[i].getpos().y));
				Ellipse(hvirtualdc, 
					static_cast<const int>(obj[i].getpos().x - 2),
					static_cast<const int>(obj[i].getpos().y+ fighter.bmHeight / 2 - 2),
					static_cast<const int>(obj[i].getpos().x + 2),
					static_cast<const int>(obj[i].getpos().y+ fighter.bmHeight / 2 + 2));
			}
		}
		if (!obj.empty())								//������Ʈ �׸���(������ŭ)
		{
			SetBkMode(hvirtualdc, TRANSPARENT);
			SetTextColor(hvirtualdc, RGB(255, 255, 255));
			std::string temp = "x :" + std::to_string(obj.back().getpos().x);		//x��ǥ
			TextOut(hvirtualdc, 0, 0, temp.c_str(), static_cast<int>(temp.size()));
			temp = "y :" + std::to_string(obj.back().getpos().y);		//y��ǥ
			TextOut(hvirtualdc, 100, 0, temp.c_str(), static_cast<int>(temp.size()));

			temp = "angle :" + std::to_string(obj.back().getimage_angle());									//��ƾ�ð� �ؽ�Ʈ
			TextOut(hvirtualdc, 680, 0, temp.c_str(), static_cast<int>(temp.size()));
		}

		if(magenta_switch)
			BitBlt(hdc, 0, 0, 800, 600, hmapdc, 0, 0, SRCCOPY);					
		else
			BitBlt(hdc, 0, 0, 800, 600, hvirtualdc, 0, 0, SRCCOPY);					


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

}