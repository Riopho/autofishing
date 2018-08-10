#include "RioLog.hpp"
#include "RioTick.hpp"
#include <functional>

void log()
{
    LOG_DBG << "Test tick 1s.";
    return;
}

void log2()
{
    LOG_DBG << "Test tick 2s.";
    return;
}

int main()
{
    RioLog::Instance()->Init();
    RioTick::Instance()->DeclareTick(log,1);
    RioTick::Instance()->DeclareTick(log2,2);
    RioTick::Instance()->Run();

    //TemplateMatch* pTmplMatch = TemplateMatch::Instance();
    //cv::Mat matQQIcon = cv::imread("./pic/QQ.png", cv::IMREAD_COLOR);
    //pTmplMatch->Update();
    //cv::Point pointQQ = pTmplMatch->GetMatchPoint(matQQIcon);
    //MoveCursor(pointQQ.x + matQQIcon.cols / 2, pointQQ.y + matQQIcon.rows/2);

    return 0;
}

