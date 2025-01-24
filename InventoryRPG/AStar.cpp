#include "AStar.h"

#include "raylib.h"

#include <vector>

std::vector<Node> AStar::Algorithm(const std::vector<std::vector<float>>& grid, Vec2 start, Vec2 goal)
{
	printf("Pathfinding Start !!");

	Node* startNode = new Node(start);
	Node* goalNode = new Node(goal);

	startNode->g = 0;
	startNode->h = Heuristic(startNode, goalNode);
	startNode->f = startNode->g + startNode->h;
	openNodes.push_back(startNode);

	std::vector<Node> path;

	while(!openNodes.empty())
	{
		// Find the node with the lowest f
		Node* currentNode = openNodes[0];

		for(int i = 0; i < openNodes.size(); ++i)
		{
			if(openNodes[i]->f < currentNode->f)
			{
				currentNode = openNodes[i];
			}
		}

		// Remove the current node from openNodes
		auto it = std::find(openNodes.begin(), openNodes.end(), currentNode);
		if(it != openNodes.end())
		{
			openNodes.erase(it);
		}

		// Check if we reached the goal
		if(currentNode->position == goalNode->position)
		{
			while(currentNode != nullptr)
			{
				path.push_back(*currentNode);
				currentNode = currentNode->parent;
			}

			std::reverse(path.begin(), path.end());

			// Output the path
			printf("Path found:\n");
			//for(Node node : path)
			//{
			//	printf("%s", node.position.ToString().c_str());
			//}

			// Clean up dynamically allocated nodes
			CleanupNodes(openNodes);
			CleanupNodes(closedNodes);
			return path;
		}

		// Add current node to closedNodes
		closedNodes.push_back(currentNode);

		// Check child
		for(Node* child : GetChildrens(currentNode, grid))
		{
			// If child is in closedNodes, skip it
			if(std::find_if(closedNodes.begin(), closedNodes.end(), [child](Node* node)
			{
				return *child == *node;
			}) != closedNodes.end())
			{
				delete child;
				continue;
			}

			// Calculate g, h, and f values
			child->g = currentNode->g + currentNode->GetDistance(*child) * ( 1 + 2 * child->costMultiplier );
			child->h = Heuristic(child, goalNode);
			child->f = child->g + child->h;

			// Check if the child is in the open list
			auto children = std::find_if(openNodes.begin(), openNodes.end(), [child](Node* node)
			{
				return *child == *node;
			});

			if(children != openNodes.end()) // Already in open list
			{
				if(child->g >= ( *children )->g)
				{
					delete child;
					continue;
				}
				else // Better path found, update the node
				{
					( *children )->g = child->g;
					( *children )->f = child->f;
					( *children )->parent = currentNode;
					delete child;
				}
			}
			else // Add the child to the open list
			{
				child->parent = currentNode;
				openNodes.push_back(child);
			}
		}
	}

	// No path found
	printf("No Path found !\n");

	// Clean up dynamically allocated nodes
	CleanupNodes(openNodes);
	CleanupNodes(closedNodes);
	return path;
}

// GetChildrens function for grid
std::vector<Node*> AStar::GetChildrens(Node* current, const std::vector<std::vector<float>>& grid)
{
	std::vector<Node*> childrens;

	const std::vector<Vec2> directions =
	{
		Vec2(0, 1), // Up
		Vec2(0, -1),  // Down
		Vec2(-1, 0), // Left
		Vec2(1, 0),   // Right
		Vec2(-1, 1), //Left - Up
		Vec2(1, 1), //Right - Up
		Vec2(-1, -1), //Left - Down
		Vec2(1, -1) //Right - Down
	};

	for(const Vec2& dir : directions)
	{
		Vec2 newPos = current->position + dir;

		// Check bounds
		if(newPos.x >= 0 && newPos.x < grid.size() &&
			newPos.y >= 0 && newPos.y < grid[0].size())
		{
			// Check if the position is walkable (not an obstacle)
			if(grid[newPos.y][newPos.x] < 1) // Assuming 0 is walkable and 1 is an obstacle
			{
				Node* newNode = new Node(newPos);
				newNode->costMultiplier = grid[newPos.y][newPos.x];
				childrens.push_back(newNode);
			}
		}
	}

	return childrens;
}

// Heuristic Function: Manhattan Distance
float AStar::Heuristic(Node* a, Node* b)
{
	return std::abs(a->position.x - b->position.x) + std::abs(a->position.y - b->position.y);
}


// Cleanup Function
void AStar::CleanupNodes(std::vector<Node*>& nodes)
{
	for(Node* node : nodes)
	{
		delete node;
	}
	nodes.clear();
}
