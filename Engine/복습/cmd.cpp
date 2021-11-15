#include<Windows.h>
//#pragma region º¹½À
//#pragma warning(push,0)
//
//LRESULT CALLBACK WndProc
//(
//    HWND   const     hwnd,
//    UINT   const     message,
//    WPARAM const     wParam,
//    LPARAM const     lParam
//) 
//{
//    switch (message)
//    {
//    default:
//        return DefWindowProc(hwnd, message, wParam, lParam);
//    }
//}
//
//int WINAPI WinMain
//(
//    _In_ HINSTANCE hInstance,
//    _In_opt_ HINSTANCE hPrevInstance,
//    _In_ LPSTR lpCmdLine,
//    _In_ int nShowCmd
//)
//{
//    HWND hWindow = HWND();
//
//    {
//        WNDCLASSEX CMDCtrl = WNDCLASSEX();
//        
//        CMDCtrl.cbSize = sizeof(CMDCtrl);
//        CMDCtrl.style = 0;
//        CMDCtrl.lpfnWndProc= WndProc;
//        CMDCtrl.cbClsExtra=0;
//        CMDCtrl.cbWndExtra=0;          
//        CMDCtrl.hInstance = hInstance;
//        CMDCtrl.hIcon =LoadIcon(hInstance,IDI_APPLICATION);
//        CMDCtrl.hCursor =LoadCursor(hInstance,IDC_ARROW) ;
//        CMDCtrl.hbrBackground= static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
//        CMDCtrl.lpszMenuName =nullptr;
//        CMDCtrl.lpszClassName ="CMD";
//        CMDCtrl.hIconSm = LoadIcon(hInstance,IDI_APPLICATION);
//
//        RegisterClassEx(&CMDCtrl);
//
//    }
//    hWindow = CreateWindowEx   //
//    (
//        0,
//        "CMD",
//        "NetState",
//        WS_OVERLAPPEDWINDOW,  //¾ÈÇÏ¸é ¹Î¹«´Ì Åä±â
//        0,
//        0,
//        640,
//        480,
//        HWND(),
//        HMENU(),
//        hInstance,
//        nullptr
//    );
//
//    ShowWindow(hWindow, nShowCmd);  
//
//    MSG Message = MSG();
//
//    while (GetMessage(&Message, HWND(), WM_NULL, WM_NULL))
//        DispatchMessage(&Message);
//
//    
//    return Message.wParam;
//
//}  
//#pragma endregion


int main()
{
	WinExec("cmd.exe", SW_SHOW);

	return 0;
}