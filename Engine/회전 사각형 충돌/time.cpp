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

		float interval = 0;
		float const speed = 0.03f;

		float rect_interval = 0;
		float rect_regenspeed = 3.0f;
	}

	void Procedure
	(HWND   const hWindow, UINT   const uMessage, WPARAM const wParameter, LPARAM const lParameter)
	{
		switch (uMessage)
		{
			case WM_APP:
			{
				using namespace std::chrono;

				 Elapsed = duration_cast<duration<float>>(steady_clock::now() - started).count();
				 //count() ->나노 단위의 long long 값
				 Delta   = duration_cast<duration<float>>(steady_clock::now() - updated).count();
				 updated = std::chrono::steady_clock::now();
				return;
			}

		}
	}
	bool isregentime()
	{
		rect_interval += Delta;
		if (rect_interval > rect_regenspeed)
		{
			rect_interval = 0;
			return true;
		}
		return false;
	}
	bool isinterval()
	{
		interval += Delta;
		if (interval > speed)
		{
			interval = 0;
			return true;
		}
		return false;
	}

}