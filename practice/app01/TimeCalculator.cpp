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
		this_thread::sleep_for(chrono::milliseconds(GetUpdateCycle()));	// 정지

		if (!GetIsStart())	// 1초가 되기전에 런닝머신의 작동이 중단되면 시간계산 끝냄
		{
			return;
		}

		RunTime += (double)GetUpdateCycle() / 1000;	// 주기만큼 더함

		if (RunTime - PrevRunTime >= 1.0f)	// 시간계산은 1초보다 짧은 주기로 계속 하지만, UI에 표시할때는 1초단위로만 함.
		{
			PrevRunTime += 1.0f;	// 다시 1초를 세기 위해 1올림

			Invoke();		// 바뀐 시간을 알림
		}
	}
}

void TimeCalculator::StartRunning()
{
	if (GetIsStart())
	{
		return;
	}

	Calculator::StartRunning();

	RunTime = 0.0f;
	PrevRunTime = 0.0f;

	thread t(&TimeCalculator::IncreaseRunTime, this);
	t.detach();
}

string TimeCalculator::ChangeToText()
{
	int hour = (int)RunTime / 3600;          // 시간
	int min = ((int)RunTime % 3600) / 60;    // 분
	int sec = (int)RunTime % 60;             // 초

	stringstream TimeText;
	TimeText << setw(2) << setfill('0') << hour << ":"  // 시간,분,초 단위를 두자리씩 표기하며, 빈자리는 0으로 채워서 나타내기
			 << setw(2) << setfill('0') << min << ":"
			 << setw(2) << setfill('0') << sec;

	return TimeText.str();
}






