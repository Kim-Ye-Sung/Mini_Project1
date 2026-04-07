#pragma once

#include<string>

// 콘솔에 나타내는 화면을 담당하는 UI클래스

enum UI_State
{
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

	void MoveCursorToTop();

	void HideCursor();

	void ShowMaiuMenuUI();

	void ShowRunningUI();

	void ShowResultUI();

	bool IsStart = false;

	void UpdateScreen();

	UI_State CurrentUI_State = UI_State::MainUI;

public:
	HealthUI();

	inline void SetRunTimeText(std::string RunTimeText) { this->RunTimeText = RunTimeText; }

	inline void SetSpeedText(std::string SpeedText) { this->SpeedText = SpeedText; }

	inline void SetDistanceText(std::string DistanceText) { this->DistanceText = DistanceText; }

	inline void SetCalorieText(std::string CalorieText) { this->CalorieText = CalorieText; }

	void StartRunning();

	void StopRunning();

	void GoToMainmenu();

	inline UI_State GetCurrentU_State() const { return CurrentUI_State; }

};