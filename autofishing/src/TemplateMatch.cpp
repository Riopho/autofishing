#include "TemplateMatch.h"
#include "Mouse.h"
#include "boost/filesystem.hpp"
using namespace boost::filesystem;

using namespace std;

bool Click(string FilePath)
 {
	 cv::Point Point;
	 LOG_ERR << "Click: " << FilePath ;
	 if (Match(FilePath, Point)) 
	 {
		 Mouse::MoveTo(Point.x, Point.y);
		 Mouse::Click();
		 return true;
	 }

	 return false;
 }

bool Match(string FileName)
{
	cv::Point MatchPoint;
	return TemplateMatch::Instance()->Match(FileName, MatchPoint);
}

bool Match(string FileName, cv::Point &MatchPoint)
{
	return TemplateMatch::Instance()->Match(FileName, MatchPoint);
}

void Wait(string FileName)
{
	do
	{
		LOG_ERR << "waiting: " << FileName;
		Sleep(1000);
	} while (!Match(FileName));
	LOG_ERR << FileName << " arrived.";
	return;
}

void WaitAndClick(string FileName)
{
	do
	{
		LOG_ERR << "waiting: " << FileName;
		Sleep(1000);
	} while (!Match(FileName));
	Click(FileName);
	LOG_ERR << FileName << " Clicked.";
	return;
}

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

	if (!src.empty())
	{
		cv::imwrite("./pic/src.png", src);
	}

    return src;
}

void TemplateMatch::_Update()
{
    HWND hDesktop = ::GetDesktopWindow();
    _matCurWindow = _HwndToMat(hDesktop);
    _matCurWindow = cv::imread("./pic/src.png", cv::IMREAD_GRAYSCALE);
	
	LoadPicImpl("./pic/src.png");
}

bool TemplateMatch::Match(std::string FilePath, cv::Point &MatchPoint)
{
	_Update();
	vector<vector<cv::DMatch> > Matches;
	vector<cv::DMatch> GoodMatches;
	m_pMatcher->knnMatch(m_Descs[FilePath], m_Descs["./pic/src.png"], Matches, 2);

	cv::Point sum;
    for (int i = 0; i < Matches.size(); i++)
    {
        if (Matches[i][0].distance < 0.6 * Matches[i][1].distance)
        {
            GoodMatches.push_back(Matches[i][0]);
			sum.x +=  m_KeyPoints["./pic/src.png"][Matches[i][0].trainIdx].pt.x;
			sum.y +=  m_KeyPoints["./pic/src.png"][Matches[i][0].trainIdx].pt.y;
		} 
	}

	LOG_ERR << FilePath << ": [ " << GoodMatches.size() << " / " << m_KeyPoints[FilePath].size() << " ] .";
	if (GoodMatches.size() < 5) 
	{
		LOG_ERR << FilePath << ": no good match .";
		return false;
	}
	
	cv::Point avg;
	avg.x = sum.x / GoodMatches.size();
	avg.y = sum.y / GoodMatches.size();

	MatchPoint = avg;
	
	LOG_ERR << FilePath << ", good match, location :" << avg;
	
	return true;
}

void TemplateMatch::LoadPicImpl(std::string FileName)
{
	cv::Mat mat = cv::imread(FileName, cv::IMREAD_GRAYSCALE);
	std::vector<cv::KeyPoint> KeyPoints;
	m_pOrb->detect(mat, KeyPoints);
	if (KeyPoints.size() == 0 || mat.empty()) 
	{
		LOG_ERR << FileName << ": has no feature point!";
		return;
	}

	LOG_ERR << FileName  << ": loaded , features : " << KeyPoints.size();
	cv::Mat Desc;
	m_pOrb->compute(mat, KeyPoints, Desc);
	if (Desc.type() != CV_32F) 
	{
		Desc.convertTo(Desc, CV_32F);
	}

	if (m_Descs.find(FileName) != m_Descs.end()) 
	{
		m_Descs.erase(FileName);
		m_KeyPoints.erase(FileName);
	}
	
	m_Descs.insert(std::pair<string, cv::Mat>(FileName, Desc));
	m_KeyPoints.insert(std::pair<string, vector<cv::KeyPoint> >(FileName, KeyPoints));
}

void TemplateMatch::LoadPic()
{
	path pic("./pic/");
	directory_iterator end;
	for (directory_iterator iter(pic); iter != end; ++iter)
	{
		string path = iter->path().string();
		if (path.find("png") != std::string::npos) 
		{
			std::size_t pos = path.find("\\");
			std::string FileName = path.substr(pos + 1);
			LoadPicImpl("./pic/" + FileName);
		}
	}
	return;
}

