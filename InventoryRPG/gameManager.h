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

	float MapColorToValue(Color color);

private:
	std::vector<std::vector<float>> grid;

	Image mapImage;
	Texture2D mapTexture;
	Color* colors;
	float mapSize = 1;
	float value = -1;
};

