#include "TimeCalculator.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <sstream>
#include <iomanip>

using namespace std;

void TimeCalculator::IncreaseRunTime()
{
	while (true)
	{	
		// 0.1초 정지를 10번돌면 1초로 계산
		for (int i = 0; i < 10; i++)
		{
			if (!GetIsStart())	// 1초가 되기전에 런닝머신의 작동이 중단되면 시간계산 끝냄
			{
				return;
			}

			this_thread::sleep_for(chrono::milliseconds(100));	// 0.1초 정지
		}

		RunTime += 1;	// 1초를 더함
		Invoke();		// 바뀐 시간을 알림
	}
}

void TimeCalculator::RunningStart()
{
	if (GetIsStart())
	{
		return;
	}

	Calculator::RunningStart();

	thread t(&TimeCalculator::IncreaseRunTime, this);
	t.detach();
}

string TimeCalculator::ChangeToText()
{
	int hour = RunTime / 3600;          // 시간
	int min = (RunTime % 3600) / 60;    // 분
	int sec = RunTime % 60;             // 초

	stringstream TimeText;
	TimeText << setw(2) << setfill('0') << hour << ":"  // 시간,분,초 단위를 두자리씩 표기하며, 빈자리는 0으로 채워서 나타내기
			 << setw(2) << setfill('0') << min << ":"
			 << setw(2) << setfill('0') << sec;

	return TimeText.str();
}






