#include <windows.h>

class Mouse
{
    public:
        static void MoveTo(int x, int y);

        //默认鼠标左键
        static void Click();
        static void DoubleClick();
};
