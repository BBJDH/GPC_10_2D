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

			//TODO: ���� Ű�Է� ó��
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