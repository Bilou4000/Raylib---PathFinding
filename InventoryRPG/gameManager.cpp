#include "gameManager.h"

#include "AStar.h"

void GameManager::Init()
{
	std::vector<std::vector<float>> grid =
	{
		{ 0, 0, 0, 1, 0 },
		{ 1, 1, 0, 1, 0 },
		{ 0, 0, 0, 0.25f, 0 },
		{ 0, 0, 1, 1, 0 },
		{ 0, 0, 0, 0, 0 }
	};

	Vec2 start(0, 0);
	Vec2 goal(4, 4);

	AStar astar;
	astar.Algorithm(grid, start, goal);

	map = LoadTexture("ressource/map.png");
	mapSize = ( float ) GetScreenWidth() / map.width;
}

void GameManager::Update()
{
	
}

void GameManager::Draw()
{
	DrawTextureEx(map, { 0,0 }, 0, mapSize, WHITE);
}

void GameManager::Unload()
{
	
}
