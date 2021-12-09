#include<Windows.h>
#include<vector>
#include<time.h>
//#include<cstdio>

//Time, Input, Collision,Rendering, Sound
//각각의 프로시져로 중계를 해준다
//옵션 - 텍스트 편집기 ctrl 정의 피킹 키 편집 가능

namespace Time
{void Procedure(HWND   const hWindow, UINT   const uMessage, WPARAM const wParameter, LPARAM const lParameter);}

namespace Rendering
{
    void update(HWND const& hwindow, int const player_x, int const player_y,
        std::vector<int*> const& Shapepos, std::vector<double*> const& ang);
}

namespace Time
{
    bool isinterval();
    bool isregentime();
}
namespace Shape
{
    void push(POINT const& player);
    void move();
    std::vector<int*> const vecpoint();
    std::vector<double*> const vecang();
}

bool iscrash(int const& dest_x, int const& dest_y, int const dest_size,
    std::vector<int*> const& shape_pos, std::vector<double*> const& angle);
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
            Shape::push(player);

            return 0;
        }
        case WM_APP:
        {
            Time::Procedure(hWindow,uMessage,wParameter,lParameter);
            if (Time::isinterval())
            {
                Shape::move();
                iscrash(player.x, player.y, 50, Shape::vecpoint(), Shape::vecang());
            }
            Rendering::update(hWindow, player.x, player.y, Shape::vecpoint(), Shape::vecang());
            if (Time::isregentime())
            {
                Shape::push(player);
            }
            return 0;
        }

        case WM_DESTROY:
        {
            PostQuitMessage(0); 


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