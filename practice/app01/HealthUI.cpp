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

void HealthUI::ShowUI()
{
	MoveCursorToTop();

	cout << "┌──────────┬───────────┬──────────────┬─────────────┐" << endl;
	cout << "│   Time   │   Speed   │   Distance   │   Calorie   │" << endl;
	cout << "│ " << RunTimeText << " │ " << SpeedText << " │   " << DistanceText << "  │             │" << endl;
	cout << "├──────────┴───────────┴──────────────┴─────────────┤" << endl;
	cout << "│                                                   │" << endl;
	cout << "│                                                   │" << endl;
    cout << "└───────────────────────────────────────────────────┘" << endl;
}

void HealthUI::UpdateScreen()
{
    while (IsStart)
    {
        this_thread::sleep_for(chrono::milliseconds(100));
        ShowUI();
    }
}

void HealthUI::SetRunTimeText(string RunTimeText)
{
    this->RunTimeText = RunTimeText;
}

void HealthUI::SetSpeedText(std::string SpeedText)
{
    this->SpeedText = SpeedText;
}

void HealthUI::SetDistanceText(std::string DistanceText)
{
    this->DistanceText = DistanceText;
}

void HealthUI::RunningStart()
{
    if (IsStart)
    {
        return;
    }

    IsStart = true;

    thread t(&HealthUI::UpdateScreen, this);
    t.detach();
}


