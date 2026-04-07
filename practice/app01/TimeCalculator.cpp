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
		this_thread::sleep_for(chrono::seconds(1));

		if (!GetIsStart())
		{
			return;
		}

		{
			lock_guard<mutex> lock(TimeMutex);   // [추가]
			RunTime += 1;
		}

		Invoke();
	}
}

void TimeCalculator::StartRunning()
{
	if (GetIsStart())
	{
		return;
	}

	Calculator::StartRunning();

	{
		lock_guard<mutex> lock(TimeMutex);   // [추가]
		RunTime = 0;
	}

	thread t(&TimeCalculator::IncreaseRunTime, this);
	t.detach();
}

string TimeCalculator::ChangeToText()
{
	int localRunTime;   // [추가]

	{
		lock_guard<mutex> lock(TimeMutex);   // [추가]
		localRunTime = RunTime;
	}

	int hour = localRunTime / 3600;
	int min = (localRunTime % 3600) / 60;
	int sec = localRunTime % 60;

	stringstream TimeText;
	TimeText << setw(2) << setfill('0') << hour << ":"
		<< setw(2) << setfill('0') << min << ":"
		<< setw(2) << setfill('0') << sec;

	return TimeText.str();
}