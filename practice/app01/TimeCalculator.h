#pragma once

#include "Calculator.h"


class TimeCalculator : public Calculator
{
private :
	double RunTime = 0.0f;

	double PrevRunTime = 0.0f;   // 1초가 지났는지 체크하기 위한 변수
	
	std::string ChangeToText() override;

	void StartRunning() override;

	void IncreaseRunTime();

public:
	inline double GetRunTime() const { return RunTime; }
};