#ifndef _TEMPLATEMATCH
#define _TEMPLATEMATCH
#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <windows.h>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "RioLog.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/gapi/imgproc.hpp"
#include "opencv2/imgproc/types_c.h"

class TemplateMatch
{
public:
	TemplateMatch()
	{
		m_pOrb = cv::ORB::create(50000);
		m_pMatcher = cv::FlannBasedMatcher::create();
		LoadPic();
	}
	
	static TemplateMatch* Instance()
	{
		if (nullptr == _instance)
		{
			_instance = new TemplateMatch; 
		} 

		return _instance;
	}
	
	bool Match(std::string FilePath, cv::Point &MatchPoint);
	int MaxFightNum;
	
	//把窗口转换成mat
	cv::Mat _HwndToMat(HWND hwnd);

private:
	static TemplateMatch* _instance;
	void LoadPic();
	void LoadPicImpl(std::string FileName);
	void _Update();
	std::map<std::string, cv::Mat>	m_Descs;
	std::map<std::string, std::vector<cv::KeyPoint> >	m_KeyPoints;
	cv::Ptr<cv::ORB> m_pOrb;
	cv::Ptr<cv::FlannBasedMatcher> m_pMatcher;
	//匹配模式
	int _iMatchMethod;


	//保存当前窗口的mat
	cv::Mat _matCurWindow;
};

extern bool Match(std::string FileName);
extern bool Match(std::string FileName, cv::Point &MatchPoint);
extern bool Click(std::string FileName);
extern void Wait(std::string FileName);
extern void WaitAndClick(std::string FileName);

#endif
