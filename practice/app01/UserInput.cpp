#include <iostream>
#include "UserInput.h"
#include "HealthUI.h"
#include "TimeCalculator.h"
#include "SpeedCalculator.h"
#include "DistanceCalculator.h"
#include "CalorieCalculator.h"
#include <conio.h>
#include <thread>

using namespace std;

void UserInput::InputLoop()
{
	while (true)
	{
		int key = _getch();

		//cout << "Now Key : " << key << endl;
		
		switch (key)
		{
		case 32:	// 스페이스바를 눌렀을때
			switch (HealthUI_Obj->GetCurrentU_State())
			{
			case UI_State::MainUI:	// 현재 화면이 메인메뉴라면 런닝머신 가동
				StartRunning();
				break;
			case UI_State::RunningUI:	// 현재 화면이 런닝머신 작동중이라면 런닝머신 종료
				StopRunning();
				break;
			case UI_State::ResultUI:	// 현재 화면이 결과창이라면 데이터베이스에 저장하고 메인메뉴로 돌아가기
				HealthUI_Obj->GoToMainmenu();
				break;
			}
			break;
		case 27:	// Esc를 눌렀을때
			switch (HealthUI_Obj->GetCurrentU_State())
			{
			case UI_State::MainUI:	// 현재 화면이 메인메뉴라면 프로그램 종료
				return;
				break;
			case UI_State::ResultUI:	// 현재 화면이 결과창이라면 메인메뉴로 바로 이동
				HealthUI_Obj->GoToMainmenu();
				break;
			}
			break;
		case 72 :	// 윗방향키를 눌렀을때
			SpeedCalculator_Obj->Speed_Up();
			break;
		case 80:	// 아랫방향키를 눌렀을때
			SpeedCalculator_Obj->Speed_Down();
			break;

		}
	}
}

UserInput::UserInput()
{
	HealthUI_Obj = make_unique<HealthUI>();

	TimeCalculator_Obj = make_unique<TimeCalculator>();	
	Calculators.push_back(TimeCalculator_Obj.get());
	SpeedCalculator_Obj = make_unique<SpeedCalculator>(); 
	Calculators.push_back(SpeedCalculator_Obj.get());
	DistanceCalculator_Obj = make_unique<DistanceCalculator>();
	Calculators.push_back(DistanceCalculator_Obj.get());
	CalorieCalculator_Obj = make_unique<CalorieCalculator>();
	Calculators.push_back(CalorieCalculator_Obj.get());

	TimeCalculator_Obj->AddFunction(bind(&HealthUI::SetRunTimeText, HealthUI_Obj.get(), placeholders::_1));
	SpeedCalculator_Obj->AddFunction(bind(&HealthUI::SetSpeedText, HealthUI_Obj.get(), placeholders::_1));
	DistanceCalculator_Obj->AddFunction(bind(&HealthUI::SetDistanceText, HealthUI_Obj.get(), placeholders::_1));
	CalorieCalculator_Obj->AddFunction(bind(&HealthUI::SetCalorieText, HealthUI_Obj.get(), placeholders::_1));
	SpeedCalculator_Obj->AddFunction(bind(&DistanceCalculator::SetCurrentSpeed, DistanceCalculator_Obj.get(), placeholders::_1));
	SpeedCalculator_Obj->AddFunction(bind(&CalorieCalculator::SetCurrentSpeed, CalorieCalculator_Obj.get(), placeholders::_1));
}

UserInput::~UserInput() = default;

void UserInput::StartRunning()	// 런닝머신 작동을 시작하는 함수
{
	for (auto Cal : Calculators)	// 시간, 속도, 거리, 칼로리 계산기들의 계산을 시작
	{
		Cal->StartRunning();
	}

	HealthUI_Obj->StartRunning();	// 스크린 갱신 시작
}

void UserInput::StopRunning()
{
	for (auto Cal : Calculators)
	{
		Cal->StopRunning();
	}

	HealthUI_Obj->StopRunning(SpeedCalculator_Obj->ChangeToText(DistanceCalculator_Obj->GetDistance(), TimeCalculator_Obj->GetRunTime()));
}

