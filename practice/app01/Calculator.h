#pragma once

#include <vector>
#include <functional>
#include <string>

class Calculator
{
private:
	bool IsStart = false;		// 런닝머신의 작동을 시작을 나타내는 변수. true = 작동, false = 정지. 처음은 정지상태로 시작

	std::vector<std::function<void(std::string)>> listeners;

protected:
	virtual void Invoke();

	virtual std::string ChangeToText() = 0;

	inline bool GetIsStart()  const { return IsStart; }

public:
	virtual void StartRunning();

	void StopRunning();

	void AddFunction(std::function<void(std::string)> func);
};