#include "SpeedCalculator.h"
#include <iostream>


using namespace std;

void SpeedCalculator::StartRunning()
{
	if (GetIsStart())
	{
		return;
	}

	Calculator::StartRunning();

	Speed = InitSpeed;       // 런닝머신을 작동시작시에는 기본적으로 InitialSpeed의 속도로 시작
	Invoke(Speed);
}

double SpeedCalculator::AvrSpeedCalcuate(double RunningDistance, double RunningTime)
{
	AverageSpeed = 0.0f;

	if (RunningTime > 0.0f)
	{
		AverageSpeed = RunningDistance / (RunningTime / 3600.0f);
	}

	return AverageSpeed;
}


void SpeedCalculator::Speed_Up()
{
	if (!GetIsStart())
	{
		return;
	}

	Speed += 0.1f;
	Invoke(Speed);
}

void SpeedCalculator::Speed_Down()
{
	if (!GetIsStart())
	{
		return;
	}

	Speed -= 0.1f;
	Invoke(Speed);
}

//void SpeedCalculator::SetSpeed(double Speed)
//{
//	if (!GetIsStart())
//	{
//		return;
//	}
//
//	this->Speed = Speed;
//	Invoke();
//}