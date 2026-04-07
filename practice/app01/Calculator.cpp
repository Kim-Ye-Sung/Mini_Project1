#include "Calculator.h"

using namespace std;

void Calculator::Invoke()
{
	for (auto& func : listeners)
	{
		func(ChangeToText());
	}
}

void Calculator::StartRunning()
{
	IsStart = true;
}

void Calculator::StopRunning()
{
	IsStart = false;
}

void Calculator::AddFunction(std::function<void(std::string)> func)
{
	listeners.push_back(func);
}
