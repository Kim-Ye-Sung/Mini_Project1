#pragma once

#include "Calculator.h"

class SpeedCalculator : public Calculator
{
private:
	double Speed = 0.0f;	 // 런닝머신의 현재 속도 변수

	double AverageSpeed = 0.0f;	 // 런닝머신 가동중 뛰었던 평균속도 변수

	const double InitSpeed = 4.0f;  // 런닝머신 작동시 시작 속도

	void StartRunning() override;

public:
	void Speed_Up();

	void Speed_Down();

	double AvrSpeedCalcuate(double RunningDistance, double RunningTime);

	//void SetSpeed(double Speed);
};