#pragma once 
#include "DxLib.h"
#include "GameObject.h"

class Player : public GameObject
{
public:
	Player();
	~Player();

	void Update(float deltaTime) override;
	void Draw() override;

private:
	/// <summary>
	/// 従来の移動
	/// </summary>
	void MoveBad();
	/// <summary>
	/// ベクトルを使った移動
	/// </summary>
	void Move();

	VECTOR pos;
	VECTOR pos2;
	float speed;
};