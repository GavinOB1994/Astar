#pragma once

#include <vector>
#include <SDL_thread.h>
#include "Renderer.h"
#include "Astar.h"
#include "InputManager.h"
#include "EventListener.h"
#include "Constants.h"
#include "ThreadPool.h"

/** The game objct whic manages the game loop*/
class Game:public EventListener
{
	InputManager inputManager;
	Renderer renderer;

	unsigned int lastTime;//time of last update;

	bool pause;
	bool quit;
	int boardSize = 100;

	//colours
	Colour orange = { 255, 140, 0 };
	Colour yellow = { 255, 255, 0 };
	Colour black = { 0, 0, 0 };
	Colour green = { 0, 255, 0 };
	Colour red = { 255, 0, 0 };
	Colour blue = { 0, 0, 255 };

	//std::vector<Rect> board;
	std::vector<std::vector<Rect>> board;

	ThreadPool tPool;

	//std::vector<std::pair<int, int>> walls;

	//std::vector<Astar> astarArray;

	//std::vector<SDL_Thread*> threadArray;

	//std::queue<Astar*> jobQueue;

	//SDL_Thread* queueLock;

	//Astar astar;
	//Astar astar2;
	//Astar astar3;
	//Astar astar4;
	//Astar astar5;

	

public:
	Game();
	~Game();

	bool init();
	void destroy();
	//int threadFunction(void*);
	void update();
	void render();
	void loop();

	void onEvent(EventListener::Event);
};

