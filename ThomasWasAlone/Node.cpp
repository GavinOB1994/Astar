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
	g = sqrt((m_pos.first - start.first) * (m_pos.first - start.first)) + sqrt((m_pos.second - start.second) * (m_pos.second - start.second));
	h = sqrt((m_pos.first - goal.first) * (m_pos.first - goal.first)) + sqrt((m_pos.second - goal.second) * (m_pos.second - goal.second));
}

bool Node::operator<(const Node & n) const
{
	//changing this between f or h will change the searches priority
	return h + g > n.h + n.g; //The operator is reversed for the sake of the priority queue, so that the smallest go to the top
}

bool Node::operator==(const Node & n) const
{
	return m_pos == n.m_pos; //I'm not sure, but there is a chance this will break the priority queue
}
std::pair<int, int> Node::getPos() { return m_pos; }



