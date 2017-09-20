#include "EngineTime.h"

GLdouble EngineTime::deltaTime;
long EngineTime::t1;
long EngineTime::t2;

void EngineTime::Time(){
	t1 = t2;
	t2 = std::clock();
	deltaTime = (t2 - t1) / double(CLOCKS_PER_SEC);
}