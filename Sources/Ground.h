#pragma once
#include "DxLib.h"
#include "GameObject.h"

/// <summary>
/// 床
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

	// Bloom用
	int colorScreen;	// 普通の描画結果を書き込むスクリーン
	int highBrightScreen;	// 普通の描画結果から高輝度部分を抜き出した結果を書き込むスクリーン
	int downScaleScreen;	// 高輝度部分を縮小した結果を書き込むスクリーン
	int gaussScreen;	// 縮小画像をガウスフィルタでぼかした結果を書き込むスクリーン
	int gaussRatio; // ガウスフィルタのぼかし具合
	int clipParam;
};