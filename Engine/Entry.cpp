#include <Windows.h>

/*
호출 규약(Calling convention)

winapi 안쓰면 cdecl 을 암시적으로 적용
       cdecl : Cdeclaration. c/c++의 기본 호출 규약.
     stdcall : Standard Call. Windows API의 기본 호출 규약.
    thiscall : 멤버 함수의 기본 호출 규약.

*/
/*

Source Annotation Language, SAL
소스 코드 주석 언어

_In_ : 포인터 형식의 인자에 대해 nullptr를 허용하지 않음.
_In_opt_ : 포인터 형식의 인자에 대해 nullptr를 허용함.

*/

//winapi -> __stdcall

/*Register -> create -> show -> run -> close -> destroy -> unregister */
//unregister os가 클래스 찾아서 알아서 정리
//#pragma warning(push,0) //모든 경고를 끄는 전처리기


//서로 다른 프로시져를 가질 경우
//같은 프로시저 안에서 처리할때

LRESULT CALLBACK WndProc
(
    HWND   const hWindow,
    UINT   const uMessage,
    WPARAM const wParameter,   //word 파라메터 ->
    LPARAM const lParameter    //long 파라메터 -> 용량을 늘리고 데이터를 압축해서 전달
                                //메세지의 세부 정보를 전달

//HWND hwnd; 윈도우 핸들 어떠한 윈도우에서 발생한 메세지인가
//UINT message; 윈도우 메세지 WM_ ...를 담는다
//WPARAM wParam; 특정 메세지에 따라 
//LPARAM lParam; 해당 메세지에 대한 세부정보를 담는다
//DWORD time; 발생시간
//POINT pt;
)
{
    switch (uMessage)
    {
        //case WM_CREATE: //생성자
        //{
        //    CREATESTRUCT const* const pcs = reinterpret_cast<CREATESTRUCT const*>(lParameter);
        //    
        //    //ex)
        //    //pcs->hMenu;
        //    return 0;
        //}
        //case WM_CLOSE:
        //{
        //    DestroyWindow(hWindow);
        //    //WM_ClOSE 발생
        //    return 0;
        //}
        case WM_LBUTTONDOWN:
        //case WM_LBUTTONUP:
        {

                //"Window has been clicked!","Click!" 메세지 박스 이용
            MessageBox(hWindow, "Window has been clicked!", "Click!", MB_OK);
            return 0;

        }
        case WM_DESTROY: //소멸자 개념
        {
            MessageBox(hWindow, "Destroy", "Message box", MB_ICONWARNING | MB_OK);

            PostQuitMessage(0); //남은 프로세스에서 사라짐
            //WM_QUIT 메세지 발생
            
            return 0;
        }
        default:
        {
            return DefWindowProc(hWindow, uMessage, wParameter, lParameter);
        }
    }
}
//LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM) = WndProc;

