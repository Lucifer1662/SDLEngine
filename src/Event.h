#pragma once
#include "API.h"
#include <vector>

using std::vector;
template<typename ret, typename... types>
class API Event
{
	vector<void*> objs;
	vector<ret(*)(void*, types...)> functions;
public:
	Event() {}
	~Event() {}
	void Add(void* obj, ret(*function)(void*, types...)){
		objs.push_back(obj);
		functions.push_back(function);
	}
	void Remove(ret(*function)(void*, types...)){
		for (size_t i = 0; i < functions.size(); i++)
		{
			if(functions[i] == function){
				functions.swap(i, functions.size() - 1);
				functions.pop_back();
				objs.swap(i, objs.size() - 1);
				objs.pop_back();
			}
		}
	}

	void Call(types... t) {
		for (size_t i = 0; i < functions.size(); i++)
		{
			functions[i](objs[i],t...);
		}
	}
};

