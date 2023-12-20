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

	// DxLib�̃Z�b�g�A�b�v
	SetGraphMode(WindowWidth, WindowHeight, ColorBitNum);
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1)
	{
		return -1;
	}
	SetDrawScreen(DX_SCREEN_BACK);

	float deltaTime = 1.0f / 60.0f; // ��O�̃Q�[�����[�v���������̂Ɋ|����������
	list<GameObject*> gameObjects;
	Ground* ground = new Ground(WindowWidth, WindowHeight, 100, GetColor(0,255,0));
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