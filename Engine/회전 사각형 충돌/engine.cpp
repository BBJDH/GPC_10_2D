#include<Windows.h>
#include<vector>
#include<time.h>
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
namespace Rendering
{
    void update(HWND const& hwindow, int const player_x, int const player_y,
        std::vector<POINT*> const& rectpos, std::vector<double*> const& ang);
}
namespace Rect
{
    void push_rect(POINT const& player);
    void move_rect();
    std::vector<POINT*> const vecpoint();
    std::vector<double*>  vecang();
}
namespace Time
{
    bool isinterval();
    bool isregentime();
}
bool iscrash(POINT const& dest, int const size,
    std::vector<POINT*> const& rect, std::vector<double*>  angle);
namespace Engine
{
    POINT player;
    LRESULT CALLBACK Procedure
    (HWND   const hWindow,UINT   const uMessage,WPARAM const wParameter,  LPARAM const lParameter )
    {

        switch (uMessage)
        {
        case WM_CREATE:
        {
            srand(static_cast<unsigned>(time(NULL)));
            player.x = 400;
            player.y = 300;
            Rect::push_rect(player);
            return 0;
        }
        case WM_APP:
        {
            Time::Procedure(hWindow,uMessage,wParameter,lParameter);
            if (Time::isinterval())
            {
                Rect::move_rect();
                Rendering::update(hWindow, player.x, player.y, Rect::vecpoint(),Rect::vecang());

                iscrash(player, 100, Rect::vecpoint(), Rect::vecang());

            }
            if (Time::isregentime())
            {
                Rect::push_rect(player);
            }
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

            return 0;
        }
        default:
        {
            return DefWindowProc(hWindow, uMessage, wParameter, lParameter);
        }
        }
    }

}