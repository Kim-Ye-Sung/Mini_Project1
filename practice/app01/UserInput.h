#pragma once

#include <memory>
#include <vector>

class UserInput
{
private:
	std::unique_ptr<class HealthUI> HealthUI_Obj;	// 전방선언을 함.
	std::unique_ptr<class TimeCalculator> TimeCalculator_Obj;
	std::unique_ptr<class SpeedCalculator> SpeedCalculator_Obj;
	std::unique_ptr<class DistanceCalculator> DistanceCalculator_Obj;

	std::vector<class Calculator*> Calculators;

public:

	UserInput();
	~UserInput(); // 전방 선언된 타입을 unique_ptr로 관리하므로 cpp에서 소멸자 정의 필요

	void RunningStart();


};