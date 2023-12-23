#include "Player.h"

Player::Player()
	: pos(VGet(300.0f, 300.0f, 0.0f))
	, pos2(VGet(300.0f, 300.0f, 0.0f))
	, speed(3.0f)
{
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	MoveBad();
	Move();
}

void Player::Draw()
{
	DrawCircle(pos.x, pos.y, 50, GetColor(0, 255, 0), true);
	DrawCircle(pos2.x, pos2.y, 50, GetColor(255, 0, 0), true);
}

/// <summary>
/// 移動
/// </summary>
void Player::MoveBad()
{
	// ベクトルを使わない方法
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		pos2.x -= speed;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		pos2.x += speed;
	}
	if (CheckHitKey(KEY_INPUT_UP))
	{
		pos2.y -= speed;
	}
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		pos2.y += speed;
	}
}

/// <summary>
/// ベクトルを使った移動
/// </summary>
void Player::Move()
{
	VECTOR inputVec = VGet(0.0f, 0.0f, 0.0f);
	bool isInput = false;
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		inputVec.x--;
		isInput = true;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		inputVec.x++;
		isInput = true;
	}
	if (CheckHitKey(KEY_INPUT_UP))
	{
		inputVec.y--;
		isInput = true;
	}
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		inputVec.y++;
		isInput = true;
	}

	// 大きさが0のベクトルをNormalize(正規化)しようとすると
	// 0除算エラーってやつになるので気を付ける
	if (isInput)
	{
		inputVec = VNorm(inputVec);
	}

	inputVec = VScale(inputVec, speed);
	pos = VAdd(pos, inputVec);
}
