#include<Windows.h>
//#include<cstdio>

//Time, Input, Collision,Rendering, Sound
//������ ���ν����� �߰踦 ���ش�
//�ɼ� - �ؽ�Ʈ ������ ctrl ���� ��ŷ Ű ���� ����

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

        case WM_DESTROY: //�Ҹ��� ����
        {
            PostQuitMessage(0); //���� ���μ������� �����


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