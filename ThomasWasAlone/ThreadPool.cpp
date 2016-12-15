#include "stdafx.h"
#include "ThreadPool.h"


struct Wrapper
{
	std::pair<Astar*, std::queue<Astar*>> holder;
} ;

int threadFunction(void* data)
{
	ThreadPool* tp = (ThreadPool*)data;
	std::queue<Astar*> *q = tp->getQueue();
	Astar *a = q->front();
	q->pop();
	
	while (true)
	{
		if (q->empty() == true && a->getActive() == a->getGoal())
		{
			SDL_mutex* m = tp->getMutex();
			SDL_LockMutex(m);
			a = q->front();
			q->pop();

			SDL_UnlockMutex(m);
		}
		a->doAstar();
	}

	return 0;
}

ThreadPool::ThreadPool()
{
	for (int i = 0; i < NOOFASTAR; i++) //1)
	{
		astarArray.push_back(Astar(std::pair<int, int>(rand() % BOARDSIZE, rand() % BOARDSIZE), std::pair<int, int>(rand() % BOARDSIZE, rand() % BOARDSIZE)));
	}
	for (int i = 0; i < NOOFASTAR; i++) //2) Separated theese tow loops, so that astarArray was fully initialized
	{
		jobQueue.push(&astarArray[i]);
	}

	for (int i = 0; i < THREADNO; i++)
	{
		//holder = std::pair<Astar*, std::queue<Astar*>*>(jobQueue.front(), &jobQueue);
		//jobQueue.pop();
		threadArray.push_back(SDL_CreateThread(threadFunction, "Astar " + i, (void*)this));
	}
}


ThreadPool::~ThreadPool()
{
}

std::vector<Astar>* ThreadPool::gatAstarArray() { return &astarArray; }

std::queue<Astar*>* ThreadPool::getQueue()
{
	return &jobQueue;
}

SDL_mutex * ThreadPool::getMutex()
{
	return queueLock;
}
