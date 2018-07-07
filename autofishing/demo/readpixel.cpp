#include <windows.h>
#include <iostream>
using namespace std;

void GetWindow()
{
    HWND hDesktop = ::GetDesktopWindow();
    HWND hWinIter = ::GetWindow(hDesktop,GW_CHILD);
    char sBuff[256] = {0};
    while(hWinIter != NULL)
    {
       memset(sBuff, 0, 256);
       ::GetWindowText(hWinIter, sBuff, 256);
       if (0 == strncmp(sBuff,"QQ",2))
       {
           cout << sBuff << endl;
           ::SwitchToThisWindow(hWinIter, false);
           break;
       }
       
       //cout << sBuff <<endl; 
       //找到特定窗口
       hWinIter = ::GetNextWindow(hWinIter, GW_HWNDNEXT);
    }
    HDC hDesktopDc = ::GetDC(hDesktop);
    COLORREF colREf = ::GetPixel(hDesktopDc, 66,77);
    //cout << hex <<colREf << endl;
}

void MoveCursor()
{
    ::INPUT stMouseIn;
    stMouseIn.type = INPUT_MOUSE;
    stMouseIn.mi.dx = 32767;
    stMouseIn.mi.dy = 32767;
    stMouseIn.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
    stMouseIn.mi.time = 0;
    ::SendInput(1, &stMouseIn, sizeof(stMouseIn));
}

int main()
{
    Sleep(1000);
    MoveCursor();
    return 0;
}

