#include "DistanceCalculator.h"
#include <thread>
#include <chrono>

using namespace std;

void DistanceCalculator::StartRunning()
{
	if (GetIsStart())
	{
		return;
	}

	Calculator::StartRunning();

	Distance = 0.0f;

	thread t(&DistanceCalculator::IncreaseDistance, this);
	t.detach();
}

void DistanceCalculator::IncreaseDistance()
{
	while (true)
	{
		this_thread::sleep_for(chrono::milliseconds(GetUpdateCycle()));	// 거리계산 갱신을 주기적으로 실행

		if (!GetIsStart())	// 주기가 지나기 전에 런닝머신이 종료되면 거리갱신 하지않음
		{
			return;
		}

		Distance += DistanceCalculate();   // 속도에 따라 거리갱신
		Invoke(Distance);		// 거리갱신 됐다고 알림
	}
}

double DistanceCalculator::DistanceCalculate()
{	
	double DistanceInInterval = 0.0f;

	DistanceInInterval = CurrentSpeed * (((double)GetUpdateCycle() / 1000) / 3600);

	return DistanceInInterval;
}

