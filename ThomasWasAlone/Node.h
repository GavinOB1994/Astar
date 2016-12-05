#pragma once
#include <unordered_map>

class Node
{
private:
	int g; //distance from start
	int h; //distance from end
	int f; //g + h

	std::pair<int, int> m_pos;

public:
	void calculateCosts();

	Node(int, int);
	~Node();
};

