#pragma once

#include "Node.h"

#include <vector>

class AStar
{
public:
	std::vector<Node> Algorithm(const std::vector<std::vector<float>>& grid, Vec2 start, Vec2 goal);
	std::vector<Node*> GetChildrens(Node* current, const std::vector<std::vector<float>>& grid);

	float Heuristic(Node* a, Node* b);
	void CleanupNodes(std::vector<Node*>& nodes);

private:
	std::vector<Node*> openNodes;
	std::vector<Node*> closedNodes;
};

