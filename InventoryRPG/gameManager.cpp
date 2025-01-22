#include "gameManager.h"

#include "AStar.h"

void GameManager::Init()
{
	//std::vector<std::vector<float>> grid =
	//{
	//	{ 0, 0, 0, 1, 0 },
	//	{ 1, 1, 0, 1, 0 },
	//	{ 0, 0, 0, 0.25f, 0 },
	//	{ 0, 0, 1, 1, 0 },
	//	{ 0, 0, 0, 0, 0 }
	//};

	//Vec2 start(0, 0);
	//Vec2 goal(4, 4);

	//AStar astar;
	//astar.Algorithm(grid, start, goal);

	//map Image
	mapImage = LoadImage("ressource/map.png");
	colors = LoadImageColors(mapImage);

	//map Texture
	mapTexture = LoadTextureFromImage(mapImage);
	mapSize = ( float ) GetScreenWidth() / mapTexture.width;

	int mapHeight = mapImage.height;
	int mapWidth = mapImage.width;
	grid = std::vector<std::vector<float>>(mapHeight, std::vector<float>(mapWidth));


	for(int y = 0; y < mapHeight; y++)
	{
		for(int x = 0; x < mapWidth; x++)
		{
			Color color = colors[y * mapWidth + x];
			grid[y][x] = MapColorToValue(color);
		}
	}
}

void GameManager::Update()
{
	value = grid[GetMouseY() / mapSize][GetMouseX() / mapSize];
}

void GameManager::Draw()
{
	DrawTextureEx(mapTexture, { 0,0 }, 0, mapSize, WHITE);
	DrawText(TextFormat("%.2f", value), 20, 20, 20, RED);

	DrawPixel(GetMouseX(), GetMouseY(), RED);
}

void GameManager::Unload()
{
	UnloadImageColors(colors);
	UnloadImage(mapImage);
	UnloadTexture(mapTexture);
}

float GameManager::MapColorToValue(Color color)
{
	//mostly white
	if(color.r > 240 && color.g > 240 && color.b > 240)
	{
		return 0.0f;
	}
	//mostly green
	if(color.g > color.r && color.g > color.b)
	{
		return 1.0f;
	}
	//mostly blue
	if(color.b > color.r && color.b > color.g)
	{
		return 0.5f;
	}

	return 0.0f;

}
