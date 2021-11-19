#include <Windows.h>

LRESULT CALLBACK WndProc
(
    HWND   const hWindow,
    UINT   const uMessage,
    WPARAM const wParameter,   //word �Ķ���� ->
    LPARAM const lParameter    //long �Ķ���� -> �뷮�� �ø��� �����͸� �����ؼ� ����
                                //�޼����� ���� ������ ����
)
{
    switch (uMessage)
    {

    case WM_LBUTTONDOWN:
        //case WM_LBUTTONUP:
    {

        //"Window has been clicked!","Click!" �޼��� �ڽ� �̿�
        MessageBox(hWindow, "Window has been clicked!", "Click!", MB_OK);
        return 0;

    }
    case WM_DESTROY: //�Ҹ��� ����
    {
        MessageBox(hWindow, "Destroy", "Message box", MB_ICONWARNING | MB_OK);

        PostQuitMessage(0); //���� ���μ������� �����
        //WM_QUIT �޼��� �߻�

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

        Class.cbSize = sizeof(WNDCLASSEX);  //������ ������ ����
        Class.style = 0;  //��ȣ���� ������, ������ Ŭ���� ��Ÿ��
        Class.lpfnWndProc = WndProc;
        Class.cbClsExtra = 0; //Ŭ������ ���� �޸�
        Class.cbWndExtra = 0; //�������� ���� �޸�
        Class.hInstance = hInstance; //�ν��Ͻ� �ڵ� (��� �ν��Ͻ� �Ҽ��ΰ�)
        Class.hIcon = LoadIcon(hInstance, IDI_APPLICATION);  //������ ��� ������
        //�Ϲ����� ���ø����̼� ������ ���
        Class.hCursor = LoadCursor(hInstance, IDC_ARROW); //���콺 ��� ������
        Class.hbrBackground = static_cast<HBRUSH>(GetStockObject(GRAY_BRUSH));
        //��� �귯�� �ڵ�
        Class.lpszMenuName = nullptr;
        //sz => string terminated by zero =>�⺻ ĳ���͹迭 ���ڿ� ���� ��
        Class.lpszClassName = "Window";
        /*Ŭ���� ���� ���� like (class name)*/
        Class.hIconSm = LoadIcon(hInstance, IDI_APPLICATION);
        //â �»�ܿ� �ߴ� ���� ������ 

        RegisterClassEx(&Class);
    }
    { //�����ڸ� ���� �ν��Ͻ� ����
        CREATESTRUCT Window = CREATESTRUCT();
        //CREATESTUCT Ư���������� ����
        //�Լ� �������޽� ������ �ڹٲ�Ƿ� �������� �����Ǿ��ִ�
        Window.dwExStyle = 0;//WS_EX_TOPMOST;//�׻� ����
        Window.lpszClass = "Window";  //String terminated by Zero
        Window.lpszName = "Game";    //-> null�� ������ ���ڿ�
        Window.style = WS_OVERLAPPEDWINDOW; //�ڿ� ������ �پ����

        Window.x = 0; //CW_USEDEFAULT; ����Ʈ â ����
        Window.y = 0; //CW_USEDEFAULT;
        Window.cx = 640;
        Window.cy = 480;
        Window.hwndParent = HWND(); //nullptr
        Window.hMenu = HMENU();
        Window.hInstance = hInstance;
        Window.lpCreateParams = nullptr;
        //�߰� ���� ���޿뵵�� ���

        {//������ �۾����� ���߱�
            RECT Rectangle = RECT();


            Rectangle.left = 0;
            Rectangle.top = 0;
            Rectangle.right = Window.cx;
            Rectangle.bottom = Window.cy;

            AdjustWindowRectEx(&Rectangle, Window.style, static_cast<bool>(Window.hMenu), Window.dwExStyle);
            //cx cy�� ���ؼ� ������ ��Ÿ�Ͽ� �°� ���ۼ����ش�
            Window.cx = Rectangle.right - Rectangle.left;
            Window.cy = Rectangle.bottom - Rectangle.top;

            //ȭ�� ����� ����
            Window.x = (GetSystemMetrics(SM_CXSCREEN) - Window.cx) / 2; //SM_CXSCREEN ȭ���ػ� ũ�⸦ �޾ƿ´� 
            Window.y = (GetSystemMetrics(SM_CYSCREEN) - Window.cy) / 2;
        }

        hWindow = CreateWindowEx  //WndProc ������ ���� ������ ���⼭ ����!
        (//CreateWindowEx ��ť �޼���(�޼����� ť�� ��ť �޼����� ������)
            //create�� ť�� ��ġ�� �ʰ� �Ѿ
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

        ShowWindow(hWindow, SW_RESTORE); //showcmd -> SW_ ...
    }   //SW_RESTORE â �ɼ� ���� ���ϰ� ����

    {
        MSG Message = MSG();


        while (true)
        {
            HDC hDC = GetDC(hWindow);

            HFONT font = HFONT();
            {
                Addf
                LOGFONT logicalfont = LOGFONT();   //��Ʈ ���� ����

                logicalfont.lfHeight = 24;//font size
                logicalfont.lfWidth  = 0; //default ���� �ڿ������� �ʺ�
                logicalfont.lfEscapement =0; //���� ��ü ȸ��
                logicalfont.lfOrientation =0; //���ڿ� ���� ȸ��
                logicalfont.lfWeight =FW_HEAVY; //�β�
                logicalfont.lfItalic = false;//����� ��ǻ� bool Ÿ��
                logicalfont.lfUnderline = false;  //����
                logicalfont.lfStrikeOut = false;  //��Ҽ�

                //��Ʈ Ž�� facename(��Ʈ����)  ã������ �󼼰��� �Ҵ�,
                //��� ���Ӹ� ��Ȯ�ϰ� ����ص� ��
                logicalfont.lfCharSet = DEFAULT_CHARSET;  //���� ���յ��� ����
                logicalfont.lfOutPrecision = OUT_DEFAULT_PRECIS;
                logicalfont.lfClipPrecision = CLIP_DEFAULT_PRECIS;  //���е�
                logicalfont.lfQuality = DEFAULT_QUALITY;
                logicalfont.lfPitchAndFamily = DEFAULT_PITCH| FF_DONTCARE;
                strcpy_s(logicalfont.lfFaceName, 32, "�ü�");
                font = CreateFontIndirect(&logicalfont);
            }
            HFONT oldfont = HFONT();
            oldfont =static_cast<HFONT>( SelectObject(hDC, font));  //���� ������Ʈ�� ��ȯ�ϹǷ� �������� ��� �Ҽ��� ����
            SetBkColor(hDC, RGB(220, 20, 60));
            //COLORREF bkcolor = RGB(220,20,60); //�Լ��� rgb    �����ڵ��B G R (3c14dc)


            //bkcolor = SetBkColor(hDC, bkcolor);//������ ���� �Ǿ��ִ� ���� �����ް� �� ������ �ٲ� (�������� ����ϱ�����)
            if (PeekMessage(&Message, HWND(), WM_NULL, WM_NULL, PM_REMOVE))
            {
                if (Message.message == WM_QUIT)
                    return static_cast<int>(Message.wParam);   //WM_QUIT �� wParam 0 ����
                //SetBkMode(hDC, TRANSPARENT);  //��� ����ȭ
                TextOut(hDC, 20, 20, "True  ", 6);

                DispatchMessage(&Message);
            }
            else
            {
                //SetBkMode(hDC, OPAQUE);  //��� ����ȭ
                //�޼����� ������ (���� ó��)
                TextOut(hDC, 20, 20, "False", 5);
                //����̽� ���ؽ�Ʈ(gdi ��¿ɼ�) �ڵ�
                //�׷��Ƚ� ����̽� �������̽����� �����ϴ� �ؽ�Ʈ ���
            }
            DeleteObject(font);  //selectobject ���� ������ �׻� �ʿ���
            
            ReleaseDC(hWindow, hDC);
        }

    }

}