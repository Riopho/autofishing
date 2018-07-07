#include <windows.h>
#include <iostream>
using namespace std;

int main()
{
    HWND hDesktop = ::GetDesktopWindow();
    HDC hDesktopDc = ::GetDC(hDesktop);
    COLORREF colREf = ::GetPixel(hDesktopDc, 66,77);
    cout << hex <<colREf << endl;
    return 0;
}

