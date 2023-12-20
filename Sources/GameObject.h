#pragma once

/// <summary>
/// 全てのオブジェクトの親クラス
/// </summary>
class GameObject
{
public:
	virtual ~GameObject() { /*処理無し*/ };

	virtual void Update(float deltaTime) = 0;
	virtual void Draw() = 0;
};