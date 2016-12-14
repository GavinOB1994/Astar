#include "stdafx.h"

#include <iostream>
using namespace std;
#include "Game.h"



const int SCREEN_FPS = 100;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;



int threadFunction(void* data)
{
	Astar *a = (Astar*)data;

	while (a->getActive() != a->getGoal())
	{
		a->doAstar();
	}

	return 0;
}



Game::Game()
{
	pause = false;
	quit = false;
}


Game::~Game()
{
}


bool Game::init() {	
	Size2D winSize(1000,1000);

	//creates our renderer, which looks after drawing and the window
	renderer.init(winSize,"Simple SDL App");

	//set up the viewport
	//we want the vp centred on origin and 20 units wide
	float aspectRatio = winSize.w / winSize.h;
	float vpWidth = 20;
	Size2D vpSize(vpWidth, vpWidth /aspectRatio);
	Point2D vpBottomLeft( -vpSize.w / 2, - vpSize.h / 2); 

	astar = Astar(std::pair<int, int>(2, 2) , std::pair<int, int>(BOARDSIZE - 1, BOARDSIZE - 1)); //Create my instance of Astar

	astar2 = Astar(std::pair<int, int>(10, 10), std::pair<int, int>(BOARDSIZE - 10, BOARDSIZE - 10)); //Create my instance of Astar

	float tWidth = winSize.w / BOARDSIZE;
	float tHeight = winSize.h / BOARDSIZE;

	for (int i = 0; i < BOARDSIZE; i++)
	{
		std::vector<Rect> rectLine;

		for (int j = 0; j < BOARDSIZE; j++)
			rectLine.push_back( Rect(tWidth * i, tHeight * j, tWidth, tHeight));

		board.push_back(rectLine);
	}

	Rect vpRect(vpBottomLeft,vpSize);
	renderer.setViewPort(vpRect);


	//astar.doAstar();

	//Run the thread
	int data = NULL;
	SDL_Thread* thread1 = SDL_CreateThread(threadFunction, "LazyThread", &astar);
	SDL_Thread* thread2 = SDL_CreateThread(threadFunction, "LazyThread", &astar2);
	SDL_DetachThread(thread1);
	SDL_DetachThread(thread2);
	//want game loop to pause
	inputManager.AddListener(EventListener::Event::PAUSE, this);
	inputManager.AddListener(EventListener::Event::QUIT, this);

	return true;

}




void Game::destroy()
{
	renderer.destroy();
}

//** calls update on all game entities*/
void Game::update()
{
	//while (astar.getActive() != astar.getGoal())
	//{
	//	astar.doAstar();
	//}
}

//** calls render on all game entities*/

void Game::render()
{
	renderer.clear(Colour(0,0,0));// prepare for new frame

	for (int i = 0; i < BOARDSIZE; i++)
	{
		for (int j = 0; j < BOARDSIZE; j++)
		{
			if (i % 2 == 0) //all code below creates the checkerboard pattern
			{
				if (j % 2 == 0)
					renderer.drawFillRect(board[i][j], orange);
				else
					renderer.drawFillRect(board[i][j], yellow);
			}
			else
			{
				if (j % 2 == 0)
					renderer.drawFillRect(board[i][j], yellow);
				else
					renderer.drawFillRect(board[i][j], orange);
			}

			if (astar.getGoal() == std::pair<int, int>(i, j)) //sets the goal tile to red
				renderer.drawFillRect(board[i][j], red);
			else if (astar.getStart() == std::pair<int, int>(i, j)) //sets the start tile to green
				renderer.drawFillRect(board[i][j], green);
			else if (astar.getActive() == std::pair<int, int>(i, j)) //sets the active tile to black
				renderer.drawFillRect(board[i][j], black);
			//else if (astar.isOnList(astar.getWalls(), std::pair<int, int>(i, j))) //sets the walls to black
			//	renderer.drawFillRect(board[i][j], black);
			//else if (astar.isOnList(astar.getClosed(), std::pair<int, int>(i, j))) //sets the closed to blue
			//	renderer.drawFillRect(board[i][j], blue);
		}	
	}

	renderer.present();// display the new frame (swap buffers)	
}

/** update and render game entities*/
void Game::loop()
{
	while (!quit) 
	{ //game loop
		inputManager.ProcessInput();

		if(!pause) //in pause mode don't bother updateing
			update();

		render();
	}
}

void Game::onEvent(EventListener::Event evt) {

	if (evt == EventListener::Event::PAUSE) {
		pause = !pause;
	}
	
	if (evt == EventListener::Event::QUIT) {
		quit=true;
	}

}
