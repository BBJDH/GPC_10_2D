#include<Windows.h>
#include<string>
namespace Input
{
	namespace
	{
		RECT textarea
		{
			0,0,640,480
		};
		std::string keytext ="";
	}
	void Procedure
	(HWND   const hWindow, UINT   const uMessage, WPARAM const wParameter, LPARAM const lParameter)
	{

		switch (uMessage)
		{
			
			case WM_SYSKEYDOWN:
			{
				
				switch (wParameter)
				{
					case VK_F10:
					{
						if (keytext.find("[F10]") == std::string::npos)
							keytext += "[F10]";
						break;
					}
					case VK_MENU: 
					{
						if(keytext.find("[SysAlt]")==std::string::npos)
							keytext += "[SysAlt]";
						break;
					}

					case VK_F1:
					{
						if (keytext.find("[F1]") == std::string::npos)
							keytext += "[F1]";
						break;

					}
					case VK_LEFT:
					{
						if (keytext.find("[ก็]") == std::string::npos)
							keytext += "[ก็]";
						break;
					}
					case 'A':
					{
						if (keytext.find("[A]") == std::string::npos)
							keytext += "[A]";
						break;
					}

				}
			}
			break;
			case WM_SYSKEYUP:
			{
				switch (wParameter)
				{

					case VK_F10:
					{
						size_t const index = keytext.find("[F10]");
						if (index != std::string::npos)
						{
							keytext.erase(index, strlen("[F10]"));
						}
						break;
					}
					case VK_MENU:
					{
						size_t const index = keytext.find("[SysAlt]");
						if (index != std::string::npos)
						{
							keytext.erase(index,strlen("[SysAlt]"));
						}
						break;
					}

					case VK_F1:
					{
						size_t const index = keytext.find("[F1]");
						if (index != std::string::npos)
						{
							keytext.erase(index, strlen("[F1]"));
						}
						break;

					}
					case VK_LEFT:
					{
						size_t const index = keytext.find("[ก็]");
						if (index != std::string::npos)
						{
							keytext.erase(index, strlen("[ก็]"));
						}
						break;

					}
					case 'A':
					{
						size_t const index = keytext.find("[A]");
						if (index != std::string::npos)
						{
							keytext.erase(index, strlen("[A]"));
						}
						break;
					}
				}
			}
			break;
			case WM_KEYDOWN:
			{
				switch (wParameter)
				{
					case VK_F1:
					{
						if (keytext.find("[F1]") == std::string::npos)
							keytext += "[F1]";
						break;

					}
					case VK_LEFT:
					{
						if (keytext.find("[ก็]") == std::string::npos)
							keytext += "[ก็]";
						break;
					}
					case 'A':
					{
						if (keytext.find("[A]") == std::string::npos)
							keytext += "[A]";
						break;
					}
				}
			}
			break;
			case WM_KEYUP:
			{
				switch (wParameter)
				{
					case VK_F1:
					{
						size_t const index = keytext.find("[F1]");
						if (index != std::string::npos)
						{
							keytext.erase(index, strlen("[F1]"));
						}
						break;

					}
					case VK_LEFT:
					{
						size_t const index = keytext.find("[ก็]");
						if (index != std::string::npos)
						{
							keytext.erase(index, strlen("[ก็]"));
						}
						break;

					}
					case 'A':
					{
						size_t const index = keytext.find("[A]");
						if (index != std::string::npos)
						{
							keytext.erase(index, strlen("[A]"));
						}
						break;
					}
				}
				
			}
			break;

		}
		HDC hdc = GetDC(hWindow);
		SelectObject(hdc,GetStockObject(WHITE_PEN));
		Rectangle(hdc,0,0,640,480);
		DrawText(hdc, keytext.c_str(), ~'\0', &textarea, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		ReleaseDC(hWindow, hdc);
		DefWindowProc(hWindow, uMessage, wParameter, lParameter);
	}
}