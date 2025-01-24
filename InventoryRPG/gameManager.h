#pragma once
#include <string>
#include <vector>

#include "raylib.h"
#include "Node.h"
#include "AStar.h"

class GameManager
{
public :
	void Init();
	void Update();
	void Draw();
	void Unload();

	float MapColorToValue(Color color);
	Vec2 GetGridPositionFromMouse(int mouseX, int mouseY);

private:
	std::vector<std::vector<float>> grid;
	std::vector<Node> path;
	std::vector<Node*> searched;

	AStar astar;
	Vec2 start = (0,0);
	Vec2 goal = (0,0);

	Image mapImage;
	Texture2D mapTexture;
	Color* colors;
	float mapSize = 1;
	float value = -1;

	bool firstPos = true;
	bool canRunAStar = false;
};

