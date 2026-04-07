#pragma once

#include "Calculator.h"
#include <mutex>   // [추가]

class SpeedCalculator : public Calculator
{
private:
	double Speed = 0.0f;

	std::vector<std::function<void(double)>> Speedlisteners;

	mutable std::mutex SpeedMutex;   // [추가]

	std::string ChangeToText() override;

	void StartRunning() override;

	void Invoke() override;

public:
	void Speed_Up();

	void Speed_Down();

	void SetSpeed(double Speed);

	using Calculator::AddFunction;
	void AddFunction(std::function<void(double)> func);
};