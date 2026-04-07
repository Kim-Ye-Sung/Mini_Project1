#include "Calculator.h"

using namespace std;

void Calculator::Invoke()
{
	string text;
	vector<function<void(string)>> copiedListeners;   // [추가]

	{
		lock_guard<mutex> lock(CalculatorMutex);   // [추가]
		text = ChangeToText();                     // [수정]
		copiedListeners = listeners;               // [추가]
	}

	for (auto& func : copiedListeners)
	{
		func(text);
	}
}

void Calculator::StartRunning()
{
	lock_guard<mutex> lock(CalculatorMutex);   // [추가]
	IsStart = true;
}

void Calculator::StopRunning()
{
	lock_guard<mutex> lock(CalculatorMutex);   // [추가]
	IsStart = false;
}

void Calculator::AddFunction(std::function<void(std::string)> func)
{
	lock_guard<mutex> lock(CalculatorMutex);   // [추가]
	listeners.push_back(func);
}

bool Calculator::GetIsStart() const
{
	lock_guard<mutex> lock(CalculatorMutex);   // [추가]
	return IsStart;
}