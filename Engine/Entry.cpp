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

/*Register -> create -> show -> run -> close -> destroy -> unregister */
#pragma warning(push,0)

LRESULT CALLBACK WndProc
(
    HWND   const hWindow,
    UINT   const uMessage,
    WPARAM const wParameter,
    LPARAM const lParameter

//HWND hwnd; ������ �ڵ� ��� �����쿡�� �߻��� �޼����ΰ�
//UINT message; ������ �޼��� WM_ ...�� ��´�
//WPARAM wParam; Ư�� �޼����� ���� 
//LPARAM lParam; �ش� �޼����� ���� ���������� ��´�
//DWORD time; �߻��ð�
//POINT pt;
)
{
    switch (uMessage)
    {
        case WM_LBUTTONDOWN:
        //case WM_LBUTTONUP:
        {
            //TODO: ������ �󿡼� ���콺 ���� ��ư Ŭ����
                //"Window has been clicked!","Click!" �޼��� �ڽ� �̿�
            MessageBox(hWindow, "Window has been clicked!", "Click!", MB_OK);
            return 0;

        }
        case WM_DESTROY:
        {
            MessageBox(hWindow, "Destroy", "Message box", MB_OK);

            PostQuitMessage(0); //���� ���μ������� �����
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
    {//���Ŀ� ���� ����
        WNDCLASSEX Class = WNDCLASSEX();

        Class.cbSize        = sizeof(WNDCLASSEX);  //������ ������ ����
        Class.style         = 0;  //��ȣ���� ������ ������ Ŭ���� ��Ÿ��
        Class.lpfnWndProc   = WndProc;
        Class.cbClsExtra    = 0; //Ŭ������ ���� �޸�
        Class.cbWndExtra    = 0; //�������� ���� �޸�
        Class.hInstance     =hInstance; //�ν��Ͻ� �ڵ� (��� �ν��Ͻ� �Ҽ��ΰ�)
        Class.hIcon         = LoadIcon(hInstance, IDI_APPLICATION);  //������ ��� ������
        //�Ϲ����� ���ø����̼� ������ ���
        Class.hCursor       = LoadCursor(hInstance, IDC_ARROW); //���콺 ��� ������
        Class.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
        //��� �귯�� �ڵ�
        Class.lpszMenuName  = nullptr;
        //sz => string terminated by zero =>�⺻ ĳ���͹迭 ���ڿ� ���� ��
        Class.lpszClassName = "Window";
        /*Ŭ���� ���� ���� like (class name)*/
        Class.hIconSm       = LoadIcon(hInstance,IDI_APPLICATION);
        //â �»�ܿ� �ߴ� ���� ������ 

        RegisterClassEx(&Class);
    }
    { //�����ڸ� ���� �ν��Ͻ� ����
        CREATESTRUCT Window = CREATESTRUCT();
        //CREATESTUCT Ư���������� ����
        Window.dwExStyle        = 0;//WS_EX_TOPMOST;//�׻� ����
        Window.lpszClass        ="Window";  //String terminated by Zero
        Window.lpszName         ="Game";    //-> null�� ������ ���ڿ�
        Window.style            =WS_OVERLAPPEDWINDOW; //�ڿ� ������ �پ����
                                                        //���ϸ� �ι��� ��� ����
        Window.x                = 0;
        Window.y                = 0;
        Window.cx               = 500;
        Window.cy               = 500;
        Window.hwndParent       = HWND(); //nullptr
        Window.hMenu            = HMENU();
        Window.hInstance        = hInstance;
        Window.lpCreateParams   = nullptr;

        hWindow = CreateWindowEx  //WndProc ������ ���� ������ ���⼭ ����!
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
        ); //������ �����ݷ��� �ٽ� ���̸� �⺻���� ��������..

        ShowWindow(hWindow, nShowCmd); //showcmd -> SW_ ...
    }

    {
        MSG Message = MSG();


        //�޼��� ť���� getmessage�� �޾ƿ´�
        //WM_QUIT �� getmessage�� false�� ��ȯ (�ݺ��� Ż��)
        while (GetMessage(&Message, HWND(), WM_NULL, WM_NULL) == true) //��� �޼������� ��� �޼��� ����
            DispatchMessage(&Message); //������, �İ��ϴ� =>�޼��� ���ν���
        //�츮�� �ۼ��� ���ν�����!
    
        return Message.wParam;
    }

}