int APIENTRY WinMain
(
    _In_     HINSTANCE  const hInstance, //nullptr 불허함 _in_ 포인터 형식에 대해서만!
    _In_opt_ HINSTANCE  const hPrevInstance, //_In_ 옵셔널 널포인터 허용
    _In_     LPSTR      const lpCmdLine, //추가되는 커맨드 라인을 받는다
    //LPSTR ->longptr string 
    _In_     int        const nShowCmd //실행탭에 어떤설정을 한상태로 실행 되었는지 전달
)
{
    //_Outptr_ 
    //WinMain(nullptr, nullptr, nullptr, 0);
    //strcmp(lpCmdLine,"-w")

    HWND hWindow = HWND(); //윈도우 창 생성
    {//형식에 대한 정의
        WNDCLASSEX Class = WNDCLASSEX();

        Class.cbSize        = sizeof(WNDCLASSEX);  //윈도우 사이즈 지정
        Class.style         = 0;  //부호없는 정수형, 윈도우 클래스 스타일
        Class.lpfnWndProc   = WndProc;
        Class.cbClsExtra    = 0; //클래스의 여분 메모리
        Class.cbWndExtra    = 0; //윈도우의 여분 메모리
        Class.hInstance     = hInstance; //인스턴스 핸들 (어느 인스턴스 소속인가)
        Class.hIcon         = LoadIcon(hInstance, IDI_APPLICATION);  //아이콘 모양 뭐쓸래
        //일반적인 어플리케이션 아이콘 사용
        Class.hCursor       = LoadCursor(hInstance, IDC_ARROW); //마우스 모양 뭐쓸래
        Class.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
        //배경 브러쉬 핸들
        Class.lpszMenuName  = nullptr;
        //sz => string terminated by zero =>기본 캐릭터배열 문자열 끝이 널
        Class.lpszClassName = "Window";
        /*클래스 네임 지정 like (class name)*/
        Class.hIconSm       = LoadIcon(hInstance,IDI_APPLICATION);
        //창 좌상단에 뜨는 작은 아이콘 

        RegisterClassEx(&Class);
    }
    { //생성자를 통한 인스턴스 생성
        CREATESTRUCT Window = CREATESTRUCT();
        //CREATESTUCT 특수목적으로 생성
        //함수 인자전달시 순서가 뒤바뀌므로 역순으로 구성되어있다
        Window.dwExStyle        = 0;//WS_EX_TOPMOST;//항상 위에
        Window.lpszClass        = "Window";  //String terminated by Zero
        Window.lpszName         = "Game";    //-> null로 끝나는 문자열
        Window.style            = WS_OVERLAPPEDWINDOW; //뒤에 윈도우 붙어야함
        //안하면 민무늬 토기 나옴, 여러가지 내용이 하나로 묶여있다
        /*(WS_OVERLAPPED     | \   0000 명목상
           WS_CAPTION        | \   
           WS_SYSMENU        | \
           WS_THICKFRAME     | \   창경계에서 창 크기 조절 기능
           WS_MINIMIZEBOX    | \   최소화 버튼
           WS_MAXIMIZEBOX)*/      

        //WS_POPUP //경계없는 창모드, 따로 빠져나가서 타이틀바를 만들어줄 필요가 있다
        
        Window.x                = 0; //CW_USEDEFAULT; 디폴트 창 설정
        Window.y                = 0; //CW_USEDEFAULT;
        Window.cx               = 640;
        Window.cy               = 480;
        Window.hwndParent       = HWND(); //nullptr
        Window.hMenu            = HMENU();
        Window.hInstance        = hInstance;
        Window.lpCreateParams   = nullptr;
        //추가 인자 전달용도로 사용

        {//윈도우 작업공간 맞추기
            RECT Rectangle = RECT();
            

            Rectangle.left   = 0;
            Rectangle.top    = 0;      
            Rectangle.right  = Window.cx;
            Rectangle.bottom = Window.cy;

            AdjustWindowRectEx(&Rectangle, Window.style, static_cast<bool>(Window.hMenu), Window.dwExStyle);
            //cx cy에 대해서 윈도우 스타일에 맞게 재작성해준다
            Window.cx = Rectangle.right - Rectangle.left;
            Window.cy = Rectangle.bottom - Rectangle.top;

            //화면 가운데로 세팅
            Window.x = (GetSystemMetrics(SM_CXSCREEN) - Window.cx) / 2; //SM_CXSCREEN 화면해상도 크기를 받아온다 
            Window.y = (GetSystemMetrics(SM_CYSCREEN) - Window.cy) / 2;
        }
        
        hWindow = CreateWindowEx  //WndProc 포인터 지정 없으면 여기서 오류!
        (//CreateWindowEx 논큐 메세지(메세지는 큐와 논큐 메세지로 나뉜다)
            //create은 큐를 거치지 않고 넘어감
            Window.dwExStyle,
            Window.lpszClass,
            Window.lpszName,
            Window.style,
            Window.x,
            Window.y,
            Window.cx,
            Window.cy,
            Window.hwndParent,
            Window.hMenu,
            Window.hInstance,
            Window.lpCreateParams
        ); //마지막 세미콜론을 다시 붙이면 기본문자 세팅으로..

        ShowWindow(hWindow, SW_RESTORE); //showcmd -> SW_ ...
    }   //SW_RESTORE 창 옵션 지정 못하게 막기

    {
        MSG Message = MSG();


        //메세지 큐에서 getmessage로 받아온다
        //WM_QUIT 은 getmessage가 false를 반환 (반복문 탈출)
        //while (GetMessage(&Message, HWND(), WM_NULL, WM_NULL)) //몇번 메세지부터 몇번 메세지 까지
        //    DispatchMessage(&Message); //보내다, 파견하다 =>메세지 프로시저
        //우리가 작성한 프로시저로!
    //GetMessage(&Message, HWND(), WM_NULL, WM_NULL)
        //특정 메세지는 어느 윈도우에서 어떤 윈도우 메세지까지 받을지
        while (true)
        {
            HDC hDC = GetDC(hWindow);
            
            if (PeekMessage(&Message, HWND(), WM_NULL, WM_NULL, PM_REMOVE))
            {
                if(Message.message ==WM_QUIT)
                    return static_cast<int>(Message.wParam);   //WM_QUIT 의 wParam 0 전달
                TextOut(hDC, 20, 20, "True  ", 6);

                DispatchMessage(&Message);
            }   
            else
            {
                //메세지가 없을때 (갱신 처리)
                TextOut(hDC, 20,20, "False",5);
                //디바이스 컨텍스트(gdi 출력옵션) 핸들
                //그래픽스 디바이스 인터페이스에서 제공하는 텍스트 출력
            }
            ReleaseDC(hWindow, hDC);
        }

    }

}