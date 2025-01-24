#pragma once

#include "Vector2.h"

struct Node
{
	Node(Vec2 pPosition = Vec2(0, 0));
	float GetDistance(const Node& from);

	bool operator==(const Node& node) const;

	Node* parent;
	Vec2 position;

	float g, h, f;
	float costMultiplier;
};

