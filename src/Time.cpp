#include "EngineTime.h"

GLdouble Time::deltaTime;
long Time::t1, Time::t2;

void Time::Time(){
	t1 = t2;
	t2 = std::clock();
	deltaTime = (t2 - t1) / double(CLOCKS_PER_SEC);
}