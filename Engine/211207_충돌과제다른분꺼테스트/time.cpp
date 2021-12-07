#include<Windows.h>

#include<chrono>

namespace Time
{
	namespace  //�͸� ���ӽ����̽� - ���� static ȭ
	{
		std::chrono::steady_clock::time_point const started =
			std::chrono::steady_clock::now();
		std::chrono::steady_clock::time_point updated =
			std::chrono::steady_clock::now();
		float Elapsed = float();
		float Delta = float();

		float interval = 0;
		float const speed = 0.03f;

		float Shape_interval = 0;
		float Shape_regenspeed = 3.0f;
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
				 //count() ->���� ������ long long ��
				 Delta   = duration_cast<duration<float>>(steady_clock::now() - updated).count();
				 updated = std::chrono::steady_clock::now();
				return;
			}

		}
	}
	bool isregentime()
	{
		Shape_interval += Delta;
		if (Shape_interval > Shape_regenspeed)
		{
			Shape_interval = 0;
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