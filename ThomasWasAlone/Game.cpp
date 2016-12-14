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
		//cout << "astar" << endl;
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


bool Game::init() 
{	
	Size2D winSize(1000,1000);

	//creates our renderer, which looks after drawing and the window
	renderer.init(winSize,"Simple SDL App");

	//set up the viewport
	//we want the vp centred on origin and 20 units wide
	float aspectRatio = winSize.w / winSize.h;
	float vpWidth = 20;

	Size2D vpSize(vpWidth, vpWidth /aspectRatio);
	Point2D vpBottomLeft( -vpSize.w / 2, - vpSize.h / 2); 

	Rect vpRect(vpBottomLeft, vpSize);
	renderer.setViewPort(vpRect);

	//int wall1 = rand() % BOARDSIZE;
	//int wall2 = rand() % BOARDSIZE;
	//int wall3 = rand() % BOARDSIZE;

	//for (int i = 0; i < rand() % ((BOARDSIZE / 3) * 2); i++)
	//{
	//	walls.push_back(std::pair<int, int>(wall1, i));
	//}

	

	for (int i = 0; i < NOOFASTAR; i++)
	{
		astar.push_back(Astar(std::pair<int, int>(rand() % BOARDSIZE, rand() % BOARDSIZE), std::pair<int, int>(rand() % BOARDSIZE, rand() % BOARDSIZE)));
	}


	//astar = Astar(std::pair<int, int>(2, 2) , std::pair<int, int>(BOARDSIZE - 1, BOARDSIZE - 1)/*, &walls*/); //Create my instance of Astar
	//astar2 = Astar(std::pair<int, int>(10, 10), std::pair<int, int>(BOARDSIZE - 10, BOARDSIZE - 10)/*, &walls*/); //Create my instance of Astar
	//astar3 = Astar(std::pair<int, int>(11, 10), std::pair<int, int>(BOARDSIZE - 5, BOARDSIZE - 5)/*, &walls*/); //Create my instance of Astar
	//astar4 = Astar(std::pair<int, int>(10, 20), std::pair<int, int>(BOARDSIZE - 10, BOARDSIZE - 5)/*, &walls*/); //Create my instance of Astar
	//astar5 = Astar(std::pair<int, int>(13, 10), std::pair<int, int>(BOARDSIZE - 5, BOARDSIZE - 10)/*, &walls*/); //Create my instance of Astar


	float tWidth = winSize.w / BOARDSIZE;
	float tHeight = winSize.h / BOARDSIZE;

	for (int i = 0; i < BOARDSIZE; i++)
	{
		std::vector<Rect> rectLine;

		for (int j = 0; j < BOARDSIZE; j++)
			rectLine.push_back( Rect(tWidth * i, tHeight * j, tWidth, tHeight));

		board.push_back(rectLine);
	}


	//Run the thread
	int data = NULL;
	SDL_Thread* thread1 = SDL_CreateThread(threadFunction, "Astar 1", &astar[0]);
	SDL_Thread* thread2 = SDL_CreateThread(threadFunction, "Astar 2", &astar[1]);
	SDL_Thread* thread3 = SDL_CreateThread(threadFunction, "Astar 3", &astar[2]);
	SDL_Thread* thread4 = SDL_CreateThread(threadFunction, "Astar 4", &astar[3]);
	SDL_Thread* thread5 = SDL_CreateThread(threadFunction, "Astar 5", &astar[4]);

	SDL_DetachThread(thread1);
	SDL_DetachThread(thread2);
	SDL_DetachThread(thread3);
	SDL_DetachThread(thread4);
	SDL_DetachThread(thread5);

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

			for (int k = 0; k < NOOFASTAR; k++)
			{
				if (SDL_LockMutex(astar[k].getMutex()) == 0)
				{
					std::pair<int, int> index = std::pair<int, int>(i, j);

					if (astar[k].getGoal() == index) //sets the goal tile to red
						renderer.drawFillRect(board[i][j], red);
					if (astar[k].getStart() == index) //sets the start tile to green
						renderer.drawFillRect(board[i][j], green);
					if (astar[k].getActive() == index) //sets the active tile to black
						renderer.drawFillRect(board[i][j], black);

					SDL_UnlockMutex(astar[k].getMutex());
				}
			}


			//else if (astar.isOnList(&walls, std::pair<int, int>(i, j))) //sets the walls to black
			//	renderer.drawFillRect(board[i][j], black);
			//if (astar.isOnList(&astar.getClosed(), std::pair<int, int>(i, j))) //sets the closed to blue
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
