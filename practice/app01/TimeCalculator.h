#pragma once

#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

class TimeCalculator
{
private :
	int RunTime = 0;

public:
	void InCreaseRunTime();

	string TimeCal();
};