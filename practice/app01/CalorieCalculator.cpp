#include "CalorieCalculator.h"
#include <thread>
#include <chrono>
#include <sstream>
#include <iomanip>


using namespace std;

std::string CalorieCalculator::ChangeToText()
{	
	stringstream CalorieText;
	CalorieText << fixed
				<< setprecision(1)
				<< setw(6)
				<< setfill(' ')
				<< Calorie << " kcal";

	return CalorieText.str();
}

void CalorieCalculator::StartRunning()
{
	if (GetIsStart())
	{
		return;
	}

	Calculator::StartRunning();

	Calorie = 0.0f;

	thread t(&CalorieCalculator::IncreaseCalorie, this);
	t.detach();
}

void CalorieCalculator::IncreaseCalorie()
{
	while (true)
	{
		this_thread::sleep_for(chrono::milliseconds(GetUpdateCycle()));

		if (!GetIsStart())
		{
			return;
		}

		Calorie += KcalCalculate();
		Invoke();
	}
}

double CalorieCalculator::KcalCalculate()
{
	double o2; // 분당 산소 섭취량 (ml/kg/min)

	// 속도 구간별 ACSM 공식 적용
	if (CurrentSpeed <= 5.0f) {			// 5km/h(걷기) 속도 이하에 사용하는 공식
		o2 = (0.1 * (CurrentSpeed * 1000.0f / 60.0f)) + 3.5f;
	}
	else {		// 달리기 속도에 사용하는 공식
		o2 = (0.2 * (CurrentSpeed * 1000.0f / 60.0f)) + 3.5f;
	}

	// 분당 칼로리 소모량 계산 (kcal/min)
	// 산소 1L당 약 5kcal 소모 원리 적용
	double kcalPerMin = (o2 * 70.0f * 5.0f) / 1000.0f;	// 여기서 70.0f는 성인 평균체중(kg)으로 잡고 계산한것

	// 칼로리 계산 주기에 따른 실시간 소모량 변환
	// (kcalPerMin / 60,000ms) * UpdateCycle(ms)
	double caloriesInInterval = (kcalPerMin / 60000.0f) * (double)GetUpdateCycle();

	return caloriesInInterval;
}
