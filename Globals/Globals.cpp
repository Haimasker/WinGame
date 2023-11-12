#include "Globals.h"


int16_t winSize = 240;
POINT circle{ 0.5 * winSize, 0.5 * winSize };
int16_t circleRadius = 0.2 * winSize;

int step = 4;

std::unordered_map<std::string, long> windowStyles = {
	{"StaticWindow", WS_POPUP},
	{"MovableWindow", WS_OVERLAPPEDWINDOW }
};

std::vector<Window*> windowList;
