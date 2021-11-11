#include <Windows.h>

/*
ȣ�� �Ծ�(Calling convention)

winapi �Ⱦ��� cdecl �� �Ͻ������� ����
       cdecl : Cdeclaration. c/c++�� �⺻ ȣ�� �Ծ�.
     stdcall : Standard Call. Windows API�� �⺻ ȣ�� �Ծ�.
    thiscall : ��� �Լ��� �⺻ ȣ�� �Ծ�.

*/
/*

Source Annotation Language, SAL
�ҽ� �ڵ� �ּ� ���

*/

//winapi -> __stdcall
int APIENTRY WinMain
(
    _In_     HINSTANCE  const hInstance, //nullptr ������ _in_ ������ ���Ŀ� ���ؼ���!
    _In_opt_ HINSTANCE  const hPrevInstance, //_In_ �ɼų� �������� ���
    _In_     LPSTR      const lpCmdLine, //�߰��Ǵ� Ŀ�ǵ� ������ �޴´�
    _In_     int        const nShowCmd //�����ǿ� ������� �ѻ��·� ���� �Ǿ����� ����
)
{
    //_Outptr_ 
    //WinMain(nullptr, nullptr, nullptr, 0);


    return 0;
}