#if 0
#include "RioLog.h"
#include "Mouse.h"
#include "TemplateMatch.h"

int main()
{
    TemplateMatch* pTmplMatch = TemplateMatch::Instance();
    cv::Mat matQuestIcon = cv::imread("./pic/quest_icon.png", cv::IMREAD_COLOR);
    cv::Mat matTrigger= cv::imread("./pic/trigger2.png", cv::IMREAD_COLOR);
    cv::Mat matTapToContinue = cv::imread("./pic/tap_to_continue.png", cv::IMREAD_COLOR);
    cv::Mat matUse = cv::imread("./pic/use.png", cv::IMREAD_COLOR);
    cv::Mat matNeedLevelUp = cv::imread("./pic/need_level_up.png", cv::IMREAD_COLOR);

#if 0
    while(1)
    {
        Sleep(300);
        pTmplMatch->Update();
        cv::Point pointQQ = pTmplMatch->GetMatchPoint(matTapToContinue, 1e+08);
        if ((pointQQ.x + pointQQ.y) != 0)
        {
            Mouse::MoveTo(pointQQ.x, pointQQ.y);
            Mouse::Click();
            continue;
        }

        pointQQ = pTmplMatch->GetMatchPoint(matUse, 4e+07);
        if ((pointQQ.x + pointQQ.y) != 0)
        {
            Mouse::MoveTo(pointQQ.x, pointQQ.y);
            Mouse::Click();
            continue;
        }

        pointQQ = pTmplMatch->GetMatchPoint(matTrigger, 1e+08);
        if ((pointQQ.x + pointQQ.y) != 0)
        {
            Mouse::MoveTo(pointQQ.x, pointQQ.y + 100);
            Mouse::Click();
            continue;
        }

        int iQuestOffset = 100;
        pointQQ = pTmplMatch->GetMatchPoint(matNeedLevelUp, 3e+07);
        if ((pointQQ.x + pointQQ.y) != 0)
        {
            iQuestOffset = 200;
        }

        pointQQ = pTmplMatch->GetMatchPoint(matQuestIcon, 1e+08);
        if ((pointQQ.x + pointQQ.y) != 0)
        {
            Mouse::MoveTo(pointQQ.x, pointQQ.y + iQuestOffset);
            Mouse::Click();
        }
    }
#endif
    //pTmplMatch->Update();
    //cv::Point pointQQ = pTmplMatch->GetMatchPoint(matQuestIcon);
    //Mouse::MoveTo(pointQQ.x, pointQQ.y + 100);
    //Mouse::Click();

    LOG_DBG <<"TEST DEBUG LOG";
    LOG_ERROR<<"TEST ERROR LOG";
    LOG_INFO<<"TEST INFO LOG";
    return 0;
}
#endif
