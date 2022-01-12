#include"stdafx.h"

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
	HWND hgamewindow =HWND();

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

	CREATESTRUCT gamewindow = CREATESTRUCT();

	gamewindow.hInstance = hInstance;
	gamewindow.cx        = WINSIZE_X;
	gamewindow.cy        = WINSIZE_Y;
	gamewindow.lpszClass = "basic";
	gamewindow.lpszName  = "Fortress";
	gamewindow.style     = WS_OVERLAPPED | \
							WS_CAPTION | \
							WS_MINIMIZEBOX | \
							WS_SYSMENU;
	RECT workspace = RECT();
	workspace.right = gamewindow.cx;
	workspace.bottom = gamewindow.cy;

	AdjustWindowRectEx
	(
		&workspace,
		gamewindow.style,
		static_cast<bool>(gamewindow.hMenu),
		gamewindow.dwExStyle
	);
	gamewindow.cx = workspace.right - workspace.left;
	gamewindow.cy = workspace.bottom - workspace.top;

	gamewindow.x = (GetSystemMetrics(SM_CXSCREEN) -gamewindow.cx)/2;
	gamewindow.y = (GetSystemMetrics(SM_CYSCREEN) -gamewindow.cy)/2;

	hgamewindow = CreateWindowEx
	(
		gamewindow.dwExStyle,
		gamewindow.lpszClass,
		gamewindow.lpszName,
		gamewindow.style,
		gamewindow.x,
		gamewindow.y,
		gamewindow.cx,
		gamewindow.cy,
		gamewindow.hwndParent,
		gamewindow.hMenu,
		gamewindow.hInstance,
		gamewindow.lpCreateParams
	);
	ShowWindow(hgamewindow,SW_RESTORE);
	MSG msg = MSG();
	RECT Clip;
	GetClientRect(hgamewindow, &Clip);
	ClientToScreen(hgamewindow, (LPPOINT)&Clip);
	ClientToScreen(hgamewindow, (LPPOINT)(&Clip.right));
	ClipCursor(&Clip);
	while (true)
	{
		if(PeekMessage(&msg,hgamewindow,WM_NULL, WM_NULL,PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
				return static_cast<int>(msg.wParam);

			DispatchMessage(&msg);
		}
		else
		{
			SendMessage(hgamewindow,WM_APP,0,0);
		}

	}

	return 0;
}
