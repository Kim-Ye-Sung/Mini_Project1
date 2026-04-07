#include "UserInput.h"
#include <thread>
#include <chrono>

using namespace std;

int main()
{
    UserInput UserInput_obj;

    while (!UserInput_obj.GetWantExit())    // main문이 꺼지지 않게 하는 용도
    {
        this_thread::sleep_for(chrono::milliseconds(100));  // 확실하게 1년 단위로 정지시켜서 while문 부담 줄이기
    }

    return 0;
}