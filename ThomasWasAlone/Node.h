#pragma once
#include <unordered_map>

class Node
{
private:
	int g; //distance from start
	int h; //distance from end
	//int f; //g + h

	std::pair<int, int> m_pos;

public:
	void calculateCosts(/*goal*/std::pair<int, int>, /*start*/std::pair<int, int>);

	bool operator< (const Node &n) const;
	bool operator== (const Node &n) const;

	std::pair<int, int> getPos();

	Node(int, int);
	~Node();
};

