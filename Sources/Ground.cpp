#include "Ground.h"

Ground::Ground(int windowWidth, int windowHeight, int size, unsigned int color)
	: position(VGet(0.0f,0.0f,0.0f))
	, size(size)
	, color(color)
{
	position.x = windowWidth / 2.0f;
	position.y = windowHeight / 2.0f;
}

Ground::~Ground()
{
	// èàóùñ≥Çµ
}

void Ground::Update(float deltaTime)
{
	// èàóùñ≥Çµ
}

void Ground::Draw()
{
	DrawBox(position.x - size, position.y - size, position.x + size, position.y + size, color, TRUE);
}
