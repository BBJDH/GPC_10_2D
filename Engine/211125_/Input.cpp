#include<Windows.h>
#include<string>
#include<iostream>
//#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console")

namespace Input
{
	namespace
	{
		class
		{
		public:
			void Down(WPARAM const code)
			{
				State.Pressed[code>>0x4] |=0x8000>>(code & 0xF); 
			}
			void Up(WPARAM const code)
			{
				//State.Pressed[code >> 0x4] ^= 0x8000 >> (code & 0xF); //0111 1111 1111 1111 같으면 0 다르면1
				State.Pressed[code >> 0x4] &= ~(0x8000) >> (code & 0xF);//0111 1111 1111 1111

				//0000 0000 0000 0100
				//
			}
			//지금 만든 매트릭스에 대해서 bool 타입으로 눌렸는지 안눌렸는지 확인해서 반환 Pressed
		private:
			struct 
			{
				WORD Pressed[16];  //256 bit
				WORD Changed[16];  //256 bit

			}
			State;

		}
		Key;

		//bool State[256] ={false};
	}
	void Procedure
	(HWND   const hWindow, UINT   const uMessage, WPARAM const wParameter, LPARAM const lParameter)
	{
		switch (uMessage)
		{
			case WM_SYSKEYDOWN:
			case WM_KEYDOWN:
			{
				//State[wParameter] = true;
				Key.Down
				break;
			}
			case WM_SYSKEYUP:
			case WM_KEYUP:
			{
				//State[wParameter] = false;
				break;
			}

		}


#pragma region 삽질
		//switch (uMessage)
		//{

		//case WM_SYSKEYDOWN:
		//{

		//	switch (wParameter)
		//	{
		//	case VK_F10:
		//	{
		//		if (keytext.find("[F10]") == std::string::npos)
		//			keytext += "[F10]";
		//		break;
		//	}
		//	case VK_MENU:
		//	{
		//		if (keytext.find("[SysAlt]") == std::string::npos)
		//			keytext += "[SysAlt]";
		//		break;
		//	}

		//	case VK_F1:
		//	{
		//		if (keytext.find("[F1]") == std::string::npos)
		//			keytext += "[F1]";
		//		break;

		//	}
		//	case VK_LEFT:
		//	{
		//		if (keytext.find("[←]") == std::string::npos)
		//			keytext += "[←]";
		//		break;
		//	}
		//	case 'A':
		//	{
		//		if (keytext.find("[A]") == std::string::npos)
		//			keytext += "[A]";
		//		break;
		//	}

		//	}
		//}
		//break;
		//case WM_SYSKEYUP:
		//{
		//	switch (wParameter)
		//	{

		//	case VK_F10:
		//	{
		//		size_t const index = keytext.find("[F10]");
		//		if (index != std::string::npos)
		//		{
		//			keytext.erase(index, strlen("[F10]"));
		//		}
		//		break;
		//	}
		//	case VK_MENU:
		//	{
		//		size_t const index = keytext.find("[SysAlt]");
		//		if (index != std::string::npos)
		//		{
		//			keytext.erase(index, strlen("[SysAlt]"));
		//		}
		//		break;
		//	}

		//	case VK_F1:
		//	{
		//		size_t const index = keytext.find("[F1]");
		//		if (index != std::string::npos)
		//		{
		//			keytext.erase(index, strlen("[F1]"));
		//		}
		//		break;

		//	}
		//	case VK_LEFT:
		//	{
		//		size_t const index = keytext.find("[←]");
		//		if (index != std::string::npos)
		//		{
		//			keytext.erase(index, strlen("[←]"));
		//		}
		//		break;

		//	}
		//	case 'A':
		//	{
		//		size_t const index = keytext.find("[A]");
		//		if (index != std::string::npos)
		//		{
		//			keytext.erase(index, strlen("[A]"));
		//		}
		//		break;
		//	}
		//	}
		//}
		//break;
		//case WM_KEYDOWN:
		//{
		//	switch (wParameter)
		//	{
		//	case VK_F1:
		//	{
		//		if (keytext.find("[F1]") == std::string::npos)
		//			keytext += "[F1]";
		//		break;

		//	}
		//	case VK_LEFT:
		//	{
		//		if (keytext.find("[←]") == std::string::npos)
		//			keytext += "[←]";
		//		break;
		//	}
		//	case 'A':
		//	{
		//		if (keytext.find("[A]") == std::string::npos)
		//			keytext += "[A]";
		//		break;
		//	}
		//	}
		//}
		//break;
		//case WM_KEYUP:
		//{
		//	switch (wParameter)
		//	{
		//	case VK_F1:
		//	{
		//		size_t const index = keytext.find("[F1]");
		//		if (index != std::string::npos)
		//		{
		//			keytext.erase(index, strlen("[F1]"));
		//		}
		//		break;

		//	}
		//	case VK_LEFT:
		//	{
		//		size_t const index = keytext.find("[←]");
		//		if (index != std::string::npos)
		//		{
		//			keytext.erase(index, strlen("[←]"));
		//		}
		//		break;

		//	}
		//	case 'A':
		//	{
		//		size_t const index = keytext.find("[A]");
		//		if (index != std::string::npos)
		//		{
		//			keytext.erase(index, strlen("[A]"));
		//		}
		//		break;
		//	}
		//	}

		//}
		//break;

		//}
		//HDC hdc = GetDC(hWindow);
		//SelectObject(hdc, GetStockObject(WHITE_PEN));
		//Rectangle(hdc, 0, 0, 640, 480);
		//DrawText(hdc, keytext.c_str(), ~'\0', &textarea, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		//ReleaseDC(hWindow, hdc);
		//DefWindowProc(hWindow, uMessage, wParameter, lParameter);
#pragma endregion

	}
}