#pragma once
#include <vector>
#include "Node.h"
#include "Constants.h"

class Astar
{
private:

	std::vector<std::vector<Node>> m_nodes;
	std::vector<std::pair<int,int>> m_closed;
	std::vector<std::pair<int, int>> m_walls;
	std::pair<int, int> m_goal;
	std::pair<int, int> m_active;
	std::pair<int, int> m_prevActive;

public:
	Astar();
	~Astar();

	void doAstar();

	Node getNode(std::pair<int, int>);

	std::pair<int, int> getGoal();
	void setGoal(std::pair<int, int>);
	void setGoal(int, int);

	std::pair<int, int> getActive();
	void setActive(std::pair<int, int>);
	void setActive(int, int);

	std::vector<std::pair<int, int>> getWalls();
	void setWall(std::pair<int, int>);
	void setWall(int, int);

	std::vector<std::pair<int, int>> getClosed();
	void setClosed(std::pair<int, int>);

	void calculateCosts(std::pair<int, int>);
};

