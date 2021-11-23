#include<Windows.h>

namespace Input
{
	namespace
	{

	}
	void Procedure
	(HWND   const hWindow, UINT   const uMessage, WPARAM const wParameter, LPARAM const lParameter)
	{

		switch (uMessage)
		{

			//TODO: 과제 키입력 처리
		case WM_SYSKEYDOWN:
		case WM_SYSKEYUP:
		case WM_KEYDOWN:
		case WM_KEYUP:

			{
				wParameter;
			}

			default:
				break;


		}
	}
}