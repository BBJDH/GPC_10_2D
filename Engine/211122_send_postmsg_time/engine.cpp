#include<Windows.h>


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
            return 0;
        }
        case WM_LBUTTONDOWN:
        {

            return 0;

        }
        case WM_DESTROY: //�Ҹ��� ����
        {
            PostQuitMessage(0); //���� ���μ������� �����


            return 0;
        }
        default:
        {
            return DefWindowProc(hWindow, uMessage, wParameter, lParameter);
        }
        }
    }

}