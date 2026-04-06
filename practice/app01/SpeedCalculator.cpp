#include "SpeedCalculator.h"
#include <iostream>

using namespace std;

void SpeedCalculator::Invoke()
{
    for (auto& func : listeners)
    {
        //func();
    }
}

string SpeedCalculator::StringText()
{

    return string a;
}

void SpeedCalculator::AddFunction(std::function<void(std::string)> func)
{
	listeners.push_back(func);
}
