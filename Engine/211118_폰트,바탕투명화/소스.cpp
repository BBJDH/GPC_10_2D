#include <Windows.h>

LRESULT CALLBACK WndProc
(
    HWND   const hWindow,
    UINT   const uMessage,
    WPARAM const wParameter,   //word 파라메터 ->
    LPARAM const lParameter    //long 파라메터 -> 용량을 늘리고 데이터를 압축해서 전달
                                //메세지의 세부 정보를 전달
)
{
    switch (uMessage)
    {

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

        Class.cbSize = sizeof(WNDCLASSEX);  //윈도우 사이즈 지정
        Class.style = 0;  //부호없는 정수형, 윈도우 클래스 스타일
        Class.lpfnWndProc = WndProc;
        Class.cbClsExtra = 0; //클래스의 여분 메모리
        Class.cbWndExtra = 0; //윈도우의 여분 메모리
        Class.hInstance = hInstance; //인스턴스 핸들 (어느 인스턴스 소속인가)
        Class.hIcon = LoadIcon(hInstance, IDI_APPLICATION);  //아이콘 모양 뭐쓸래
        //일반적인 어플리케이션 아이콘 사용
        Class.hCursor = LoadCursor(hInstance, IDC_ARROW); //마우스 모양 뭐쓸래
        Class.hbrBackground = static_cast<HBRUSH>(GetStockObject(GRAY_BRUSH));
        //배경 브러쉬 핸들
        Class.lpszMenuName = nullptr;
        //sz => string terminated by zero =>기본 캐릭터배열 문자열 끝이 널
        Class.lpszClassName = "Window";
        /*클래스 네임 지정 like (class name)*/
        Class.hIconSm = LoadIcon(hInstance, IDI_APPLICATION);
        //창 좌상단에 뜨는 작은 아이콘 

        RegisterClassEx(&Class);
    }
    { //생성자를 통한 인스턴스 생성
        CREATESTRUCT Window = CREATESTRUCT();
        //CREATESTUCT 특수목적으로 생성
        //함수 인자전달시 순서가 뒤바뀌므로 역순으로 구성되어있다
        Window.dwExStyle = 0;//WS_EX_TOPMOST;//항상 위에
        Window.lpszClass = "Window";  //String terminated by Zero
        Window.lpszName = "Game";    //-> null로 끝나는 문자열
        Window.style = WS_OVERLAPPEDWINDOW; //뒤에 윈도우 붙어야함

        Window.x = 0; //CW_USEDEFAULT; 디폴트 창 설정
        Window.y = 0; //CW_USEDEFAULT;
        Window.cx = 640;
        Window.cy = 480;
        Window.hwndParent = HWND(); //nullptr
        Window.hMenu = HMENU();
        Window.hInstance = hInstance;
        Window.lpCreateParams = nullptr;
        //추가 인자 전달용도로 사용

        {//윈도우 작업공간 맞추기
            RECT Rectangle = RECT();


            Rectangle.left = 0;
            Rectangle.top = 0;
            Rectangle.right = Window.cx;
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


        while (true)
        {
            HDC hDC = GetDC(hWindow);

            HFONT font = HFONT();
            {
                Addf
                LOGFONT logicalfont = LOGFONT();   //폰트 설정 생성

                logicalfont.lfHeight = 24;//font size
                logicalfont.lfWidth  = 0; //default 같이 자연스러운 너비값
                logicalfont.lfEscapement =0; //문장 전체 회전
                logicalfont.lfOrientation =0; //글자에 대한 회전
                logicalfont.lfWeight =FW_HEAVY; //두께
                logicalfont.lfItalic = false;//기울임 사실상 bool 타입
                logicalfont.lfUnderline = false;  //밑줄
                logicalfont.lfStrikeOut = false;  //취소선

                //폰트 탐색 facename(폰트네임)  찾으려는 상세값을 할당,
                //사실 네임만 명확하게 명시해도 됨
                logicalfont.lfCharSet = DEFAULT_CHARSET;  //문자 집합들중 설정
                logicalfont.lfOutPrecision = OUT_DEFAULT_PRECIS;
                logicalfont.lfClipPrecision = CLIP_DEFAULT_PRECIS;  //정밀도
                logicalfont.lfQuality = DEFAULT_QUALITY;
                logicalfont.lfPitchAndFamily = DEFAULT_PITCH| FF_DONTCARE;
                strcpy_s(logicalfont.lfFaceName, 32, "궁서");
                font = CreateFontIndirect(&logicalfont);
            }
            HFONT oldfont = HFONT();
            oldfont =static_cast<HFONT>( SelectObject(hDC, font));  //기존 오브젝트를 반환하므로 설정값을 기억 할수도 있음
            SetBkColor(hDC, RGB(220, 20, 60));
            //COLORREF bkcolor = RGB(220,20,60); //함수는 rgb    색상코드는B G R (3c14dc)


            //bkcolor = SetBkColor(hDC, bkcolor);//기존에 설정 되어있던 색을 돌려받고 새 색으로 바꿈 (기존값을 기억하기위해)
            if (PeekMessage(&Message, HWND(), WM_NULL, WM_NULL, PM_REMOVE))
            {
                if (Message.message == WM_QUIT)
                    return static_cast<int>(Message.wParam);   //WM_QUIT 의 wParam 0 전달
                //SetBkMode(hDC, TRANSPARENT);  //배경 투명화
                TextOut(hDC, 20, 20, "True  ", 6);

                DispatchMessage(&Message);
            }
            else
            {
                //SetBkMode(hDC, OPAQUE);  //배경 투명화
                //메세지가 없을때 (갱신 처리)
                TextOut(hDC, 20, 20, "False", 5);
                //디바이스 컨텍스트(gdi 출력옵션) 핸들
                //그래픽스 디바이스 인터페이스에서 제공하는 텍스트 출력
            }
            DeleteObject(font);  //selectobject 이후 해제가 항상 필요함
            
            ReleaseDC(hWindow, hDC);
        }

    }

}