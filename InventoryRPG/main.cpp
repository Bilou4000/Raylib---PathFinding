#include "raylib.h"

#include "gameManager.h"

#include <vector>
#include <iostream>

void Load();
void Update();
void Draw();
void Unload();

GameManager gameManager;

int main()
{
	Load();

	while (!WindowShouldClose()) {
		Update();
		Draw();
	}

	Unload();

	return 0;
}

void Load()
{
	InitWindow(1080, 720, "PathFinding");
	SetTargetFPS(60);

	gameManager.Init();
}

void Update()
{
	gameManager.Update();
}

void Draw()
{
	BeginDrawing();

	ClearBackground(LIGHTGRAY);
	gameManager.Draw();

	EndDrawing();
}

void Unload()
{
	gameManager.Unload();

	CloseWindow();
}