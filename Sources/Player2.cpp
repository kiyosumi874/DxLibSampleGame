#include "Player2.h"

Player2::Player2()
	: pos(VGet(450.0f, 300.0f, 0.0f))
	, currentJumpSpeed(0.0f)
	, onGround(true)
	, isJumpButtonDown(false)
{
}

Player2::~Player2()
{
}

void Player2::Update(float deltaTime)
{
	CheckOnGround();
	Move();
	Jump();
}

void Player2::Draw()
{
	DrawCircle(pos.x, pos.y, 50, GetColor(0, 0, 255), true);
}


/// <summary>
/// ベクトルを使った移動
/// </summary>
void Player2::Move()
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
	

	// 大きさが0のベクトルをNormalize(正規化)しようとすると
	// 0除算エラーってやつになるので気を付ける
	if (isInput)
	{
		inputVec = VNorm(inputVec);
	}

	inputVec = VScale(inputVec, MoveSpeed);
	pos = VAdd(pos, inputVec);
}

/// <summary>
/// ジャンプ
/// </summary>
void Player2::Jump()
{
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		if (!isJumpButtonDown)
		{
			if (onGround)
			{
				currentJumpSpeed -= JumpPower;
				onGround = false;
			}
		}
		isJumpButtonDown = true;
	}
	else
	{
		isJumpButtonDown = false;
	}

	if (!onGround)
	{
		pos.y += currentJumpSpeed;
		currentJumpSpeed += Gravity;
	}
}

/// <summary>
/// 着地しているかチェック
/// </summary>
void Player2::CheckOnGround()
{
	if (!onGround)
	{
		if (pos.y + currentJumpSpeed > 300.0f)
		{
			pos.y = 300.0f;
			currentJumpSpeed = 0.0f;
			onGround = true;
		}
	}
}