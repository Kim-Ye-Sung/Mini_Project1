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
    HideCursor();       // 시작시 커서를 숨기기.

    ShowUI();           // 시작시 최초 UI 띄우기.
}

void HealthUI::StopRunning()
{
    if (!IsStart)
    {
        return;
    }

    IsStart = false;

    RunTimeText = "00:00:00";	
    SpeedText = " 0.0 km/h";	
    DistanceText = "  0.000 km";	
    CalorieText = "   0.0 kcal"; 

    ShowUI();
}

void HealthUI::ShowUI()
{
	MoveCursorToTop();

	cout << "┌──────────┬───────────┬──────────────┬─────────────┐" << endl;
	cout << "│   Time   │   Speed   │   Distance   │   Calorie   │" << endl;
	cout << "│ " << RunTimeText << " │ " << SpeedText << " │  " << DistanceText << "  │ " << CalorieText << " │" << endl;
	cout << "├──────────┴───────────┴──────────────┴─────────────┤" << endl;
	cout << "│                                                   │" << endl;
	cout << "│                                                   │" << endl;
    cout << "└───────────────────────────────────────────────────┘" << endl;
}

void HealthUI::UpdateScreen()
{
    while (true)
    {
        this_thread::sleep_for(chrono::milliseconds(100));  // 0.1초 단위로 업데이트 실행
        
        if (!IsStart)  // 0.1초가 지나기 전에 런닝머신의 작동이 정지되면 화면 업데이트 하지 않음
        {
            return;
        }

        ShowUI();
    }
}


void HealthUI::StartRunning()
{
    if (IsStart)
    {
        return;
    }

    IsStart = true;

    thread t(&HealthUI::UpdateScreen, this);
    t.detach();
}


