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
#pragma warning(push,0)

LRESULT CALLBACK WndProc
(
    HWND   const hWindow,
    UINT   const uMessage,
    WPARAM const wParameter,
    LPARAM const lParameter
)
{

    switch (uMessage)
    {
    case WM_LBUTTONDOWN:
    {
        //TODO: 윈도우 상에서 마우스 왼쪽 버튼 클릭시
            //"Window has been clicked!","Click!" 메세지 박스 이용 ㄱㄱ
        MessageBox(hWindow, "Destroy", "Message box", MB_OK);
    }
        case WM_DESTROY:
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
    int i = 0;
    HWND hWindow = HWND(); //윈도우 창 생성
    {//형식에 대한 정의
        WNDCLASSEX Class = WNDCLASSEX();

        Class.cbSize        = sizeof(WNDCLASSEX);  //윈도우 사이즈 지정
        Class.style         = 0;  //부호없는 정수형 윈도우 클래스 스타일
        Class.lpfnWndProc   = WndProc;
        Class.cbClsExtra    = 0;
        Class.cbWndExtra    = 0;
        Class.hInstance     =hInstance; //인스턴스 핸들 (어느 인스턴스 소속인가)
        Class.hIcon         = LoadIcon(hInstance, IDI_APPLICATION); 
        //일반적인 어플리케이션 아이콘 사용
        Class.hCursor       = LoadCursor(hInstance, IDC_ARROW); 
        Class.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
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
        Window.dwExStyle        = 0;//WS_EX_TOPMOST;//항상 위에
        Window.lpszClass        ="Window";
        Window.lpszName         ="Game";
        Window.style            =WS_OVERLAPPEDWINDOW; //뒤에 윈도우 붙어야함

        Window.x                = 0;
        Window.y                = 0;
        Window.cx               = 500;
        Window.cy               = 500;
        Window.hwndParent       = HWND(); //nullptr
        Window.hMenu            = HMENU();
        Window.hInstance        = hInstance;
        Window.lpCreateParams   = nullptr;

        hWindow = CreateWindowEx
        (
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

        ShowWindow(hWindow, nShowCmd); //showcmd -> SW_ ...
    }

    {
        MSG Message = MSG();


        //메세지 큐에서 getmessage로 받아온다
        while (GetMessage(&Message, HWND(), WM_NULL, WM_NULL) == true) //몇번 메세지부터 몇번 메세지 까지
            DispatchMessage(&Message); //보내다, 파견하다 =>메세지 프로시저
        //우리가 작성한 프로시저로!
    
        return Message.wParam;
    }

}