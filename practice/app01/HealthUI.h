#pragma once

#include <string>
#include <mutex>   // [추가]

class HealthUI
{
private:
	std::string RunTimeText = "00:00:00";
	std::string SpeedText = " 0.0 km/h";
	std::string DistanceText = "  0.000 km";
	std::string CalorieText = "   0.0 kcal";

	bool IsStart = false;

	std::mutex UIMutex;   // [추가]

	void MoveCursorToTop();

	void HideCursor();

	void ShowUI();

	void UpdateScreen();

public:
	HealthUI();

	void SetRunTimeText(std::string RunTimeText);

	void SetSpeedText(std::string SpeedText);

	void SetDistanceText(std::string DistanceText);

	void SetCalorieText(std::string CalorieText);

	void StartRunning();

	void StopRunning();
};