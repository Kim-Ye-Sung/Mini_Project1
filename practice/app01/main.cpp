//#include <cstdlib>
//#include <windows.h>
#include "UserInput.h"
#include <iostream>

using namespace std;

//using namespace std;

//void MoveCursorToTop()
//{
//    COORD pos = { 0, 0 };
//    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
//}
//
//void HideCursor()
//{
//    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//    CONSOLE_CURSOR_INFO cursorInfo;
//    GetConsoleCursorInfo(hConsole, &cursorInfo);
//    cursorInfo.bVisible = false;
//    SetConsoleCursorInfo(hConsole, &cursorInfo);
//}

int main()
{
    //HideCursor();

    //HealthUI HealthUI_obj;
    //TimeCalculator TimeCal_Obj;

    //thread t(&TimeCalculator::InCreaseRunTime, &TimeCal_Obj);
    //t.detach();

    //while (true)
    //{
    //    MoveCursorToTop();
    //    HealthUI_obj.ShowUI(TimeCal_Obj.TimeCal());

    //    this_thread::sleep_for(chrono::seconds(1));
    //}

    UserInput UserInput_obj;

    cout << "시작하시겠습니까?";
    int asdsa;
    cin >> asdsa;

    if (asdsa == 1)
    {
        UserInput_obj.RunningStart();
    }

    while (true);

    return 0;
}