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

	// �ʏ�̕`�挋�ʂ��������ރX�N���[���ƁA�t�B���^�[�̏������ʂ��������ރX�N���[���̍쐬
	colorScreen = MakeScreen(windowWidth, windowHeight, FALSE);
	highBrightScreen = MakeScreen(windowWidth, windowHeight, FALSE);
	downScaleScreen = MakeScreen(windowWidth / 8, windowHeight / 8, FALSE);
	gaussScreen = MakeScreen(windowWidth / 8, windowHeight / 8, FALSE);
}

Ground::~Ground()
{
	// ��������
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

	// �ʏ�̕`�挋�ʂ��������ރX�N���[����`��Ώۂɂ���
	SetDrawScreen(colorScreen);
	DrawBox(position.x - size / 2.0f, position.y - size / 2.0f, position.x + size / 2.0f, position.y + size / 2.0f, color, TRUE);
	DrawBox(position.x - size2 + size / 2.0f, position.y - size / 2.0f, position.x + size2 + size / 2.0f, position.y + size / 2.0f, GetColor(255, 0, 0), TRUE);
	// �`�挋�ʂ��獂�P�x�����݂̂𔲂��o�����摜�𓾂�
	GraphFilterBlt(colorScreen, highBrightScreen, DX_GRAPH_FILTER_BRIGHT_CLIP, DX_CMP_LESS, clipParam, TRUE, GetColor(0, 0, 0), 255);
	// ���P�x�������W���̂P�ɏk�������摜�𓾂�
	GraphFilterBlt(highBrightScreen, downScaleScreen, DX_GRAPH_FILTER_DOWN_SCALE, 8);
	// �W���̂P�ɏk�������摜���K�E�X�t�B���^�łڂ���
	GraphFilterBlt(downScaleScreen, gaussScreen, DX_GRAPH_FILTER_GAUSS, 16, gaussRatio);
	// �`��Ώۂ𗠉�ʂɂ���
	SetDrawScreen(DX_SCREEN_BACK);
	// �ʏ�̕`�挋�ʂ�`�悷��
	DrawGraph(0, 0, colorScreen, FALSE);
	// �`�惂�[�h���o�C���j�A�t�B���^�����O�ɂ���( �g�債���Ƃ��Ƀh�b�g���ڂ₯��悤�ɂ��� )
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	// �`��u�����h���[�h�����Z�ɂ���
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	// ���P�x�������k�����Ăڂ������摜����ʂ����ς��ɂQ��`�悷��( �Q��`�悷��̂͂�薾�邭�݂���悤�ɂ��邽�� )
	DrawExtendGraph(0, 0, 640, 480, gaussScreen, FALSE);
	DrawExtendGraph(0, 0, 640, 480, gaussScreen, FALSE);
	// �`��u�����h���[�h���u�����h�����ɖ߂�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	// �`�惂�[�h���A���X�g�ɖ߂�
	SetDrawMode(DX_DRAWMODE_NEAREST);
#ifdef _DEBUG
	printfDx("gaussRatio[%d]\n", gaussRatio);
#endif // _DEBUG
}
