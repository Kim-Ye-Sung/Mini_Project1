#pragma once

#include <memory>
#include <vector>
#include <mutex>   // [추가]

class UserInput
{
private:
	std::unique_ptr<class HealthUI> HealthUI_Obj;
	std::unique_ptr<class TimeCalculator> TimeCalculator_Obj;
	std::unique_ptr<class SpeedCalculator> SpeedCalculator_Obj;
	std::unique_ptr<class DistanceCalculator> DistanceCalculator_Obj;
	std::unique_ptr<class CalorieCalculator> CalorieCalculator_Obj;

	std::vector<class Calculator*> Calculators;

	std::mutex InputMutex;   // [추가]

	void InputLoop();

	void StartRunning();

	void StopRunning();

public:
	UserInput();
	~UserInput();
};