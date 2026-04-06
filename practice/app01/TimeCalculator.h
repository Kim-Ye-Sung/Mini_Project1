#pragma once

#include "Calculator.h"


class TimeCalculator : public Calculator
{
private :
	int RunTime = 0;

	std::string ChangeToText() override;

	void RunningStart() override;

	void IncreaseRunTime();
};