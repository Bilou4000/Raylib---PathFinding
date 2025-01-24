#include "gameManager.h"

void GameManager::Init()
{

	//map Image
	mapImage = LoadImage("ressource/map2.png");
	colors = LoadImageColors(mapImage);

	//map Texture
	mapTexture = LoadTextureFromImage(mapImage);
	mapSize = ( float ) GetScreenWidth() / mapTexture.width;
	printf("MapSize: %f\n", mapSize);

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
	int gridX = GetMouseX() / mapSize;
	int gridY = GetMouseY() / mapSize;
	if(gridX >= 0 && gridX < grid[0].size() && gridY >= 0 && gridY < grid.size())
	{
		value = grid[gridY][gridX];
	}
	else
	{
		value = -1.0f;
	}

	//start = GetGridPositionFromMouse(GetMouseX(), GetMouseY());

	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && firstPos)
	{
		start = GetGridPositionFromMouse(GetMouseX(), GetMouseY());
		firstPos = false;
	}
	else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) )
	{
		goal = GetGridPositionFromMouse(GetMouseX(), GetMouseY());
		firstPos = true;
		canRunAStar = true;
	}

	if (canRunAStar)
	{
		path = astar.Algorithm(grid, start, goal);

		for (Node node : path)
		{
			printf("%s", node.position.ToString().c_str());
		}

		canRunAStar = false;
	}
}

void GameManager::Draw()
{
	//Vec2 mousePos = GetGridPositionFromMouse(GetMouseX(), GetMouseY());

	DrawTextureEx(mapTexture, { 0,0 }, 0, mapSize, WHITE);
	DrawText(TextFormat("%.2f", value), 20, 20, 20, RED);
	DrawText(TextFormat("(%.f : %.f),(%.f : %.f)", start.x,start.y, goal.x,goal.y), 20, 50, 20, RED);
	//DrawText(TextFormat("Mouse Pos : (%.f : %.f)", mousePos.x,mousePos.y), 20, 70, 20, RED);

	DrawRectangle(start.x * mapSize, start.y * mapSize, mapSize, mapSize, VIOLET);
	DrawRectangle(goal.x * mapSize, goal.y * mapSize, mapSize, mapSize, PINK);

	// Draw the path
	for (const Node node : path)
	{
		DrawRectangle(node.position.x * mapSize, node.position.y * mapSize, mapSize, mapSize, RED);
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
	//mostly green
	if(color.g > color.r && color.g > color.b)
	{
		return 0.0f;
	}
	//mostly white or black or red
	if((color.r > 240 && color.g > 240 && color.b > 240) || (color.r < 10 && color.g < 10 && color.b < 10) || ( color.r > color.g && color.r > color.b ))
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
