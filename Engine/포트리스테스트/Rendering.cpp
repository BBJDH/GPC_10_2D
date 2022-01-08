#include<Windows.h>
#include<vector>
#include<string>
#include"Object.h"
#include"stdafx.h"

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

	BOOL RotateSizingImage(HDC hdc, HBITMAP hBmp,
		double dblAngle,
		int    ixRotateAxis, int iyRotateAxis,
		int    ixDisplay,    int iyDisplay,
		double dblSizeRatio = 1,
		HBITMAP hMaskBmp    = NULL, int ixMask = 0, int iyMask = 0)
	{
		int       i;
		BITMAP    bm;
		GetObject(hBmp, sizeof(BITMAP), &bm);
		POINT     apt[3]    = { 0 };
		double	  dblWidth  = (double)bm.bmWidth * dblSizeRatio;
		double	  dblHeight = (double)bm.bmHeight * dblSizeRatio;
		double	  ixRotate  = (int)((double)ixRotateAxis * dblSizeRatio); // ũ�Ⱑ ���ϴ� �� ���
		double	  iyRotate  = (int)((double)iyRotateAxis * dblSizeRatio);


		double dblx, dbly, dblxDest, dblyDest, cosVal, sinVal;
		cosVal = cos(dblAngle), sinVal = sin(dblAngle);

		// 1. ȸ������ �������� �����ǥ�� ���ϰ�
		// 2. ȸ���� ��ġ��ǥ(�����ǥ)�� ���� ��
		// 3. ���� ���� ������ ��ǥ�� ����.
 		for (i = 0; i < 3; i++)
		{
			if (i == 0) { dblx = -ixRotate, dbly = -iyRotate; }    // left up  ������ �κ�
			else if (i == 1) { dblx = dblWidth - ixRotate, dbly = -iyRotate; }  // right up ������ �κ�
			else if (i == 2) { dblx = -ixRotate, dbly = dblHeight - iyRotate; } // left low ������ �κ�
			dblxDest = dblx * cosVal - dbly * sinVal;
			dblyDest = dblx * sinVal + dbly * cosVal;
			dblxDest += ixRotate, dblyDest += iyRotate;
			apt[i].x = ixDisplay - (long)ixRotate + (long)dblxDest;
			apt[i].y = iyDisplay - (long)iyRotate + (long)dblyDest;
		}

		HDC hMemdc;
		HBITMAP hOldBmp;
		hMemdc = CreateCompatibleDC(hdc);
		hOldBmp = (HBITMAP)SelectObject(hMemdc, hBmp);
		BOOL iRes = PlgBlt(hdc, apt, hMemdc, 0, 0, bm.bmWidth, bm.bmHeight, hMaskBmp, ixMask, iyMask);
		SelectObject(hMemdc, hOldBmp);
		DeleteDC(hMemdc);
		return iRes;

	}

	void update(HWND const& hwindow, std::vector<Object> const & obj,bool const magenta_switch)
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
					static_cast<const int>(obj[i].getpos().y),1);
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




}