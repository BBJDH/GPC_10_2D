#include<Windows.h>
//#include<cstdio>

//Time, Input, Collision,Rendering, Sound
//각각의 프로시져로 중계를 해준다
//옵션 - 텍스트 편집기 ctrl 정의 피킹 키 편집 가능

namespace Time
{void Procedure(HWND   const hWindow, UINT   const uMessage, WPARAM const wParameter, LPARAM const lParameter);}
namespace Input
{
    void Procedure(HWND   const hWindow, UINT   const uMessage, WPARAM const wParameter, LPARAM const lParameter);
}
namespace Engine
{
    LRESULT CALLBACK Procedure
    (HWND   const hWindow,UINT   const uMessage,WPARAM const wParameter,  LPARAM const lParameter )
    {

        switch (uMessage)
        {
        case WM_CREATE:
        {
            return 0;
        }
        case WM_APP:
        {
            Time::Procedure(hWindow,uMessage,wParameter,lParameter);
            //Input::Procedure(hWindow, uMessage, wParameter, lParameter);

            return 0;
        }

        case WM_DESTROY: //소멸자 개념
        {
            PostQuitMessage(0); //남은 프로세스에서 사라짐


            return 0;
        }
        case WM_MOUSEWHEEL:   case WM_MOUSEHWHEEL: case WM_MOUSEMOVE:
        case WM_SYSKEYDOWN:   case WM_LBUTTONDOWN: case WM_LBUTTONUP:
        case WM_SYSKEYUP:     case WM_RBUTTONDOWN: case WM_RBUTTONUP:
        case WM_KEYDOWN:      case WM_MBUTTONDOWN: case WM_MBUTTONUP:
        case WM_KEYUP:        case WM_XBUTTONDOWN: case WM_XBUTTONUP:
        {
            Input::Procedure(hWindow, uMessage, wParameter, lParameter);

            return 0;
        }
        default:
        {
            return DefWindowProc(hWindow, uMessage, wParameter, lParameter);
        }
        }
    }

}