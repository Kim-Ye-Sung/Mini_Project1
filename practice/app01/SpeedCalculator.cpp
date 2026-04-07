#include "SpeedCalculator.h"
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

string SpeedCalculator::ChangeToText()
{
	stringstream SpeedText;
	SpeedText << fixed		// 고정 소수점
			  << setprecision(1)   // 소수점 1자리까지 표기
			  << setw(4)   // . 까지 포함하여 4자리 나타내기
			  << setfill(' ')  // 비어있는 곳은 0으로 표기
			  << Speed << " km/h";

	return SpeedText.str();
}

void SpeedCalculator::StartRunning()
{
	if (GetIsStart())
	{
		return;
	}

	Calculator::StartRunning();

	Speed = InitSpeed;       // 런닝머신을 작동시작시에는 기본적으로 InitialSpeed의 속도로 시작
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

	this->Speed = Speed;
	Invoke();
}

std::string SpeedCalculator::ChangeToText(double RunningDistance, double RunningTime)
{
	double AverageSpeed = 0.0f;

	if (RunningTime > 0.0f)
	{
		AverageSpeed = RunningDistance / (RunningTime / 3600.0f);
	}

	stringstream AverageSpeedText;
	AverageSpeedText << fixed		// 고정 소수점
					 << setprecision(1)   // 소수점 1자리까지 표기
					 << setw(4)   // . 까지 포함하여 4자리 나타내기
					 << setfill(' ')  // 비어있는 곳은 0으로 표기
					 << AverageSpeed << " km/h";

	return AverageSpeedText.str();
}

void SpeedCalculator::AddFunction(std::function<void(double)> func)
{
	Speedlisteners.push_back(func);
}
