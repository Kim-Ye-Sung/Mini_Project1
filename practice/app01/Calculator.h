#pragma once

#include <vector>
#include <functional>
#include <string>
#include <mutex>   // [추가]

class Calculator
{
private:
	bool IsStart = false;

	std::vector<std::function<void(std::string)>> listeners;

protected:
	mutable std::mutex CalculatorMutex;   // [추가]

	virtual void Invoke();

	virtual std::string ChangeToText() = 0;

	bool GetIsStart() const;   // [수정] inline 제거

public:
	virtual void StartRunning();

	void StopRunning();

	void AddFunction(std::function<void(std::string)> func);
};