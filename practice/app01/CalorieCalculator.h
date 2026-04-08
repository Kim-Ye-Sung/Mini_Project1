 #pragma once

#include "Calculator.h"

class CalorieCalculator : public Calculator
{
private:
	double Calorie = 0.0f;

	double CurrentSpeed = 0.0f;

	void StartRunning() override;

	void IncreaseCalorie();

	double KcalCalculate();

public:

	inline void SetCurrentSpeed(double Speed) { CurrentSpeed = Speed; }

};