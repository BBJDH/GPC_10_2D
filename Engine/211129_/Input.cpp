#include<Windows.h>
#include<windowsx.h>
//#include<iostream>
//#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console")

namespace Input
{
	namespace
	{
		size_t count =0;

		class
		{
		public:
			void Update()
			{	//특정주소의 비트셋을 0으로, 인자는 주소, 초기화사이즈 받는다
				ZeroMemory(State.Changed,sizeof(State.Changed));
			}
			//void print() const
			//{
			//		system("cls");
			//	for (size_t i = 0; i < 256; i++)
			//	{
			//		if ((i % 16)==0)
			//			std::cout << std::endl;
			//		if (Pressed(i))
			//			std::cout << "O" << " ";
			//		else
			//			std::cout << "X" << " ";
			//	}
			//}
			bool Changed(WPARAM const code) const
			{
				return State.Changed[code >> 0x4] & (0x8000 >> (code & 0xF));
			}
			bool Pressed(WPARAM const code) const
			{
				return State.Pressed[code >> 0x4] & (0x8000 >> (code & 0xF));
			}
			void Down(WPARAM const code) 
			{
				if (!Pressed(code))
				{
					State.Changed[code >> 0x4] ^= 0x8000 >> (code & 0xF);
					State.Pressed[code>>0x4]   ^=0x8000>>(code & 0xF); 
				}

			}
			void Up(WPARAM const code)
			{
				State.Changed[code >> 0x4] ^= 0x8000 >> (code & 0xF);
				State.Pressed[code >> 0x4] ^= 0x8000 >> (code & 0xF);
			}
		private:
			struct 
			{
				WORD Pressed[16];  //256 bit
				WORD Changed[16];  //256 bit
			}
			State;
		}
		Key;
		POINT Cursor;
		POINT Wheel;
	}
	void Procedure
	(HWND   const hWindow, UINT   const uMessage, WPARAM const wParameter, LPARAM const lParameter)
	{
		switch (uMessage)
		{//wparameter의 숫자 순으로 정렬
			case WM_APP:
			{
				Key.Update();
				Wheel = POINT();
				return;
			}
			case WM_SYSKEYDOWN:
			case WM_KEYDOWN:	 {Key.Down(wParameter); return;}
			case WM_SYSKEYUP:
			case WM_KEYUP:		 {Key.Up(wParameter); return;}
			case WM_LBUTTONDOWN: {Key.Down(VK_LBUTTON); return; }
			case WM_RBUTTONDOWN: {Key.Down(VK_RBUTTON); return; }
			case WM_MBUTTONDOWN: {Key.Down(VK_MBUTTON); return; }
			case WM_XBUTTONDOWN:
			{
				switch (GET_XBUTTON_WPARAM(wParameter))
				{
					case XBUTTON1: {Key.Down(VK_XBUTTON1); return; }
					case XBUTTON2: {Key.Down(VK_XBUTTON2); return; }
				}
			}
			case WM_LBUTTONUP: {Key.Up(VK_LBUTTON); return; }
			case WM_RBUTTONUP: {Key.Up(VK_RBUTTON); return;
			case WM_MBUTTONUP: {Key.Up(VK_MBUTTON); return;
			case WM_XBUTTONUP:
			{
				switch (GET_XBUTTON_WPARAM(wParameter))
				{
				case XBUTTON1: {Key.Up(VK_XBUTTON1); return; }
				case XBUTTON2: {Key.Up(VK_XBUTTON2); return; }
				}
				return;
			}
			case WM_MOUSEHWHEEL: {Wheel.x += GET_WHEEL_DELTA_WPARAM(wParameter) / WHEEL_DELTA; return; } //wParameter
			case WM_MOUSEWHEEL: {Wheel.y += GET_WHEEL_DELTA_WPARAM(wParameter) / WHEEL_DELTA; return; }
			case WM_MOUSEMOVE:
			{
				//[[fallthrough]];
				//[[nodiscard]]
				Cursor.x = GET_X_LPARAM(lParameter);
				Cursor.y = GET_Y_LPARAM(lParameter);

				return;
			}
		}


		//if(Key.Changed(wParameter))
		//{
		//	Key.print();
		//	std::cout<<"\n키상태 변동 수 : "<<++count<<std::endl;
		//}

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
