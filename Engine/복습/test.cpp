#include<Windows.h>
#pragma region 복습

LRESULT CALLBACK WndProc
(
    HWND const hwindow,
    UINT const uMessage,
    WPARAM const wParameter,
    LPARAM const lParameter
)
{
    switch (uMessage)
    {
    //case WM_PAINT:
    //{
    //    HDC hdc = GetDC(hwindow);
    //    Ellipse(hdc, 0, 0, 50, 50);
    //    ReleaseDC(hwindow, hdc);
    //    return 0;
    //}
    case WM_DESTROY:
    {
        ExitProcess(0);
        return 0;
    }
    case WM_MOUSEMOVE:
    {

    }

    case WM_RBUTTONDOWN:
    {
        //SendMessage(hwindow, WM_DESTROY, 0, 0);
        //HDC hdc = GetDC(hwindow);
        //Ellipse(hdc, LOWORD(lParameter)-20, HIWORD(lParameter)-20, LOWORD(lParameter)+20, HIWORD(lParameter)+20);
        //ReleaseDC(hwindow, hdc);
        
        return 0;
    }
    case WM_LBUTTONDOWN:
    {
        
        //HDC hdc = GetDC(hwindow);
        //SetBkMode(hdc, TRANSPARENT);
        //TextOut(hdc, LOWORD(lParameter), HIWORD(lParameter), ".", 1);
        //ReleaseDC(hwindow, hdc);
        return 0;
    }
    case WM_LBUTTONUP:
    {
    }
    
    default:
        return DefWindowProc(hwindow,uMessage,wParameter,lParameter);
    }
}


//메인 생성 -HWND 생성- WNDCLASSEX 생성
int WINAPI WinMain
(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nShowCmd
)
{
    HWND hprintwindow = HWND();

    WNDCLASSEXA basic = WNDCLASSEX();
    
#pragma region 창 기본설정
    basic.cbSize = sizeof(WNDCLASSEX);
    basic.style = 0;
    basic.lpfnWndProc = WndProc;
    basic.cbClsExtra = 0;
    basic.cbWndExtra = 0;
    basic.hInstance = hInstance;
    basic.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    basic.hCursor = LoadCursor(NULL,IDC_HAND);
    basic.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
    basic.lpszMenuName = nullptr;
    basic.lpszClassName = "Basic";
    basic.hIconSm = LoadIcon(hInstance, IDI_APPLICATION);

    RegisterClassEx(&basic);
#pragma endregion

    CREATESTRUCT printwindow = CREATESTRUCT();
#pragma region 메인창 설정
    printwindow.lpCreateParams = nullptr;
    printwindow.hInstance = hInstance;
    printwindow.hMenu = HMENU();
    printwindow.hwndParent = HWND();
    printwindow.cy = 320;
    printwindow.cx = 480;
    printwindow.y = CW_USEDEFAULT;
    printwindow.x = CW_USEDEFAULT;
    printwindow.style = WS_OVERLAPPEDWINDOW;
    printwindow.lpszName = "Print";
    printwindow.lpszClass = "Basic";
    printwindow.dwExStyle = 0;

    RECT rect = RECT();
    rect.left = 0;
    rect.top = 0;
    rect.right = printwindow.cx;
    rect.bottom = printwindow.cy;

    AdjustWindowRectEx(&rect, printwindow.style, false, printwindow.dwExStyle);
    printwindow.cx = rect.right - rect.left;
    printwindow.cy = rect.bottom - rect.top;
#pragma endregion
#pragma region 창생성-SHOW
    hprintwindow = CreateWindowEx
    (
        printwindow.dwExStyle,
        printwindow.lpszClass,
        printwindow.lpszName,
        printwindow.style,
        printwindow.x,
        printwindow.y,
        printwindow.cx,
        printwindow.cy,
        printwindow.hwndParent,
        printwindow.hMenu,
        printwindow.hInstance,
        printwindow.lpCreateParams
    );
    ShowWindow(hprintwindow, SW_RESTORE);
#pragma endregion
    MSG msg = MSG();

    while (true)
    {
        if (PeekMessage(&msg, HWND(), WM_NULL, WM_NULL, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                return static_cast<int>(msg.wParam);
            DispatchMessage(&msg);
        }
        else
        {

        }

    }

 
    return 0;
}
#pragma endregion

