#include "TimeCalculator.h"

void TimeCalculator::InCreaseRunTime()
{
	while (true)
	{
		this_thread::sleep_for(chrono::seconds(1));		// 1초후에 1 올리기
		RunTime += 1;
	}
}

string TimeCalculator::TimeCal()
{
    int hour = RunTime / 3600;
    int min = (RunTime % 3600) / 60;
    int sec = RunTime % 60;

    stringstream TimeString;
    TimeString << std::setw(2) << std::setfill('0') << hour << ":"  // 시간,분,초 단위를 두자리씩 표기하며, 빈자리는 0으로 채워서 나타내기
        << std::setw(2) << std::setfill('0') << min << ":"
        << std::setw(2) << std::setfill('0') << sec;

    return TimeString.str();
}