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

*/

//winapi -> __stdcall
int APIENTRY WinMain
(
    _In_     HINSTANCE  const hInstance, //nullptr 불허함 _in_ 포인터 형식에 대해서만!
    _In_opt_ HINSTANCE  const hPrevInstance, //_In_ 옵셔널 널포인터 허용
    _In_     LPSTR      const lpCmdLine, //추가되는 커맨드 라인을 받는다
    _In_     int        const nShowCmd //실행탭에 어떤설정을 한상태로 실행 되었는지 전달
)
{
    //_Outptr_ 
    //WinMain(nullptr, nullptr, nullptr, 0);


    return 0;
}