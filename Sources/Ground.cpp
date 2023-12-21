#include "Ground.h"

Ground::Ground(int windowWidth, int windowHeight, int size, unsigned int color)
	: position(VGet(0.0f,0.0f,0.0f))
	, size(size)
	, color(color)
	, colorScreen(0)
	, highBrightScreen(0)
	, downScaleScreen(0)
	, gaussScreen(0)
	, gaussRatio(30)
	, clipParam(29)
{
	position.x = windowWidth / 2.0f;
	position.y = windowHeight / 2.0f;

	// 通常の描画結果を書き込むスクリーンと、フィルターの処理結果を書き込むスクリーンの作成
	colorScreen = MakeScreen(windowWidth, windowHeight, FALSE);
	highBrightScreen = MakeScreen(windowWidth, windowHeight, FALSE);
	downScaleScreen = MakeScreen(windowWidth / 8, windowHeight / 8, FALSE);
	gaussScreen = MakeScreen(windowWidth / 8, windowHeight / 8, FALSE);
}

Ground::~Ground()
{
	// 処理無し
}

void Ground::Update(float deltaTime)
{
#ifdef _DEBUG
	if (CheckHitKey(KEY_INPUT_UP))
	{
		gaussRatio++;
	}
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		gaussRatio--;
	}
#endif // _DEBUG
}

void Ground::Draw()
{
	auto size2 = size / 60.0f;

	// 通常の描画結果を書き込むスクリーンを描画対象にする
	SetDrawScreen(colorScreen);
	DrawBox(position.x - size / 2.0f, position.y - size / 2.0f, position.x + size / 2.0f, position.y + size / 2.0f, color, TRUE);
	DrawBox(position.x - size2 + size / 2.0f, position.y - size / 2.0f, position.x + size2 + size / 2.0f, position.y + size / 2.0f, GetColor(255, 0, 0), TRUE);
	// 描画結果から高輝度部分のみを抜き出した画像を得る
	GraphFilterBlt(colorScreen, highBrightScreen, DX_GRAPH_FILTER_BRIGHT_CLIP, DX_CMP_LESS, clipParam, TRUE, GetColor(0, 0, 0), 255);
	// 高輝度部分を８分の１に縮小した画像を得る
	GraphFilterBlt(highBrightScreen, downScaleScreen, DX_GRAPH_FILTER_DOWN_SCALE, 8);
	// ８分の１に縮小した画像をガウスフィルタでぼかす
	GraphFilterBlt(downScaleScreen, gaussScreen, DX_GRAPH_FILTER_GAUSS, 16, gaussRatio);
	// 描画対象を裏画面にする
	SetDrawScreen(DX_SCREEN_BACK);
	// 通常の描画結果を描画する
	DrawGraph(0, 0, colorScreen, FALSE);
	// 描画モードをバイリニアフィルタリングにする( 拡大したときにドットがぼやけるようにする )
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	// 描画ブレンドモードを加算にする
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	// 高輝度部分を縮小してぼかした画像を画面いっぱいに２回描画する( ２回描画するのはより明るくみえるようにするため )
	DrawExtendGraph(0, 0, 640, 480, gaussScreen, FALSE);
	DrawExtendGraph(0, 0, 640, 480, gaussScreen, FALSE);
	// 描画ブレンドモードをブレンド無しに戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	// 描画モードを二アレストに戻す
	SetDrawMode(DX_DRAWMODE_NEAREST);
#ifdef _DEBUG
	printfDx("gaussRatio[%d]\n", gaussRatio);
#endif // _DEBUG
}
