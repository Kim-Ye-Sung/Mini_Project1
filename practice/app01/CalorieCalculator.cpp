#include "CalorieCalculator.h"
#include <thread>
#include <chrono>
#include <sstream>
#include <iomanip>

using namespace std;

std::string CalorieCalculator::ChangeToText()
{
	double localCalorie;

	{
		lock_guard<mutex> lock(CalorieMutex);
		localCalorie = Calorie;
	}

	stringstream CalorieText;
	CalorieText << fixed
		<< setprecision(1)
		<< setw(6)
		<< setfill(' ')
		<< localCalorie << " kcal";

	return CalorieText.str();
}

void CalorieCalculator::StartRunning()
{
	if (GetIsStart())
	{
		return;
	}

	Calculator::StartRunning();

	{
		lock_guard<mutex> lock(CalorieMutex);
		Calorie = 0.0f;
	}

	thread t(&CalorieCalculator::IncreaseCalorie, this);
	t.detach();
}

void CalorieCalculator::IncreaseCalorie()
{
	while (true)
	{
		this_thread::sleep_for(chrono::milliseconds(UpdateCycle));

		if (!GetIsStart())
		{
			return;
		}

		double addValue = KcalCalculate();

		{
			lock_guard<mutex> lock(CalorieMutex);
			Calorie += addValue;
		}

		Invoke();
	}
}

double CalorieCalculator::KcalCalculate()
{
	double localSpeed;

	{
		lock_guard<mutex> lock(CalorieMutex);
		localSpeed = CurrentSpeed;
	}

	double o2;

	if (localSpeed <= 5.0f)
	{
		o2 = (0.1 * (localSpeed * 1000.0f / 60.0f)) + 3.5f;
	}
	else
	{
		o2 = (0.2 * (localSpeed * 1000.0f / 60.0f)) + 3.5f;
	}

	double kcalPerMin = (o2 * 70.0f * 5.0f) / 1000.0f;
	double caloriesInInterval = (kcalPerMin / 60000.0f) * (double)UpdateCycle;

	return caloriesInInterval;
}

void CalorieCalculator::SetCurrentSpeed(double Speed)
{
	lock_guard<mutex> lock(CalorieMutex);
	CurrentSpeed = Speed;
}