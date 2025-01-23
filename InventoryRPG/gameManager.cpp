#include "gameManager.h"

void GameManager::Init()
{

	//map Image
	mapImage = LoadImage("ressource/arthur-map.png");
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

	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && firstPos)
	{
		start = GetGridPositionFromMouse(GetMouseX(), GetMouseY());
		firstPos = false;
	}
	else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !firstPos)
	{
		goal = GetGridPositionFromMouse(GetMouseX(), GetMouseY());
		//firstPos = true;
	}

	if ((start.x != 0) && (start.y != 0) && (goal.x != 0) && (goal.y != 0) && !hasRunAStar)
	{
		path = astar.Algorithm(grid, start, goal);

		hasRunAStar = true;

		for (Node* node : path)
		{
			printf("%s", node->position.ToString().c_str());
		}
	}
}

void GameManager::Draw()
{
	DrawTextureEx(mapTexture, { 0,0 }, 0, mapSize, WHITE);
	DrawText(TextFormat("%.2f", value), 20, 20, 20, RED);
	DrawText(TextFormat("(%.f : %.f),(%.f : %.f)", start.x,start.y, goal.x,goal.y), 20, 50, 20, RED);

	// Draw the path
	for (const Node* node : path)
	{
		DrawRectangle(node->position.x * mapSize, node->position.y * mapSize, mapSize, mapSize, RED);
	}
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

Vec2 GameManager::GetGridPositionFromMouse(int mouseX, int mouseY)
{
	int gridX = static_cast<int>(mouseX / mapSize);
	int gridY = static_cast<int>(mouseY / mapSize);
	return Vec2(gridX, gridY);
}

void GameManager::Cleanup()
{
	for (Node* node : path)
	{
		delete node;
	}
	path.clear();
}
