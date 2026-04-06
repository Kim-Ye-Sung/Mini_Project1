#pragma once

#include "Calculator.h"

class DistanceCalculator : public Calculator
{
private:
	double Distance = 0.0f;

	double CurrentSpeed = 0.0f;

	std::string ChangeToText() override;

	void RunningStart() override;

public:
	void IncreaseDistance();

	inline void SetCurrentSpeed(double Speed) { CurrentSpeed = Speed; }

};