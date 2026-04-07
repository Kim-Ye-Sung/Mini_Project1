 #pragma once

#include "Calculator.h"

class CalorieCalculator : public Calculator
{
private:
	double Calorie = 0.0f;

	double CurrentSpeed = 0.0f;

	std::string ChangeToText() override;

	void StartRunning() override;

	void IncreaseCalorie();

	const int UpdateCycle = 200;  // 칼로리 계산시 갱신 주기. 200 = 0.2초

	double KcalCalculate();

public:

	inline void SetCurrentSpeed(double Speed) { CurrentSpeed = Speed; }

};