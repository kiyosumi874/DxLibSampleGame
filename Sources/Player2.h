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
	/// ベクトルを使った移動
	/// </summary>
	void Move();

	/// <summary>
	/// ジャンプ
	/// </summary>
	void Jump();

	/// <summary>
	/// 着地しているかチェック
	/// </summary>
	void CheckOnGround();

	static constexpr float JumpPower = 20.0f; // ジャンプの初速
	static constexpr float MoveSpeed = 3.0f; // 移動スピード
	static constexpr float Gravity = 1.0f; // 重力

	VECTOR pos;
	float currentJumpSpeed; // 現在のジャンプのスピード
	bool onGround; // 着地しているか？
	bool isJumpButtonDown; // ジャンプボタンを押しっぱなしか？
};