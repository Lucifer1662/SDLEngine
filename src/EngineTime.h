#pragma once
#include "API.h"
#include "GL\glew.h"
#include <ctime>

namespace Time {
	API extern GLdouble deltaTime;
	API extern long t1, t2;
	void Time();

}