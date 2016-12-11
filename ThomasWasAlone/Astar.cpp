#include "stdafx.h"
#include "Astar.h"

Astar::Astar(std::pair<int, int> start, std::pair<int, int> end)
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

	setActive(start);
	setStart(start);
	setGoal(end);

	//for (int i = 0; i < BOARDSIZE; i++) //reserves the apropriate board size
	//{
	//	std::vector<Node> nodeLine;
	//	nodeLine.reserve(BOARDSIZE);
	//	m_nodes.push_back(nodeLine);
	//}

	m_nodes[start.first][start.second] = Node(start.first, start.second);
	m_nodes[start.first - 1][start.second].calculateCosts(end, start);
	searchOrder.push(m_nodes[start.first][start.second]);

	//wall list must be given values at the start here
}


Astar::~Astar()
{
}

void Astar::doAstar()
{
	calculateSurroundingCosts(m_active);



	m_prevActive = m_active; //just before the new active is assigned keep reor od the old active
	Node tempNode = searchOrder.top();
	searchOrder.pop(); //Remove from the priority queue
	m_active = tempNode.getPos();
	doAstar();
}

void Astar::calculateSurroundingCosts(std::pair<int, int> index)
{
	//up
	if (index.first - 1 >= 0 && isTraversable(m_closed, std::pair<int, int>(index.first - 1, index.second)) && !isOpen(m_nodes[index.first - 1][index.second])) //ensures it's not out of range or in the closed list or in the walls list
	{
		m_nodes[index.first - 1][index.second] = Node(index.first - 1, index.second);
		m_nodes[index.first - 1][index.second].calculateCosts(m_goal, m_start);
		searchOrder.push(m_nodes[index.first - 1][index.second]);
	}
	//down
	if (index.first + 1 <= BOARDSIZE && isTraversable(m_closed, std::pair<int, int>(index.first + 1, index.second)) && !isOpen(m_nodes[index.first + 1][index.second]))
	{
		m_nodes[index.first + 1][index.second] = Node(index.first - 1, index.second);
		m_nodes[index.first + 1][index.second].calculateCosts(m_goal, m_start);
		searchOrder.push(m_nodes[index.first + 1][index.second]);
	}
	//left
	if (index.second - 1 >= 0 && isTraversable(m_closed, std::pair<int, int>(index.first, index.second - 1)) && !isOpen(m_nodes[index.first][index.second - 1]))
	{
		m_nodes[index.first][index.second - 1] = Node(index.first - 1, index.second);
		m_nodes[index.first][index.second - 1].calculateCosts(m_goal, m_start);
		searchOrder.push(m_nodes[index.first][index.second - 1]);
	}
	//right
	if (index.second + 1 <= BOARDSIZE && isTraversable(m_closed, std::pair<int, int>(index.first, index.second + 1)) && !isOpen(m_nodes[index.first][index.second + 1]))
	{
		m_nodes[index.first][index.second + 1] = Node(index.first - 1, index.second);
		m_nodes[index.first][index.second + 1].calculateCosts(m_goal, m_start);
		searchOrder.push(m_nodes[index.first][index.second + 1]);
	}
	//upRight
	if ((index.first - 1 >= 0 && index.second + 1 <= BOARDSIZE) && isTraversable(m_closed, std::pair<int, int>(index.first - 1, index.second + 1)) && !isOpen(m_nodes[index.first - 1][index.second + 2]))
	{
		m_nodes[index.first - 1][index.second + 1] = Node(index.first - 1, index.second);
		m_nodes[index.first - 1][index.second + 1].calculateCosts(m_goal, m_start);
		searchOrder.push(m_nodes[index.first - 1][index.second + 1]);
	}
	//downRight
	if ((index.first + 1 <= BOARDSIZE && index.second + 1 <= BOARDSIZE) && isTraversable(m_closed, std::pair<int, int>(index.first + 1, index.second + 1)) && !isOpen(m_nodes[index.first + 1][index.second + 1]))
	{
		m_nodes[index.first + 1][index.second + 1] = Node(index.first - 1, index.second);
		m_nodes[index.first + 1][index.second + 1].calculateCosts(m_goal, m_start);
		searchOrder.push(m_nodes[index.first + 1][index.second + 1]);
	}
	//upLeft
	if ((index.first - 1 >= 0 && index.second - 1 >= 0) && isTraversable(m_closed, std::pair<int, int>(index.first - 1, index.second - 1)) && !isOpen(m_nodes[index.first - 1][index.second - 1]))
	{
		m_nodes[index.first - 1][index.second - 1] = Node(index.first - 1, index.second);
		m_nodes[index.first - 1][index.second - 1].calculateCosts(m_goal, m_start);
		searchOrder.push(m_nodes[index.first - 1][index.second - 1]);
	}
	//downLeft
	if ((index.first + 1 <= BOARDSIZE && index.second - 1 >= 0) && isTraversable(m_closed, std::pair<int, int>(index.first + 1, index.second - 1)) && !isOpen(m_nodes[index.first + 1][index.second - 1]))
	{
		m_nodes[index.first + 1][index.second - 1] = Node(index.first - 1, index.second);
		m_nodes[index.first + 1][index.second - 1].calculateCosts(m_goal, m_start);
		searchOrder.push(m_nodes[index.first + 1][index.second - 1]);
	}
}

bool Astar::isOnList(std::vector<std::pair<int, int>> list, std::pair<int, int> item)
{
	return std::find(list.begin(), list.end(), item) != list.end();
}

bool Astar::isTraversable(std::vector<std::pair<int, int>> list, std::pair<int, int> item)
{
	if (isOnList(m_walls, item) || isOnList(m_closed, item))
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool Astar::isOpen(Node item)
{
	for (int i = 0; i < BOARDSIZE; i++)
	{ 
		if (std::find(m_nodes[i].begin(), m_nodes[i].end(), item) != m_nodes[i].end())
		{
			return true;
		}
	}
	return false;
}

Node Astar::getNode(std::pair<int, int> index) { return m_nodes[index.first][index.second]; }

std::pair<int, int> Astar::getGoal() { return m_goal; }
void Astar::setGoal(std::pair<int, int> index) { m_goal = index; }
void Astar::setGoal(int i, int j) { m_goal.first = i; m_goal.second = j; }

std::pair<int, int> Astar::getActive() { return m_active; }
void Astar::setActive(std::pair<int, int> index) { m_active = index; }
void Astar::setActive(int i, int j) { m_active.first = i; m_active.second = j; }

std::pair<int, int> Astar::getStart() { return m_start; }
void Astar::setStart(std::pair<int, int> start) { m_start = start; }
void Astar::setStart(int x, int y) { m_start.first = x; m_start.second = y;}

std::vector<std::pair<int, int>> Astar::getWalls() { return m_walls; }
void Astar::setWall(std::pair<int, int> index) { m_walls.push_back(index); }
void Astar::setWall(int i, int j) { m_walls.push_back(std::pair<int, int>(i, j)); }

std::vector<std::pair<int, int>> Astar::getClosed() { return m_closed; }
void Astar::setClosed(std::pair<int, int> index) { m_closed.push_back(index); }



