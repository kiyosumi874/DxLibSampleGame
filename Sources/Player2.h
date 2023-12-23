#pragma once 
#include "DxLib.h"
#include "GameObject.h"

class Player2 : public GameObject
{
public:
	Player2();
	~Player2();

	void Update(float deltaTime) override;
	void Draw() override;

private:
	/// <summary>
	/// �x�N�g�����g�����ړ�
	/// </summary>
	void Move();

	/// <summary>
	/// �W�����v
	/// </summary>
	void Jump();

	/// <summary>
	/// ���n���Ă��邩�`�F�b�N
	/// </summary>
	void CheckOnGround();

	static constexpr float JumpPower = 20.0f; // �W�����v�̏���
	static constexpr float MoveSpeed = 3.0f; // �ړ��X�s�[�h
	static constexpr float Gravity = 1.0f; // �d��

	VECTOR pos;
	float currentJumpSpeed; // ���݂̃W�����v�̃X�s�[�h
	bool onGround; // ���n���Ă��邩�H
	bool isJumpButtonDown; // �W�����v�{�^�����������ςȂ����H
};