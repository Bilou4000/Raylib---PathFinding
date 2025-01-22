#pragma once

#include "Vector2.h"

struct Node
{
	Node(Vec2 pPosition = Vec2(0, 0));
	float GetDistance(Node* from);

	Node* parent;
	Vec2 position;

	float g, h, f;
	float costMultiplier;
};

