#include "SpeedCalculator.h"
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

string SpeedCalculator::ChangeToText()
{
	double localSpeed;   // [추가]

	{
		lock_guard<mutex> lock(SpeedMutex);   // [추가]
		localSpeed = Speed;
	}

	stringstream SpeedText;
	SpeedText << fixed
		<< setprecision(1)
		<< setw(4)
		<< setfill(' ')
		<< localSpeed << " km/h";

	return SpeedText.str();
}

void SpeedCalculator::StartRunning()
{
	if (GetIsStart())
	{
		return;
	}

	Calculator::StartRunning();

	{
		lock_guard<mutex> lock(SpeedMutex);   // [추가]
		Speed = 4.0f;
	}

	Invoke();
}

void SpeedCalculator::Invoke()
{
	double localSpeed;   // [추가]
	vector<function<void(double)>> copiedListeners;   // [추가]

	Calculator::Invoke();

	{
		lock_guard<mutex> lock(SpeedMutex);   // [추가]
		localSpeed = Speed;
		copiedListeners = Speedlisteners;
	}

	for (auto& func : copiedListeners)
	{
		func(localSpeed);
	}
}

void SpeedCalculator::Speed_Up()
{
	if (!GetIsStart())
	{
		return;
	}

	{
		lock_guard<mutex> lock(SpeedMutex);   // [추가]
		Speed += 0.1f;
	}

	Invoke();
}

void SpeedCalculator::Speed_Down()
{
	if (!GetIsStart())
	{
		return;
	}

	{
		lock_guard<mutex> lock(SpeedMutex);   // [추가]
		Speed -= 0.1f;
	}

	Invoke();
}

void SpeedCalculator::SetSpeed(double Speed)
{
	if (!GetIsStart())
	{
		return;
	}

	{
		lock_guard<mutex> lock(SpeedMutex);   // [추가]
		this->Speed = Speed;
	}

	Invoke();
}

void SpeedCalculator::AddFunction(std::function<void(double)> func)
{
	lock_guard<mutex> lock(SpeedMutex);   // [추가]
	Speedlisteners.push_back(func);
}