#pragma once
#include "DxLib.h"
#include "GameObject.h"

/// <summary>
/// è∞
/// </summary>
class Ground : public GameObject
{
public:
	Ground(int windowWidth, int windowHeight, int size, unsigned int color);
	~Ground();

	void Update(float deltaTime) override;
	void Draw() override;
private:
	VECTOR position;
	int size;
	unsigned int color;
};