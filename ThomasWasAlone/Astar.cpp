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

}

void Astar::calculateCosts(std::pair<int, int> index)
{


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



