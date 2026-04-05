#include <iostream>
#include "HealthUI.h"

using namespace std;


void HealthUI::ShowUI(string a)
{
    cout << "┌──────────┬────────────┬──────────────┬──────────────┐" << endl;
    cout << "│   Time   │   Speed   │   Distance   │   Calorie   │" << endl;
    cout << "│ " << a << " │            │              │              │" << endl;
    cout << "├────────────┴────────────┴──────────────┴──────────────┤" << endl;
    cout << "│                                                       │" << endl;
    cout << "│                                                       │" << endl;
    cout << "└───────────────────────────────────────────────────────┘" << endl;
}