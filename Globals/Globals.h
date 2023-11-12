#ifndef GLOBALS_H
#define GLOBALS_H

#include <Windows.h>
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>


class Window;

extern std::vector<Window*> windowList;
extern int16_t winSize;
extern POINT circle;
extern int16_t circleRadius;

extern int step;

extern std::unordered_map<std::string, long> windowStyles;


#endif // GLOBALS_H
