#include<Windows.h>

#include<chrono>

namespace Time
{
	namespace  //익명 네임스페이스 - 내부 static 화
	{
		std::chrono::steady_clock::time_point const started =
			std::chrono::steady_clock::now();
		std::chrono::steady_clock::time_point updated =
			std::chrono::steady_clock::now();
		float Elapsed = float();
		float Delta = float();
	}

	void Procedure
	(HWND   const hWindow, UINT   const uMessage, WPARAM const wParameter, LPARAM const lParameter)
	{
		switch (uMessage)
		{
			case WM_APP:
			{
				using namespace std::chrono;

				 Elapsed = duration_cast<duration<float>>(steady_clock::now()-started).count();
				 //count() ->나노 단위의 long long 값
				 Delta   = duration_cast<duration<float>>(steady_clock::now() -updated).count();
				 updated = std::chrono::steady_clock::now();
				return;
			}

		}
	}

}