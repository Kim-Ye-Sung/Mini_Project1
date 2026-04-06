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
				 << setprecision(2) // 소수점 2자리
				 << setw(6)         // 전체 폭 (000.00  == .을 포함한6자리)
				 << setfill('0')    // 빈 자리 0으로 채움
				 << Distance << " km";

	return DistanceText.str();
}

void DistanceCalculator::RunningStart()
{
	if (GetIsStart())
	{
		return;
	}

	Calculator::RunningStart();

	thread t(&DistanceCalculator::IncreaseDistance, this);
	t.detach();
}

void DistanceCalculator::IncreaseDistance()
{
	while (GetIsStart())
	{
		this_thread::sleep_for(chrono::milliseconds(200));
		Distance += CurrentSpeed / 100;
		Invoke();
	}
}

