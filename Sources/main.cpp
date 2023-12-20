#include "DxLib.h"
#include <list>
#include "GameObject.h"
#include "Ground.h"

using namespace std;

// エントリーポイント
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// 定数
	constexpr int WindowWidth = 640; // 画面の横幅
	constexpr int WindowHeight = 480; // 画面の縦幅
	constexpr int ColorBitNum = 16; // カラービット数

	// DxLibのセットアップ
	SetGraphMode(WindowWidth, WindowHeight, ColorBitNum);
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1)
	{
		return -1;
	}
	SetDrawScreen(DX_SCREEN_BACK);

	float deltaTime = 1.0f / 60.0f; // 一個前のゲームループが一周するのに掛かった時間
	list<GameObject*> gameObjects;
	Ground* ground = new Ground(WindowWidth, WindowHeight, 100, GetColor(0,255,0));
	gameObjects.emplace_back(ground);

	// ゲームループ
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

	// DxLibの後処理
	DxLib_End();

	return 0;
}