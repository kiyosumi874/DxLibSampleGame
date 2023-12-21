#include "DxLib.h"
#include <list>
#include "GameObject.h"
#include "Ground.h"

using namespace std;

// �G���g���[�|�C���g
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �萔
	constexpr int WindowWidth = 640; // ��ʂ̉���
	constexpr int WindowHeight = 480; // ��ʂ̏c��
	constexpr int ColorBitNum = 16; // �J���[�r�b�g��
	constexpr unsigned int White = 4294967295; // DxLib��GetColor�ł��炩���ߎ擾���Ă������F�̔ԍ�
	constexpr unsigned int Red = 4294901760;
	constexpr unsigned int Green = 4278255360;
	constexpr unsigned int Blue = 4278190335;
	constexpr unsigned int Yellow = 4294956032;

	// DxLib�̃Z�b�g�A�b�v
	SetGraphMode(WindowWidth, WindowHeight, ColorBitNum);
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1)
	{
		return -1;
	}
	SetDrawScreen(DX_SCREEN_BACK);
	//SetBackgroundColor(255, 255, 255);

	float deltaTime = 1.0f / 60.0f; // ��O�̃Q�[�����[�v���������̂Ɋ|����������
	list<GameObject*> gameObjects;
	Ground* ground = new Ground(WindowWidth, WindowHeight, 400, White);
	gameObjects.emplace_back(ground);

	// �Q�[�����[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		int prevCount = GetNowCount();
		ClearDrawScreen();
#ifdef _DEBUG
		clsDx();
		printfDx("deltaTime[%.3f]\n", deltaTime);
#endif // _DEBUG

		for (auto inst : gameObjects)
		{
			inst->Update(deltaTime);
			inst->Draw();
		}

		ScreenFlip();
		deltaTime = (GetNowCount() - prevCount) / 1000.0f;
	}

	gameObjects.clear();
	delete ground;

	// DxLib�̌㏈��
	DxLib_End();

	return 0;
}