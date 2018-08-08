#include "TemplateMatch.h"

TemplateMatch* TemplateMatch::_instance = NULL;
cv::Mat TemplateMatch::_HwndToMat(HWND hwnd)
{
    HDC hwindowDC,hwindowCompatibleDC;

    int height,width,srcheight,srcwidth;
    HBITMAP hbwindow;
    cv::Mat src;
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

    cv::imwrite("./pic/src.png", src);
    return src;
}

void TemplateMatch::Update()
{
    HWND hDesktop = ::GetDesktopWindow();
    _matCurWindow = _HwndToMat(hDesktop);
    _matCurWindow = cv::imread(".//pic//src.png", cv::IMREAD_COLOR);
}

cv::Point TemplateMatch::GetMatchPoint(const cv::Mat &matTmpl, double dThreshHold)
{
  int result_cols =  _matCurWindow.cols - matTmpl.cols + 1;
  int result_rows = _matCurWindow.rows - matTmpl.rows + 1;
  cv::Mat result;
  result.create(result_rows, result_cols, CV_8UC4);
  matchTemplate( _matCurWindow, matTmpl, result, _iMatchMethod);

  double minVal; double maxVal; cv::Point minLoc; cv::Point maxLoc;
  cv::Point matchLoc;
  minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, cv::Mat());

  if( _iMatchMethod == cv::TM_SQDIFF || _iMatchMethod == cv::TM_SQDIFF_NORMED )
  { 
      if (minVal > dThreshHold)
      {
         return matchLoc; 
      }
      matchLoc = minLoc; 
  }
  else
  { 
      matchLoc = maxLoc;
  }
  
  matchLoc.x += matTmpl.cols / 2;
  matchLoc.y += matTmpl.rows / 2;

  return matchLoc;
}

