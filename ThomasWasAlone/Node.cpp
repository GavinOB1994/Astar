#include "stdafx.h"
#include "Node.h"


Node::Node(int i, int j)
{
	m_pos.first = i;
	m_pos.second = j;
}


Node::~Node()
{
}

void Node::calculateCosts(std::pair<int, int> goal, std::pair<int, int> start)
{

}



