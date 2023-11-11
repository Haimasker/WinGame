#ifndef GLOBALS_H
#define GLOBALS_H

#include <Windows.h>
#include <unordered_map>
//#include "../Window/Window.h"

class Window;

extern std::vector<Window*> windowList;
extern uint16_t winSize;
extern POINT circle;
extern uint16_t circleRadius;

extern int step;

extern std::unordered_map<std::string, long> windowStyles;

#endif