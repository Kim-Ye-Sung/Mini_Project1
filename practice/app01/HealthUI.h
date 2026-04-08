#pragma once

#include<string>

// 콘솔에 나타내는 화면을 담당하는 UI클래스

enum UI_State
{
	InputMemberidUI,
	MainUI,
	RunningUI,
	ResultUI,
};

class HealthUI
{
private:
	std::string RunTimeText = "00:00:00";	// 런닝시간을 나타내는 텍스트 변수

	std::string SpeedText = " 0.0 km/h";	// 런닝머신의 현재 속도를 나타내는 텍스트 변수

	std::string DistanceText = "  0.000 km";	// 런닝머신의 달린 거리를 나타내는 텍스트 변수

	std::string CalorieText = "   0.0 kcal"; // 런닝머신으로 달리면서 소비한 칼로리를 나타내는 텍스트 변수

	void MoveCursorPosition(int x, int y);

	void HideCursor();

	void ShowInputMemberidUI();

	void ShowMaiuMenuUI();

	void ShowRunningUI();

	void ShowResultUI(std::string T_Text, std::string S_Text, std::string D_Text, std::string C_Text);

	bool IsStart = false;

	void UpdateScreen();

	std::string FormatSpeedText(double Speed);

	UI_State CurrentUI_State = UI_State::InputMemberidUI;

public:
	HealthUI();

	void SetRunTimeText(double RunTime);

	void SetSpeedText(double Speed);

	void SetDistanceText(double Distance);

	void SetCalorieText(double Calorie);

	void StartRunning();

	void StopRunning(double AverageSpeed);

	void GoToMainmenu();

	inline UI_State GetCurrentU_State() const { return CurrentUI_State; }

};