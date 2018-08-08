#include "Mouse.h"

void Mouse::MoveTo(int x, int y)
{
    ::INPUT stMouseIn;
    stMouseIn.type = INPUT_MOUSE;
    stMouseIn.mi.dx = 65535 / 1980 * x;
    stMouseIn.mi.dy = 65535 / 1080 * y;
    stMouseIn.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
    stMouseIn.mi.time = 0;
    ::SendInput(1, &stMouseIn, sizeof(stMouseIn));
}

void Mouse::Click()
{
    ::INPUT stMouseIn;
    stMouseIn.type = INPUT_MOUSE;
    stMouseIn.mi.dwFlags =  MOUSEEVENTF_LEFTDOWN;
    stMouseIn.mi.time = 0;
    ::SendInput(1, &stMouseIn, sizeof(stMouseIn));

    Sleep(100);
    stMouseIn.mi.dwFlags =  MOUSEEVENTF_LEFTUP;
    ::SendInput(1, &stMouseIn, sizeof(stMouseIn));
     
}

void Mouse::DoubleClick()
{
    ::INPUT stMouseIn;
    stMouseIn.type = INPUT_MOUSE;
    stMouseIn.mi.dwFlags =  MOUSEEVENTF_LEFTDOWN;
    stMouseIn.mi.time = 0;
    ::SendInput(1, &stMouseIn, sizeof(stMouseIn));

    Sleep(100);
    stMouseIn.mi.dwFlags =  MOUSEEVENTF_LEFTUP;
    ::SendInput(1, &stMouseIn, sizeof(stMouseIn));
     
    Sleep(100);
    stMouseIn.mi.dwFlags =  MOUSEEVENTF_LEFTDOWN;
    ::SendInput(1, &stMouseIn, sizeof(stMouseIn));

    Sleep(100);
    stMouseIn.mi.dwFlags =  MOUSEEVENTF_LEFTUP;
    ::SendInput(1, &stMouseIn, sizeof(stMouseIn));
}
