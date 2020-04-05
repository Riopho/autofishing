#include "RioLog.hpp"
#include "RioTick.hpp"
#include <functional>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <windows.h>
#include <vector>
#include "TemplateMatch.h"
#include "Mouse.h"
#include "State.h"
#include <numeric>
#include <cstdlib>
#include <sstream>
#include <tchar.h>

void GetWindow()
{
    HWND hDesktop = ::GetDesktopWindow();
	int i = 0;
	while (1)
	{
		Sleep(2000);
		HWND hWnd = ::FindWindow(0,_T("À×µçÄ£ÄâÆ÷"));
		cv::Mat tmp = TemplateMatch::Instance()->_HwndToMat(hWnd);
		std::stringstream ss;
		ss << "./pic2/" <<i << ".png";
		if (!tmp.empty()) 
		{
			cv::imwrite(ss.str(), tmp);
		}
	}
	
}

#if 0
int main()
{
	GetWindow();
	return 0;
}

#endif
int main(int argc, char *argv[])
{

	if (argc == 2) 
	{
		TemplateMatch::Instance()->MaxFightNum = atoi(argv[1]);		
	}
	else
	{
		TemplateMatch::Instance()->MaxFightNum = 10;		
	}
	LOG_ERR << "Max Num: " << TemplateMatch::Instance()->MaxFightNum;
    State state;
    state.start();

	return 0;
}


