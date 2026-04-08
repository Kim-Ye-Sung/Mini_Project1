#include <iostream>
#include "HealthUI.h"
#include <windows.h>
#include <thread>
#include <chrono>
#include <sstream>
#include <iomanip>

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

    ShowMaiuMenuUI();   // 시작시 최초 UI 띄우기.
}

void HealthUI::SetRunTimeText(double RunTime)
{
	int hour = (int)RunTime / 3600;          // 시간
	int min = ((int)RunTime % 3600) / 60;    // 분
	int sec = (int)RunTime % 60;             // 초

	stringstream TimeText;
	TimeText << setw(2) << setfill('0') << hour << ":"  // 시간,분,초 단위를 두자리씩 표기하며, 빈자리는 0으로 채워서 나타내기
		     << setw(2) << setfill('0') << min << ":"
		     << setw(2) << setfill('0') << sec;

	RunTimeText = TimeText.str();
}

void HealthUI::SetSpeedText(double Speed)
{
    this->SpeedText = FormatSpeedText(Speed);
}

void HealthUI::SetDistanceText(double Distance)
{
	stringstream DistanceText;

	DistanceText << fixed           // 고정 소수점
		         << setprecision(3) // 소수점 2자리
		         << setw(7)         // 전체 폭 (000.00  == .을 포함한6자리)
		         << setfill(' ')    // 빈 자리 0으로 채움
		         << Distance << " km";

	this->DistanceText = DistanceText.str();
}

void HealthUI::SetCalorieText(double Calorie)
{
	stringstream CalorieText;
	CalorieText << fixed
		        << setprecision(1)
		        << setw(6)
		        << setfill(' ')
		        << Calorie << " kcal";

    this->CalorieText = CalorieText.str();
}

std::string HealthUI::FormatSpeedText(double Speed)
{
    stringstream SpeedText;
    SpeedText << fixed		// 고정 소수점
                     << setprecision(1)   // 소수점 1자리까지 표기
                     << setw(4)   // . 까지 포함하여 4자리 나타내기
                     << setfill(' ')  // 비어있는 곳은 0으로 표기
                     << Speed << " km/h";

    return SpeedText.str();
}

void HealthUI::StopRunning(double AverageSpeed)
{
    if (!IsStart)
    {
        return;
    }

    IsStart = false;

    string TimeResultText = RunTimeText;
    string AverageSpeedText = FormatSpeedText(AverageSpeed);
    string DistanceResltText = DistanceText;
    string CalorieResultText = CalorieText;

    RunTimeText = "00:00:00";	
    SpeedText = " 0.0 km/h";	
    DistanceText = "  0.000 km";	
    CalorieText = "   0.0 kcal"; 

    CurrentUI_State = UI_State::ResultUI;

    ShowResultUI(TimeResultText, AverageSpeedText, DistanceResltText, CalorieResultText);
}

void HealthUI::GoToMainmenu()
{
    CurrentUI_State = UI_State::MainUI;

    ShowMaiuMenuUI();
}

void HealthUI::ShowRunningUI()
{
	MoveCursorToTop();

	cout << "┌──────────┬───────────┬──────────────┬─────────────┐" << endl;
	cout << "│   Time   │   Speed   │   Distance   │   Calorie   │" << endl;
	cout << "│ " << RunTimeText << " │ " << SpeedText << " │  " << DistanceText << "  │ " << CalorieText << " │" << endl;
	cout << "├──────────┴───────────┴──────────────┴─────────────┤" << endl;
    cout << "│                                                   │" << endl;
    cout << "│                    Stop     : Space               │" << endl;
    cout << "│                                                   │" << endl;
    cout << "│                                                   │" << endl;
    cout << "│                  Speed Up   : ↑                   │" << endl;
    cout << "│                                                   │" << endl;
    cout << "│                                                   │" << endl;
    cout << "│                  Speed Down : ↓                   │" << endl;
    cout << "│                                                   │" << endl;
    cout << "│                                                   │" << endl;
    cout << "│                                                   │" << endl;
    cout << "└───────────────────────────────────────────────────┘" << endl;
}

void HealthUI::ShowMaiuMenuUI()
{
    MoveCursorToTop();

    cout << "┌──────────┬───────────┬──────────────┬─────────────┐" << endl;
    cout << "│   Time   │   Speed   │   Distance   │   Calorie   │" << endl;
    cout << "│ " << RunTimeText << " │ " << SpeedText << " │  " << DistanceText << "  │ " << CalorieText << " │" << endl;
    cout << "├──────────┴───────────┴──────────────┴─────────────┤" << endl;
    cout << "│                                                   │" << endl;
    cout << "│                                                   │" << endl;
    cout << "│                                                   │" << endl;
    cout << "│                  Start : Space                    │" << endl;
    cout << "│                                                   │" << endl;
    cout << "│                                                   │" << endl;
    cout << "│                                                   │" << endl;
    cout << "│                   Exit :  ESC                     │" << endl;
    cout << "│                                                   │" << endl;
    cout << "│                                                   │" << endl;
    cout << "│                                                   │" << endl;
    cout << "└───────────────────────────────────────────────────┘" << endl;
}

void HealthUI::ShowResultUI(std::string T_Text, std::string S_Text, std::string D_Text, std::string C_Text)
{
    MoveCursorToTop();

    cout << "┌──────────┬───────────┬──────────────┬─────────────┐" << endl;
    cout << "│   Time   │   Speed   │   Distance   │   Calorie   │" << endl;
    cout << "│ " << RunTimeText << " │ " << SpeedText << " │  " << DistanceText << "  │ " << CalorieText << " │" << endl;
    cout << "├──────────┴───────────┴──────────────┴─────────────┤" << endl;
    cout << "│                      Result                       │" << endl;
    cout << "│                                                   │" << endl;
    cout << "│              Time      :   " << T_Text << "               │" << endl;
    cout << "│          Average Speed :       "  << S_Text << "          │" << endl;
    cout << "│            Distance    :    "   << D_Text << "            │" << endl;
    cout << "│            Calorie     :     "  << C_Text << "          │" << endl;
    cout << "│                                                   │" << endl;
    cout << "│               Do you want to save?                │" << endl;
    cout << "│                                                   │" << endl;
    cout << "│           Yes : Space       No : Esc              │" << endl;
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

        ShowRunningUI();
    }
}


void HealthUI::StartRunning()
{
    if (IsStart)
    {
        return;
    }

    IsStart = true;

    ShowRunningUI();

    CurrentUI_State = UI_State::RunningUI;

    thread t(&HealthUI::UpdateScreen, this);
    t.detach();
}


