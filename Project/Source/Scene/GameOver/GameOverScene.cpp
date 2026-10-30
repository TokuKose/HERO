#include "DxLib.h"
#include "GameOverScene.h"
#include "../../BackGround/BackGround.h"
#include "../../Input/Input.h"
#include "../../Scene/SceneManager.h"
//#include "../../Sound/SoundManager.h"

// 背景のスクロール速度
#define BACK_GROUND_SPEED (-5.0f)

// 自動遷移までの待機時間
#define WAIT_TIMER		(300)

// 待機時間タイマー
int g_WaitTimer = 0;
// GameOver文字画像ハンドル
int g_GameOverHandle = 0;

void InitGameOverScene()
{
	// 背景初期化
	InitBackGround();

	// タイマー初期化
	g_WaitTimer = 0;
}

void LoadGameOverScene()
{
	// 背景ロード
	LoadBackGround("Data/Title/TitleBG.png", BACK_GROUND_LAYER_1);
	// 背景スクロール
	SetBackGroundMove(BACK_GROUND_SPEED, 0.0f, BACK_GROUND_LAYER_1);

	// GameOver文字画像
	g_GameOverHandle = LoadGraph("Data/GameOver/GameOver.png");
}

void StartGameOverScene()
{
	// 待機タイマーをセット
	g_WaitTimer = WAIT_TIMER;

	// BGM再生
	//PlayBGM(BGM_GAME_OVER);
}

void StepGameOverScene()
{
	// 背景ステップ
	StepBackGround();
	// タイマーをカウントダウン
	g_WaitTimer--;
}

void UpdateGameOverScene()
{
	// 背景更新
	UpdateBackGround();

	// タイマーが0もしくはZキーでタイトルに戻る
	if (g_WaitTimer <= 0 || IsTriggerKey(KEY_Z))
	{
		ChangeScene(SCENE_TITLE);
	}
}

void DrawGameOverScene()
{
	// 背景描画
	DrawBackGround();

	// GameOver文字画像描画
	DrawGraph(500, 350, g_GameOverHandle, TRUE);
}

void FinGameOverScene()
{
	// 背景終了
	FinBackGround();

	// 文字画像削除
	DeleteGraph(g_GameOverHandle);

	// BGM停止
	//StopBGM(BGM_GAME_OVER);
}
