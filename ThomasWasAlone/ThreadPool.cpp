#include "stdafx.h"
#include "ThreadPool.h"
#include <iostream>


struct Wrapper
{
	std::pair<Astar*, std::queue<Astar*>> holder;
} ;

int threadFunction(void* data)
{
	ThreadPool* tp = static_cast<ThreadPool*>(data);
	std::queue<Astar*> *q = tp->getQueue();
	Astar *a = nullptr;
	
	while (true)
	{
		if (a == nullptr ||a->getActive() == a->getGoal())
		{
			SDL_SemWait(tp->getSem());
			std::cout << SDL_SemValue(tp->getSem()) << std::endl;
			a = q->front();
			q->pop();

		}
		a->doAstar();
	}

	return 0;
}

ThreadPool::ThreadPool()
{
	semaphore = SDL_CreateSemaphore(0);
	for (int i = 0; i < NOOFASTAR; i++) //1)
	{
		astarArray.push_back(Astar(std::pair<int, int>(rand() % BOARDSIZE, rand() % BOARDSIZE), std::pair<int, int>(rand() % BOARDSIZE, rand() % BOARDSIZE)));	
	}
	for (int i = 0; i < NOOFASTAR; i++) //2) Separated theese tow loops, so that astarArray was fully initialized
	{
		jobQueue.push(&astarArray[i]);
		SDL_SemPost(semaphore);
		//std::cout << SDL_SemValue(getSem()) << std::endl;
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
	//SDL_DestroyMutex(queueLock);
	SDL_DestroySemaphore(semaphore);
}

std::vector<Astar>* ThreadPool::gatAstarArray() { return &astarArray; }

std::queue<Astar*>* ThreadPool::getQueue() { return &jobQueue; }

//SDL_mutex * ThreadPool::getMutex()
//{
//	return queueLock;
//}
SDL_sem * ThreadPool::getSem(){ return semaphore;}
