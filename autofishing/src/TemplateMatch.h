#ifndef _TEMPLATEMATCH
#define _TEMPLATEMATCH
#include <iostream>
#include <windows.h>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#define LOG(logstr) cout<<__FILE__<<":"<<__LINE__<<":"<<logstr<<endl;

class TemplateMatch
{
    public:
        TemplateMatch():_iMatchMethod(0)
        {

        }
        static TemplateMatch* Instance()
        {
            if (nullptr == _instance)
            {
               _instance = new TemplateMatch; 
            } 

            return _instance;
        }

        //刷新屏幕像素,模式匹配之前调用
        void Update();

        //获取屏幕上最匹配当前模式的点
        cv::Point GetMatchPoint(const cv::Mat &matTmpl, double dThreshHold = 0);

    private:
        static TemplateMatch* _instance;

        //匹配模式
        int _iMatchMethod;

        //把窗口转换成mat
        cv::Mat _HwndToMat(HWND hwnd);

        //保存当前窗口的mat
        cv::Mat _matCurWindow;
};


#endif
