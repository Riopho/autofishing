MyDemo:Mouse.h Mouse.cpp TemplateMatch.h TemplateMatch.cpp TestTmpl.cpp RioLog.h
	g++ -g RioLog.h Mouse.h Mouse.cpp TemplateMatch.h TemplateMatch.cpp TestTmpl.cpp -lgdi32 `pkg-config --cflags --libs opencv` -lboost_log -lboost_log_setup -std=c++11 -o MyDemo
clean:
	rm -rf TestTmpl
