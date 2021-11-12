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

_In_ : ������ ������ ���ڿ� ���� nullptr�� ������� ����.
_In_opt_ : ������ ������ ���ڿ� ���� nullptr�� �����.

*/

//winapi -> __stdcall
int APIENTRY WinMain
(
    _In_     HINSTANCE  const hInstance, //nullptr ������ _in_ ������ ���Ŀ� ���ؼ���!
    _In_opt_ HINSTANCE  const hPrevInstance, //_In_ �ɼų� �������� ���
    _In_     LPSTR      const lpCmdLine, //�߰��Ǵ� Ŀ�ǵ� ������ �޴´�
    //LPSTR ->longptr string 
    _In_     int        const nShowCmd //�����ǿ� ������� �ѻ��·� ���� �Ǿ����� ����
)
{
    //_Outptr_ 
    //WinMain(nullptr, nullptr, nullptr, 0);
    //strcmp(lpCmdLine,"-w")

    HWND hWindow = HWND(); //������ â ����
    {
        WNDCLASSEX Class = WNDCLASSEX();

        Class.cbSize        = sizeof(WNDCLASSEX);  //������ ������ ����
        Class.style         = 0;  //��ȣ���� ������ ������ Ŭ���� ��Ÿ��
        Class.lpfnWndProc   = nullptr;
        Class.cbClsExtra    = 0;
        Class.cbWndExtra    = 0;
        Class.hInstance     =hInstance; //�ν��Ͻ� �ڵ� (��� �ν��Ͻ� �Ҽ��ΰ�)
        Class.hIcon         = LoadIcon(hInstance, IDI_APPLICATION); 
        //�Ϲ����� ���ø����̼� ������ ���
        Class.hCursor       = LoadCursor(hInstance, IDC_ARROW); 
        Class.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
        Class.lpszMenuName  = nullptr;
        //sz => string terminated by zero =>�⺻ ĳ���͹迭 ���ڿ� ���� ��
        Class.lpszClassName = "Window";
        /*Ŭ���� ���� ���� like (class name)*/
        Class.hIconSm       = LoadIcon(hInstance,IDI_APPLICATION);
        //â �»�ܿ� �ߴ� ���� ������ 

        RegisterClassEx(&Class);
    }
    {
        CREATESTRUCT Window = CREATESTRUCT();

        Window.dwExStyle        = 0;//WS_EX_TOPMOST;//�׻� ����
        Window.lpszClass        ="Window";
        Window.lpszName         ="Game";
        Window.style            =WS_OVERLAPPEDWINDOW; //�ڿ� ������ �پ����

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