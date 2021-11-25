#include<Windows.h>
#include<iostream>
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console")

namespace Input
{
	namespace
	{
		size_t count =0;

		class
		{
		public:
			
			void print() const
			{
					system("cls");
				for (size_t i = 0; i < 256; i++)
				{
					if ((i % 16)==0)
						std::cout << std::endl;

					if (Pressed(i))
						std::cout << "O" << " ";
					else
						std::cout << "X" << " ";

				}
			}
			bool Pressed(WPARAM const code) const
			{
				return State.Pressed[code >> 0x4] & (0x8000 >> (code & 0xF));
			}
			void Down(WPARAM const code) 
			{
				if(!Pressed(code)) //해당키가 이전에 안눌려있으면
					State.Changed[code >> 0x4] |= 0x8000 >> (code & 0xF);
				else//눌려있었으면
					State.Changed[code >> 0x4] &= ~(0x8000 >> (code & 0xF));
				State.Pressed[code>>0x4] |=0x8000>>(code & 0xF); 
			}
			void Up(WPARAM const code)
			{
				if (Pressed(code))  //눌려있었으면
					State.Changed[code >> 0x4] |= 0x8000 >> (code & 0xF);
				else //해당키가 이전에 안눌려있으면
					State.Changed[code >> 0x4] &= ~(0x8000 >> (code & 0xF));
				State.Pressed[code >> 0x4] &= ~(0x8000 >> (code & 0xF));
			}

			bool Changed(WPARAM const code) const
			{
				return State.Changed[code >> 0x4] & (0x8000 >> (code & 0xF));
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
	}
	void Procedure
	(HWND   const hWindow, UINT   const uMessage, WPARAM const wParameter, LPARAM const lParameter)
	{
		switch (uMessage)
		{
			case WM_SYSKEYDOWN:
			case WM_KEYDOWN:
			{
				Key.Down(wParameter);
				break;
			}
			case WM_SYSKEYUP:
			case WM_KEYUP:
			{
				Key.Up(wParameter);
				break;
			}
		}
		if(Key.Changed(wParameter))
		{
			Key.print();
			std::cout<<"\n키상태 변동 수 : "<<++count<<std::endl;
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
