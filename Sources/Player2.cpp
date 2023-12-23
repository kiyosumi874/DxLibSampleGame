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
/// �x�N�g�����g�����ړ�
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
	

	// �傫����0�̃x�N�g����Normalize(���K��)���悤�Ƃ����
	// 0���Z�G���[���Ă�ɂȂ�̂ŋC��t����
	if (isInput)
	{
		inputVec = VNorm(inputVec);
	}

	inputVec = VScale(inputVec, MoveSpeed);
	pos = VAdd(pos, inputVec);
}

/// <summary>
/// �W�����v
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
/// ���n���Ă��邩�`�F�b�N
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