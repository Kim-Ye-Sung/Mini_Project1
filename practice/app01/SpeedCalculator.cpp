#include "SpeedCalculator.h"
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

string SpeedCalculator::ChangeToText()
{
	stringstream SpeedText;
	SpeedText << fixed		// 고정 소수점
			  << setprecision(1)   // 소수점 2자리까지 표기
			  << setw(4)   // . 까지 포함하여 6자리 나타내기
			  << setfill('0')  // 비어있는 곳은 0으로 표기
			  << Speed << " km/h";

	return SpeedText.str();
}

void SpeedCalculator::RunningStart()
{
	if (GetIsStart())
	{
		return;
	}

	Calculator::RunningStart();

	Speed = 4.0f;       // 런닝머신을 작동시작시에는 기본적으로 4km/h의 속도로 시작
	Invoke();
}

void SpeedCalculator::Invoke()
{
	Calculator::Invoke();

	for (auto& func : Speedlisteners)
	{
		func(Speed);
	}
}

void SpeedCalculator::Speed_Up()
{
	if (!GetIsStart())
	{
		return;
	}

	Speed += 0.1f;
	Invoke();
}

void SpeedCalculator::Speed_Down()
{
	if (!GetIsStart())
	{
		return;
	}

	Speed -= 0.1f;
	Invoke();
}

void SpeedCalculator::SetSpeed(double Speed)
{
	if (!GetIsStart())
	{
		return;
	}

	Speed = Speed;
	Invoke();
}

void SpeedCalculator::AddFunction(std::function<void(double)> func)
{
	Speedlisteners.push_back(func);
}
