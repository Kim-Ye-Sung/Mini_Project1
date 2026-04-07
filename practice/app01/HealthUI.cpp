#include <iostream>
#include "HealthUI.h"
#include <windows.h>
#include <thread>
#include <chrono>

using namespace std;

void HealthUI::MoveCursorToTop()
{
	COORD pos = { 0, 0 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void HealthUI::HideCursor()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hConsole, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(hConsole, &cursorInfo);
}

HealthUI::HealthUI()
{
	HideCursor();
	ShowUI();
}

void HealthUI::SetRunTimeText(std::string RunTimeText)
{
	lock_guard<mutex> lock(UIMutex);   // [추가]
	this->RunTimeText = RunTimeText;
}

void HealthUI::SetSpeedText(std::string SpeedText)
{
	lock_guard<mutex> lock(UIMutex);   // [추가]
	this->SpeedText = SpeedText;
}

void HealthUI::SetDistanceText(std::string DistanceText)
{
	lock_guard<mutex> lock(UIMutex);   // [추가]
	this->DistanceText = DistanceText;
}

void HealthUI::SetCalorieText(std::string CalorieText)
{
	lock_guard<mutex> lock(UIMutex);   // [추가]
	this->CalorieText = CalorieText;
}

void HealthUI::StopRunning()
{
	{
		lock_guard<mutex> lock(UIMutex);   // [추가]

		if (!IsStart)
		{
			return;
		}

		IsStart = false;

		RunTimeText = "00:00:00";
		SpeedText = " 0.0 km/h";
		DistanceText = "  0.000 km";
		CalorieText = "   0.0 kcal";
	}

	ShowUI();   // [수정] 락 해제 후 호출
}

void HealthUI::ShowUI()
{
	string runTimeText;
	string speedText;
	string distanceText;
	string calorieText;

	{
		lock_guard<mutex> lock(UIMutex);   // [추가]
		runTimeText = RunTimeText;
		speedText = SpeedText;
		distanceText = DistanceText;
		calorieText = CalorieText;
	}

	MoveCursorToTop();

	cout << "┌──────────┬───────────┬──────────────┬─────────────┐" << endl;
	cout << "│   Time   │   Speed   │   Distance   │   Calorie   │" << endl;
	cout << "│ " << runTimeText << " │ " << speedText << " │  " << distanceText << "  │ " << calorieText << " │" << endl;
	cout << "├──────────┴───────────┴──────────────┴─────────────┤" << endl;
	cout << "│                                                   │" << endl;
	cout << "│                                                   │" << endl;
	cout << "└───────────────────────────────────────────────────┘" << endl;
}

void HealthUI::UpdateScreen()
{
	while (true)
	{
		this_thread::sleep_for(chrono::milliseconds(100));

		{
			lock_guard<mutex> lock(UIMutex);   // [추가]
			if (!IsStart)
			{
				return;
			}
		}

		ShowUI();
	}
}

void HealthUI::StartRunning()
{
	{
		lock_guard<mutex> lock(UIMutex);   // [추가]

		if (IsStart)
		{
			return;
		}

		IsStart = true;
	}

	thread t(&HealthUI::UpdateScreen, this);
	t.detach();
}