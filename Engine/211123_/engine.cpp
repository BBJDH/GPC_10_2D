#include<Windows.h>
//#include<cstdio>

//Time, Input, Collision,Rendering, Sound
//������ ���ν����� �߰踦 ���ش�


//TIME
//��Ÿ Ÿ�� :������Ʈ ���� ������ ���� Ȥ�� ������� ���� �ð���
//
/*
W -> position += (0, 1);
S -> position -= (0, 1);
A -> position -= (1, 0);
D -> position += (1, 0);

        A	B
FPS		300	150
Speed		1.0	1.5
Distance	300	225

W -> position += (0, 1) * Delta;
S -> position -= (0, 1) * Delta;
A -> position -= (1, 0) * Delta;
D -> position += (1, 0) * Delta;

        A	B
Delta		1 / 300	1 / 150
Speed		1.0	1.5
Distance	1.0	1.5
*/
//#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console")
//�ֿܼ� ����� �ϴ� �뵵�� ���

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
            return 0;
        }
        default:
        {
            return DefWindowProc(hWindow, uMessage, wParameter, lParameter);
        }
        }
    }

}