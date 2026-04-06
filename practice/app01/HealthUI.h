#pragma once

#include<string>

// 콘솔에 나타내는 화면을 담당하는 UI클래스

class HealthUI
{
private:
	std::string RunTimeText = "00:00:00";	// 런닝시간을 나타내는 텍스트 변수

	std::string SpeedText = "00.0 km/h";	// 런닝머신의 현재 속도를 나타내는 텍스트 변수

	void MoveCursorToTop();

	void HideCursor();

	void ShowUI();


public:
	HealthUI();

	void SetRunTimeText(std::string RunTimeText);

	void SetSpeedText(std::string SpeedText);

};