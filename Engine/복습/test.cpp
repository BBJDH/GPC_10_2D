#include<Windows.h>
#pragma region 복습

LRESULT CALLBACK WndProc
(
    HWND   const hwindow,
    UINT   const uMessage,
    WPARAM const wParameter,
    LPARAM const lParameter
)
{
    static bool lmouseclick = false;
    static bool rmouseclick = false;
    static int cursor_x     = 0;
    static int cursor_y     = 0;


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
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwindow,&ps);
        TextOut(hdc, LOWORD(lParameter), HIWORD(lParameter), "WM_PAINT", 8);

        EndPaint(hwindow,&ps);
        return 0;
    }
    case WM_MOUSEMOVE:
    {
        if(lmouseclick)
        {
            HDC hdc = GetDC(hwindow);

            //SetBkMode(hdc, TRANSPARENT);
            //SetPixel(hdc, LOWORD(lParameter), HIWORD(lParameter),RGB(0,0,0));
            //TextOut(hdc, LOWORD(lParameter), HIWORD(lParameter), ".", 1);
            MoveToEx(hdc, cursor_x,cursor_y, NULL);
            cursor_x = LOWORD(lParameter);
            cursor_y = HIWORD(lParameter);
            LineTo(hdc, cursor_x, cursor_y );

            ReleaseDC(hwindow, hdc);
        }
        else if(rmouseclick)
        {
            HPEN hpen = CreatePen(PS_SOLID,1,RGB(255,255,255));
            HDC hdc = GetDC(hwindow);
            SelectObject(hdc,hpen);
            Ellipse(hdc, LOWORD(lParameter)-20, HIWORD(lParameter)-20, LOWORD(lParameter)+20, HIWORD(lParameter)+20);
            DeleteObject(hpen);
            ReleaseDC(hwindow, hdc);
            
        }
        return 0;

    }

    case WM_RBUTTONUP:
    {
        rmouseclick = false;
        return 0;

    }
    case WM_RBUTTONDOWN:
    {
        rmouseclick = true;

        //SendMessage(hwindow, WM_DESTROY, 0, 0);
        
        
        return 0;
    }
    case WM_LBUTTONDOWN:
    {
        lmouseclick = true;
        cursor_x = LOWORD(lParameter);
        cursor_y = HIWORD(lParameter);

        //HDC hdc = GetDC(hwindow);
        
        return 0;
    }
    case WM_LBUTTONUP:
    {
        lmouseclick = false;
    }
    
    default:
        return DefWindowProc(hwindow,uMessage,wParameter,lParameter);
    }
}

//메인 생성 -HWND 생성- WNDCLASSEX 생성
int WINAPI WinMain
(
    _In_     HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_     LPSTR     lpCmdLine,
    _In_     int       nShowCmd
)
{
    HWND hprintwindow = HWND();

    WNDCLASSEXA basic = WNDCLASSEX();
    
#pragma region 창 기본설정
    basic.cbSize          = sizeof(WNDCLASSEX);
    basic.style           = 0;
    basic.lpfnWndProc     = WndProc;
    basic.cbClsExtra      = 0;
    basic.cbWndExtra      = 0;
    basic.hInstance       = hInstance;
    basic.hIcon           = LoadIcon(hInstance, IDI_APPLICATION);
    basic.hCursor         = LoadCursor(NULL,IDC_HAND);
    basic.hbrBackground   = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
    basic.lpszMenuName    = nullptr;
    basic.lpszClassName   = "Basic";
    basic.hIconSm         = LoadIcon(hInstance, IDI_APPLICATION);

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

