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
    {
        WNDCLASSEX Class = WNDCLASSEX();

        Class.cbSize        = sizeof(WNDCLASSEX);  //윈도우 사이즈 지정
        Class.style         = 0;  //부호없는 정수형 윈도우 클래스 스타일
        Class.lpfnWndProc   = nullptr;
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
    {
        CREATESTRUCT Window = CREATESTRUCT();

        Window.dwExStyle        = 0;//WS_EX_TOPMOST;//항상 위에
        Window.lpszClass        ="Window";
        Window.lpszName         ="Game";
        Window.style            =WS_OVERLAPPEDWINDOW; //뒤에 윈도우 붙어야함

        Window.x                ;
        Window.y                ;
        Window.cx               ;
        Window.cy               ;
        Window.hwndParent       ;
        Window.hMenu            ;
        Window.hInstance        ;
        Window.lpCreateParams   ;
    }

    return 0;
}