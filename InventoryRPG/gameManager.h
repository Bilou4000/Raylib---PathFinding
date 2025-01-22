#pragma once
#include <string>
#include <vector>

#include "raylib.h"

class GameManager
{
public :
	void Init();
	void Update();
	void Draw();
	void Unload();

private:
	Texture2D map;
	float mapSize = 1;
};

