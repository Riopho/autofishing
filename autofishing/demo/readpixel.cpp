#include <iostream>
#include <windows.h>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
using namespace std;
using namespace cv;

Mat hwnd2mat(HWND hwnd)
{
    HDC hwindowDC,hwindowCompatibleDC;

    int height,width,srcheight,srcwidth;
    HBITMAP hbwindow;
    Mat src;
    BITMAPINFOHEADER  bi;

    hwindowDC=GetDC(hwnd);
    hwindowCompatibleDC=CreateCompatibleDC(hwindowDC);
    SetStretchBltMode(hwindowCompatibleDC,COLORONCOLOR);

    RECT windowsize;    // get the height and width of the screen
    GetClientRect(hwnd, &windowsize);

    srcheight = windowsize.bottom;
    srcwidth = windowsize.right;
    height = windowsize.bottom/1;  //change this to whatever size you want to resize to
    width = windowsize.right/1;

    src.create(height,width,CV_8UC4);

    // create a bitmap
    hbwindow = CreateCompatibleBitmap( hwindowDC, width, height);
    bi.biSize = sizeof(BITMAPINFOHEADER);    //http://msdn.microsoft.com/en-us/library/windows/window/dd183402%28v=vs.85%29.aspx
    bi.biWidth = width;
    bi.biHeight = -height;  //this is the line that makes it draw upside down or not
    bi.biPlanes = 1;
    bi.biBitCount = 32;
    bi.biCompression = BI_RGB;
    bi.biSizeImage = 0;
    bi.biXPelsPerMeter = 0;
    bi.biYPelsPerMeter = 0;
    bi.biClrUsed = 0;
    bi.biClrImportant = 0;

    // use the previously created device context with the bitmap
    SelectObject(hwindowCompatibleDC, hbwindow);
    // copy from the window device context to the bitmap device context
    StretchBlt( hwindowCompatibleDC, 0,0, width, height, hwindowDC, 0, 0,srcwidth,srcheight, SRCCOPY); //change SRCCOPY to NOTSRCCOPY for wacky colors !
    GetDIBits(hwindowCompatibleDC,hbwindow,0,height,src.data,(BITMAPINFO *)&bi,DIB_RGB_COLORS);  //copy from hwindowCompatibleDC to hbwindow

    // avoid memory leak
    DeleteObject (hbwindow);
    DeleteDC(hwindowCompatibleDC);
    ReleaseDC(hwnd, hwindowDC);

    return src;
}

void GetWindow()
{
    HWND hDesktop = ::GetDesktopWindow();
	Mat matSrc= hwnd2mat(hDesktop);
    imwrite("a.png", matSrc);
    //Mat matTmpl = imread("icon.png");
    
    //Mat matRet;
    //matRet.create(matSrc.rows - matTmpl.rows + 1, matSrc.cols - matTmpl.cols + 1, CV_32FC1);
    //matchTemplate(matSrc, matTmpl, matRet,TM_SQDIFF,0); 
    //normalize( matRet, matRet, 0, 1, NORM_MINMAX, -1, Mat() );
	//double minVal; double maxVal; Point minLoc; Point maxLoc;
	//Point matchLoc;
	//minMaxLoc( matRet, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );
	//matchLoc = minLoc;
    


#if 0
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
    RECT rcClient;
    GetClientRect(hDesktop, &rcClient);
    HDC hDesktopDc = ::GetDC(hDesktop);
    HBITMAP hmScreen= ::CreateCompatibleBitmap(hDesktopDc, rcClient.right - rcClient.left, rcClient.top - rcClient.bottom);
	
     
    COLORREF colREf = ::GetPixel(hDesktopDc, 66,77);
    //cout << hex <<colREf << endl;
#endif
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
	GetWindow();
    return 0;
}

