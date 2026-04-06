#include "TimeCalculator.h"
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

void TimeCalculator::IncreaseRunTime()
{
	while (true)     // IsStart가 true이면 
	{
        while (IsStart)
        {
            this_thread::sleep_for(chrono::seconds(1));		// 1초 후에 RunTime을 1올리기
            RunTime += 1;
            Invoke();
        }
    }
}

string TimeCalculator::TimeCal()
{
    int hour = RunTime / 3600;          // 시간
    int min = (RunTime % 3600) / 60;    // 분
    int sec = RunTime % 60;             // 초

    stringstream TimeString;
    TimeString << setw(2) << setfill('0') << hour << ":"  // 시간,분,초 단위를 두자리씩 표기하며, 빈자리는 0으로 채워서 나타내기
        << setw(2) << setfill('0') << min << ":"
        << setw(2) << setfill('0') << sec;

    return TimeString.str();
}

void TimeCalculator::Invoke()
{
    for (auto& func : listeners)
    {
        func(TimeCal());
    }
}

void TimeCalculator::AddFunction(function<void(string)> func)
{
    listeners.push_back(func);
}
