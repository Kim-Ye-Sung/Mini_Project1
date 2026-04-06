#pragma once

#include <vector>
#include <functional>
#include <string>


class TimeCalculator
{
private :
	bool IsStart = false;

	int RunTime = 0;

	std::vector<std::function<void(std::string)>> listeners;

	std::string TimeCal();

	void Invoke();
public:
	void IncreaseRunTime();

	inline void const SetIsStart() { IsStart = !IsStart; }

	void AddFunction(std::function<void(std::string)> func);
};