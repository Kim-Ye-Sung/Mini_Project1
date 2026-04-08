#pragma once

#include <vector>
#include <functional>
#include <string>

class Calculator
{
private:
	bool IsStart = false;		// 런닝머신의 작동을 시작을 나타내는 변수. true = 작동, false = 정지. 처음은 정지상태로 시작

	std::vector<std::function<void(double)>> listeners;

	const int UpdateCycle = 200;	// 시간, 거리, 칼로리 등등 계산할것들의 계산 주기.    200 = 0.2초


protected:
	void Invoke(double Value);

	inline bool GetIsStart()  const { return IsStart; }

	inline int GetUpdateCycle() { return UpdateCycle; }
 
public:
	virtual void StartRunning();

	inline void StopRunning() { IsStart = false; }

	void AddFunction(std::function<void(double)> func);
};