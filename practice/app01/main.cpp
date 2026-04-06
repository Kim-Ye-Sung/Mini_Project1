#include "UserInput.h"
#include <iostream>

using namespace std;

int main()
{
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