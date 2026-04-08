#pragma once

#include "Calculator.h"

class DistanceCalculator : public Calculator
{
private:
	double Distance = 0.0f;

	double CurrentSpeed = 0.0f;

	void StartRunning() override;

	void IncreaseDistance();

	double DistanceCalculate();
public:

	inline void SetCurrentSpeed(double Speed) { CurrentSpeed = Speed; }

	inline double GetDistance() const { return Distance; }
};