#include "DistanceCalculator.h"
#include <sstream>
#include <iomanip>
#include <thread>
#include <chrono>

using namespace std;

string DistanceCalculator::ChangeToText()
{
	std::stringstream DistanceText;

	DistanceText << fixed           // 고정 소수점
				 << setprecision(3) // 소수점 2자리
				 << setw(7)         // 전체 폭 (000.00  == .을 포함한6자리)
				 << setfill(' ')    // 빈 자리 0으로 채움
				 << Distance << " km";

	return DistanceText.str();
}

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

		Distance += CurrentSpeed * (((double)GetUpdateCycle() / 1000) / 3600);   // 속도에 따라 거리갱신
		Invoke();		// 거리갱신 됐다고 알림
	}
}

