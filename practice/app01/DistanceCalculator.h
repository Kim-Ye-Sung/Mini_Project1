#pragma once

#include "Calculator.h"
#include <mutex>   // [추가]

class DistanceCalculator : public Calculator
{
private:
	double Distance = 0.0f;

	double CurrentSpeed = 0.0f;

	int UpdateCycle = 200;

	mutable std::mutex DistanceMutex;   // [추가]

	std::string ChangeToText() override;

	void StartRunning() override;

	void IncreaseDistance();

public:
	void SetCurrentSpeed(double Speed);   // [수정] inline 제거
};