#include <iostream>
#include "UserInput.h"
#include "HealthUI.h"
#include "TimeCalculator.h"
#include "SpeedCalculator.h"
#include <thread>

using namespace std;

UserInput::UserInput()
{
	HealthUI_Obj = make_unique<HealthUI>();
	TimeCalculator_Obj = make_unique<TimeCalculator>();
	SpeedCalculator_Obj = make_unique<SpeedCalculator>();

	TimeCalculator_Obj->AddFunction(bind(&HealthUI::SetRunTimeText, HealthUI_Obj.get(), placeholders::_1));

	thread t(&TimeCalculator::IncreaseRunTime, TimeCalculator_Obj.get());
	t.detach();
}

UserInput::~UserInput() = default;

void UserInput::RunningStart()
{
	TimeCalculator_Obj->SetIsStart();
}

