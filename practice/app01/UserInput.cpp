#include <iostream>
#include "UserInput.h"
#include "HealthUI.h"
#include "TimeCalculator.h"
#include "SpeedCalculator.h"
#include "DistanceCalculator.h"

using namespace std;

UserInput::UserInput()
{
	HealthUI_Obj = make_unique<HealthUI>();

	TimeCalculator_Obj = make_unique<TimeCalculator>();	
	Calculators.push_back(TimeCalculator_Obj.get());
	SpeedCalculator_Obj = make_unique<SpeedCalculator>();
	Calculators.push_back(SpeedCalculator_Obj.get());
	DistanceCalculator_Obj = make_unique<DistanceCalculator>();
	Calculators.push_back(DistanceCalculator_Obj.get());

	TimeCalculator_Obj->AddFunction(bind(&HealthUI::SetRunTimeText, HealthUI_Obj.get(), placeholders::_1));
	SpeedCalculator_Obj->AddFunction(bind(&HealthUI::SetSpeedText, HealthUI_Obj.get(), placeholders::_1));
	DistanceCalculator_Obj->AddFunction(bind(&HealthUI::SetDistanceText, HealthUI_Obj.get(), placeholders::_1));
	SpeedCalculator_Obj->AddFunction(bind(&DistanceCalculator::SetCurrentSpeed, DistanceCalculator_Obj.get(), placeholders::_1));
}

UserInput::~UserInput() = default;

void UserInput::RunningStart()
{
	for (auto Cal : Calculators)
	{
		Cal->RunningStart(); 
	}

	HealthUI_Obj->RunningStart();
}

