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
}

