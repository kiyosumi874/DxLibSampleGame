#pragma once

/// <summary>
/// �S�ẴI�u�W�F�N�g�̐e�N���X
/// </summary>
class GameObject
{
public:
	virtual ~GameObject() { /*��������*/ };

	virtual void Update(float deltaTime) = 0;
	virtual void Draw() = 0;
};