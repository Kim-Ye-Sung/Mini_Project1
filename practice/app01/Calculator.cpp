#include "Calculator.h"

using namespace std;

void Calculator::Invoke(double Value)
{
	for (auto& func : listeners)
	{
		func(Value);
	}
}

void Calculator::StartRunning()
{
	IsStart = true;
}


void Calculator::AddFunction(std::function<void(double)> func)
{
	listeners.push_back(func);
}
