#include "DistanceCalculator.h"
#include <sstream>
#include <iomanip>
#include <thread>
#include <chrono>

using namespace std;

string DistanceCalculator::ChangeToText()
{
	double localDistance;   // [추가]

	{
		lock_guard<mutex> lock(DistanceMutex);   // [추가]
		localDistance = Distance;
	}

	std::stringstream DistanceText;

	DistanceText << fixed
		<< setprecision(3)
		<< setw(7)
		<< setfill(' ')
		<< localDistance << " km";

	return DistanceText.str();
}

void DistanceCalculator::StartRunning()
{
	if (GetIsStart())
	{
		return;
	}

	Calculator::StartRunning();

	{
		lock_guard<mutex> lock(DistanceMutex);   // [추가]
		Distance = 0.0f;
	}

	thread t(&DistanceCalculator::IncreaseDistance, this);
	t.detach();
}

void DistanceCalculator::IncreaseDistance()
{
	while (true)
	{
		this_thread::sleep_for(chrono::milliseconds(UpdateCycle));

		if (!GetIsStart())
		{
			return;
		}

		{
			lock_guard<mutex> lock(DistanceMutex);   // [추가]
			Distance += CurrentSpeed * (((double)UpdateCycle / 1000) / 3600);
		}

		Invoke();
	}
}

void DistanceCalculator::SetCurrentSpeed(double Speed)
{
	lock_guard<mutex> lock(DistanceMutex);   // [추가]
	CurrentSpeed = Speed;
}