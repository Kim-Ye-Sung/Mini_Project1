#pragma once

#include <vector>
#include <functional>

class SpeedCalculator
{
private:
	float Speed = 4.0f;	 // 런닝머신의 속도 변수. 런닝머신이 시작하면 기본적으로 4km/h 속도로 시작

	std::vector<std::function<void(std::string)>> listeners;

	void Invoke();

	std::string StringText();
	
public:
	inline void Speed_Up() { this->Speed += 0.1f; }

	inline void Speed_Down() { this->Speed -= 0.1f; }

	inline void SetSpeed(float Speed) { this->Speed = Speed; }



	void AddFunction(std::function<void(std::string)> func);
};