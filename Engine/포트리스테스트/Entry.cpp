#include<Windows.h>
#include<time.h>
namespace Engine{
	LRESULT CALLBACK Procedure
	(HWND , UINT , WPARAM , LPARAM );
}

int WINAPI WinMain
(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd
)
{
	srand(static_cast<unsigned>(time(NULL)));
	HWND hdodgewindow =HWND();

	WNDCLASSEX basic = WNDCLASSEX();

	basic.cbSize         = sizeof(WNDCLASSEX);
	basic.lpfnWndProc    = Engine::Procedure;
	basic.hInstance      = hInstance;
	basic.hIcon          = LoadIcon(hInstance,IDI_APPLICATION);
	basic.hCursor        = LoadCursor(hInstance,IDC_HAND);
	basic.hbrBackground  = static_cast<HBRUSH>(GetStockObject(RGB(255,0,255)));
	basic.lpszClassName  = "basic";
	basic.hIconSm        = LoadIcon(hInstance,IDI_APPLICATION);

	RegisterClassEx(&basic);

	CREATESTRUCT dodgewindow = CREATESTRUCT();

	dodgewindow.hInstance = hInstance;
	dodgewindow.cx        = 800;
	dodgewindow.cy        = 600;
	dodgewindow.lpszClass = "basic";
	dodgewindow.lpszName  = "Fortress";
	dodgewindow.style     = WS_OVERLAPPED | \
							WS_CAPTION | \
							WS_MINIMIZEBOX | \
							WS_SYSMENU;
	RECT workspace = RECT();
	workspace.right = dodgewindow.cx;
	workspace.bottom = dodgewindow.cy;

	AdjustWindowRectEx
	(
		&workspace,
		dodgewindow.style,
		static_cast<bool>(dodgewindow.hMenu),
		dodgewindow.dwExStyle
	);
	dodgewindow.cx = workspace.right - workspace.left;
	dodgewindow.cy = workspace.bottom - workspace.top;

	dodgewindow.x = (GetSystemMetrics(SM_CXSCREEN) -dodgewindow.cx)/2;
	dodgewindow.y = (GetSystemMetrics(SM_CYSCREEN) -dodgewindow.cy)/2;

	hdodgewindow = CreateWindowEx
	(
		dodgewindow.dwExStyle,
		dodgewindow.lpszClass,
		dodgewindow.lpszName,
		dodgewindow.style,
		dodgewindow.x,
		dodgewindow.y,
		dodgewindow.cx,
		dodgewindow.cy,
		dodgewindow.hwndParent,
		dodgewindow.hMenu,
		dodgewindow.hInstance,
		dodgewindow.lpCreateParams
	);
	ShowWindow(hdodgewindow,SW_RESTORE);
	MSG msg = MSG();
	while (true)
	{
		if(PeekMessage(&msg,hdodgewindow,WM_NULL, WM_NULL,PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
				return static_cast<int>(msg.wParam);

			DispatchMessage(&msg);
		}
		else
		{
			SendMessage(hdodgewindow,WM_APP,0,0);
		}

	}

	return 0;
}
