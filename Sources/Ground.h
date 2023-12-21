#pragma once
#include "DxLib.h"
#include "GameObject.h"

/// <summary>
/// ��
/// </summary>
class Ground : public GameObject
{
public:
	Ground(int windowWidth, int windowHeight, int size, unsigned int color);
	~Ground();

	void Update(float deltaTime) override;
	void Draw() override;
private:
	VECTOR position;
	int size;
	unsigned int color;

	// Bloom�p
	int colorScreen;	// ���ʂ̕`�挋�ʂ��������ރX�N���[��
	int highBrightScreen;	// ���ʂ̕`�挋�ʂ��獂�P�x�����𔲂��o�������ʂ��������ރX�N���[��
	int downScaleScreen;	// ���P�x�������k���������ʂ��������ރX�N���[��
	int gaussScreen;	// �k���摜���K�E�X�t�B���^�łڂ��������ʂ��������ރX�N���[��
	int gaussRatio; // �K�E�X�t�B���^�̂ڂ����
	int clipParam;
};