#include "stdafx.h"
#include "Astar.h"


Astar::Astar()
{
	for (int i = 0; i < BOARDSIZE; i++)
	{
		std::vector<Node> nodeLine;
		for (int j = 0; j < BOARDSIZE; j++)
		{
			nodeLine.push_back(Node(i, j));
		}	
		m_nodes.push_back(nodeLine);
	}
}


Astar::~Astar()
{
}

void Astar::doAstar()
{

	calculateSurroundingCosts(m_active);
}

void Astar::calculateSurroundingCosts(std::pair<int, int> index)
{
	//up
	if (index.first - 1 >= 0 && !isOnList(m_closed, std::pair<int, int>(index.first - 1, index.second))) //ensures it's not out of range or in the closed list
			m_nodes[index.first - 1][index.second].calculateCosts(m_goal, m_start);
	//down
	if (index.first + 1 <= BOARDSIZE && !isOnList(m_closed, std::pair<int, int>(index.first + 1, index.second)))
		m_nodes[index.first + 1][index.second].calculateCosts(m_goal, m_start);
	//left
	if (index.second - 1 >= 0 && !isOnList(m_closed, std::pair<int, int>(index.first, index.second - 1)))
		m_nodes[index.first][index.second - 1].calculateCosts(m_goal, m_start);
	//right
	if (index.second + 1 <= BOARDSIZE && !isOnList(m_closed, std::pair<int, int>(index.first, index.second + 1)))
		m_nodes[index.first][index.second + 1].calculateCosts(m_goal, m_start);
	//upRight
	if ((index.first - 1 >= 0 && index.second + 1 <= BOARDSIZE) && !isOnList(m_closed, std::pair<int, int>(index.first - 1, index.second + 1)))
		m_nodes[index.first - 1][index.second + 1].calculateCosts(m_goal, m_start);
	//downRight
	if ((index.first + 1 <= BOARDSIZE && index.second + 1 <= BOARDSIZE) && !isOnList(m_closed, std::pair<int, int>(index.first + 1, index.second + 1)))
		m_nodes[index.first + 1][index.second + 1].calculateCosts(m_goal, m_start);
	//upLeft
	if ((index.first - 1 >= 0 && index.second - 1 >= 0) && !isOnList(m_closed, std::pair<int, int>(index.first - 1, index.second - 1)))
		m_nodes[index.first - 1][index.second - 1].calculateCosts(m_goal, m_start);
	//downLeft
	if ((index.first + 1 <= BOARDSIZE && index.second - 1 >= 0) && !isOnList(m_closed, std::pair<int, int>(index.first + 1, index.second - 1)))
		m_nodes[index.first + 1][index.second - 1].calculateCosts(m_goal, m_start);
}

bool Astar::isOnList(std::vector<std::pair<int, int>> list, std::pair<int, int> item)
{
	return std::find(list.begin(), list.end(), item) != list.end();
}

Node Astar::getNode(std::pair<int, int> index)
{
	return m_nodes[index.first][index.second];
}

std::pair<int, int> Astar::getGoal() { return m_goal; }
void Astar::setGoal(std::pair<int, int> index) { m_goal = index; }
void Astar::setGoal(int i, int j) { m_goal.first = i; m_goal.second = j; }

std::pair<int, int> Astar::getActive() { return m_active; }
void Astar::setActive(std::pair<int, int> index) { m_active = index; }
void Astar::setActive(int i, int j) { m_active.first = i; m_active.second = j; }

std::vector<std::pair<int, int>> Astar::getWalls() { return m_walls; }
void Astar::setWall(std::pair<int, int> index) { m_walls.push_back(index); }
void Astar::setWall(int i, int j) { m_walls.push_back(std::pair<int, int>(i, j)); }

std::vector<std::pair<int, int>> Astar::getClosed() { return m_closed; }
void Astar::setClosed(std::pair<int, int> index) { m_closed.push_back(index); }



