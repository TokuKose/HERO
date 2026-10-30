#include "DxLib.h"
#include "GameClearScene.h"
#include "../../BackGround/BackGround.h"
#include "../../Input/Input.h"
#include "../../Scene/SceneManager.h"
//#include "../../Sound/SoundManager.h"
//#include "../../UI/UIText.h"
//#include "../../Score/Score.h"
#include <stdio.h>

// 背景のスクロール速度
#define BACK_GROUND_SPEED (-1.5)

// GameClear文字画像
int g_GameClearHandle = 0;

void InitGameClearScene()
{
	// 背景初期化
	InitBackGround();

	// 文字画像ハンドル初期化
	g_GameClearHandle = 0;
}

void LoadGameClearScene()
{
	// 背景ロード
	LoadBackGround("Data/Title/TitleBG.png", BACK_GROUND_LAYER_1);
	// 背景スクロール
	SetBackGroundMove(BACK_GROUND_SPEED, 0.0f, BACK_GROUND_LAYER_1);

	// GameClear文字画像
	g_GameClearHandle = LoadGraph("Data/GameClear/GameClear.png");
}

void StartGameClearScene()
{
	// スコアUI生成
	// スコア
	//CreateScoreUI(436.0f, 450.0f);
	//// ハイスコア
	//CreateHiScoreUI(390, 315);

	//// BGM再生
	//PlayBGM(BGM_GAME_CLEAR);
}

void StepGameClearScene()
{
	// 背景ステップ
	StepBackGround();

	// Zキーでタイトルに戻る
	if (IsTriggerKey(KEY_Z))
	{
		ChangeScene(SCENE_TITLE);
	}
}

void UpdateGameClearScene()
{
	// 背景更新
	UpdateBackGround();
}

void DrawGameClearScene()
{
	// 背景描画
	DrawBackGround();

	// 文字画像描画
	DrawGraph(560, 110, g_GameClearHandle, TRUE);

	// スコア描画
	//DrawUIText();
}

void FinGameClearScene()
{
	// 背景終了
	FinBackGround();

	// 文字画像削除
	DeleteGraph(g_GameClearHandle);

	// スコアUIリセット
	//ResetUIText();

	// BGM停止
	//StopBGM(BGM_GAME_CLEAR);
}
