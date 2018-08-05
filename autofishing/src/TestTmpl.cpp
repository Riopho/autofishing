#include "TemplateMatch.h"

void MoveCursor(int x, int y)
{
    ::INPUT stMouseIn;
    stMouseIn.type = INPUT_MOUSE;
    stMouseIn.mi.dx = 65535 / 1980 * x;
    stMouseIn.mi.dy = 65535 / 1080* y;
    stMouseIn.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
    stMouseIn.mi.time = 0;
    ::SendInput(1, &stMouseIn, sizeof(stMouseIn));
}

int main()
{
    TemplateMatch* pTmplMatch = TemplateMatch::Instance();
    cv::Mat matQQIcon = cv::imread("./pic/QQ.png", cv::IMREAD_COLOR);
    pTmplMatch->Update();
    cv::Point pointQQ = pTmplMatch->GetMatchPoint(matQQIcon);
    MoveCursor(pointQQ.x + matQQIcon.cols / 2, pointQQ.y + matQQIcon.rows/2);

    return 0;
}

