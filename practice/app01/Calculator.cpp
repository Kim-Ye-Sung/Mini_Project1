#include "Calculator.h"

using namespace std;

void Calculator::Invoke()
{
	for (auto& func : listeners)
	{
		func(ChangeToText());
	}
}

string Calculator::ChangeToText()
{
	string a = "kkk";

	return a;
}

void Calculator::RunningStart()
{
	IsStart = true;
}

void Calculator::AddFunction(std::function<void(std::string)> func)
{
	listeners.push_back(func);
}
