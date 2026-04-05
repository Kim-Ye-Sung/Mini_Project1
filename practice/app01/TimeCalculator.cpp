#include "TimeCalculator.h"

void TimeCalculator::InCreaseRunTime()
{
	while (true)
	{
		this_thread::sleep_for(chrono::seconds(1));		// 1초후에 1초 올리기
		RunTime += 1;
	}
}

string TimeCalculator::TimeCal()
{
    int hour = RunTime / 3600;
    int min = (RunTime % 3600) / 60;
    int sec = RunTime % 60;

    stringstream TimeString;
    TimeString << std::setw(2) << std::setfill('0') << hour << ":"  // 시간을 나타내는데 두자리수로 나타내며, 빈자리를 0으로 표시
        << std::setw(2) << std::setfill('0') << min << ":"
        << std::setw(2) << std::setfill('0') << sec;

    return TimeString.str();
}