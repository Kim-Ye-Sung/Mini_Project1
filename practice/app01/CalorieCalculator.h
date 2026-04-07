#pragma once

#include "Calculator.h"
#include <mutex>

class CalorieCalculator : public Calculator
{
private:
	double Calorie = 0.0f;
	double CurrentSpeed = 0.0f;
	int UpdateCycle = 200;

	mutable std::mutex CalorieMutex;

	std::string ChangeToText() override;
	void StartRunning() override;
	void IncreaseCalorie();
	double KcalCalculate();

public:
	void SetCurrentSpeed(double Speed);
};