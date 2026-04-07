#pragma once

#include "Calculator.h"
#include <mutex>   // [추가]

class TimeCalculator : public Calculator
{
private:
	int RunTime = 0;

	mutable std::mutex TimeMutex;   // [추가]

	std::string ChangeToText() override;

	void StartRunning() override;

	void IncreaseRunTime();
};