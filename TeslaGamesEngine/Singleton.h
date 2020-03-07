#pragma once

#include <memory>
#include <list>

#include "Caltrops.h"

class Singleton
{
public:
	static Singleton* getInst() { return &inst;	}
	//std::list<std::unique_ptr<Caltrops>> getCaltrops() { return caltrops; }
	std::list<Caltrops*> getCaltrops() { return caltrops; }

private:
	Singleton();
	Singleton(Singleton const&);

	static Singleton inst;
	std::list<Caltrops *> caltrops;
};


