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
	/// �]���̈ړ�
	/// </summary>
	void MoveBad();
	/// <summary>
	/// �x�N�g�����g�����ړ�
	/// </summary>
	void Move();

	VECTOR pos;
	VECTOR pos2;
	float speed;
};