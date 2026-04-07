#pragma once

#include "Calculator.h"


class TimeCalculator : public Calculator
{
private :
	int RunTime = 0;

	std::string ChangeToText() override;

	void StartRunning() override;

	void IncreaseRunTime();

public:
	inline int GetRunTime() const { return RunTime; }
};