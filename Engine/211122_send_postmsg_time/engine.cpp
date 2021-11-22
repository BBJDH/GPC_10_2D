#include<Windows.h>


//Time, Input, Collision,Rendering, Sound
//각각의 프로시져로 중계를 해준다


//TIME
//델타 타임 :업데이트 이전 이후의 시작 혹은 종료시의 사이 시간값
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
        case WM_DESTROY: //소멸자 개념
        {
            PostQuitMessage(0); //남은 프로세스에서 사라짐


            return 0;
        }
        default:
        {
            return DefWindowProc(hWindow, uMessage, wParameter, lParameter);
        }
        }
    }

}