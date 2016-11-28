#pragma once

#include <vector>

#include "Renderer.h"
#include "GameObject.h"
#include "InputManager.h"
#include "EventListener.h"
#include "Constants.h"

/** The game objct whic manages the game loop*/
class Game:public EventListener
{
	InputManager inputManager;
	Renderer renderer;

	unsigned int lastTime;//time of last update;

	bool pause;
	bool quit;
	int boardSize = 100;

	std::vector<Rect> board;

public:
	Game();
	~Game();

	bool init();
	void destroy();

	void update();
	void render();
	void loop();

	void onEvent(EventListener::Event);
};

