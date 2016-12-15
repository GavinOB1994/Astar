#pragma once
#include <vector>
#include <SDL_thread.h>
#include "Constants.h"
#include "Astar.h"

class ThreadPool
{
private:

	std::vector<Astar> astarArray;
	std::vector<SDL_Thread*> threadArray;
	std::queue<Astar*> jobQueue;
	SDL_mutex* queueLock;
	std::pair<Astar*, std::queue<Astar*>*> holder;

public:
	ThreadPool();
	~ThreadPool();

	//int threadFunction(void* data);

	std::vector<Astar>* gatAstarArray();
	std::queue<Astar*>* getQueue();
	SDL_mutex* getMutex();

};

