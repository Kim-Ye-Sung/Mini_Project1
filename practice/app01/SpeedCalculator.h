#pragma once

#include "Calculator.h"

class SpeedCalculator : public Calculator
{
private:
	double Speed = 0.0f;	 // 런닝머신의 속도 변수

	std::string ChangeToText() override;

	void RunningStart() override;

	std::vector<std::function<void(double)>> Speedlisteners;

	void Invoke() override;
 
public:
	void Speed_Up();

	void Speed_Down();

	void SetSpeed(double Speed);

	using Calculator::AddFunction;  // 자식클래스에서의 오버로딩 함수로 인해 가려짐현상을 방지하기 위해 선언.
	void AddFunction(std::function<void(double)> func);  // 오버로딩으로 동일한 이름의 함수를 사용함으로서 다르게 델리게이트 바인딩함.
};