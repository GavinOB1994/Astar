#pragma once
#include <vector>
#include <queue>
#include <SDL_thread.h>
#include "Node.h"
#include "Constants.h"

class Astar
{
private:

	std::vector<std::vector<Node>> m_nodes; //open nodes
	std::vector<std::pair<int,int>> m_closed;
	std::vector<std::pair<int, int>> m_walls;
	std::priority_queue<Node> searchOrder;
	std::pair<int, int> m_goal;
	std::pair<int, int> m_start;
	std::pair<int, int> m_active;
	std::pair<int, int> m_prevActive;

	Node m_tempNode = Node();

	SDL_mutex *mutex;

public:
	Astar() {};
	Astar(std::pair<int, int>, std::pair<int, int>);
	~Astar();

	void doAstar();

	Node getNode(std::pair<int, int>);

	bool isOnList(std::vector<std::pair<int, int>>*, std::pair<int, int>);
	bool isTraversable(std::pair<int, int>);
	bool isOpen(Node);

	std::pair<int, int> getGoal();
	void setGoal(std::pair<int, int>);
	void setGoal(int, int);

	std::pair<int, int> getActive();
	void setActive(std::pair<int, int>);
	void setActive(int, int);

	std::pair<int, int> getStart();
	void setStart(std::pair<int, int>);
	void setStart(int, int);

	SDL_mutex* getMutex();

	std::vector<std::pair<int, int>> getClosed();
	void setClosed(std::pair<int, int>);
	void setClosed(int, int);

	void calculateSurroundingCosts(std::pair<int, int>);
};

