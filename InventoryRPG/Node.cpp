#include "Node.h"

#include <limits>
#define inf std::numeric_limits<int>::max()

Node::Node(Vec2 pPosition) : position(pPosition)
{
	g = inf;
	h = inf;
	f = inf;

	parent = nullptr;
}

float Node::GetDistance(const Node& from)
{
	return ( position - from.position ).SqrDistance();
}

bool Node::operator==(const Node& node) const
{
	return position == node.position;
}
