#include "SceneManager.h"
//#include "Title/TitleScene.h"
#include "Play/PlayScene.h"
#include "GameClear/GameClearScene.h"
#include "GameOver/GameOverScene.h"

// 最初に開かれるシーンを初期値にする
Scene g_NowScene = SCENE_PLAY;

// 次に遷移するシーン
Scene g_NextScene = SCENE_TITLE;

// シーンの状態
SceneState g_SceneState = SCENE_STATE_INIT;

// ループを終了するか
bool g_IsLoopEnd = false;

void SceneManagerUpdate()
{
	// シーンの状態ごとに各シーンの処理を呼ぶ
	switch (g_SceneState)
	{
	case SCENE_STATE_INIT:	// 初期化
		InitScene();

		// ロードへ
		g_SceneState = SCENE_STATE_LOAD;
		break;

	case SCENE_STATE_LOAD:	// ロード
		LoadScene();

		// ループ終了フラグを折っておく
		g_IsLoopEnd = false;

		// 開始へ
		g_SceneState = SCENE_STATE_START;
		break;

	case SCENE_STATE_START:	// 開始（ループ開始前に1回だけ）
		// 開始処理
		StartScene();

		// 開始へ
		g_SceneState = SCENE_STATE_LOOP;
		break;

	case SCENE_STATE_LOOP:	// ループ（ステップ→更新→描画）
		StepScene();
		UpdateScene();
		DrawScene();

		// ループ終了フラグが立ったら終了処理へ
		if (g_IsLoopEnd)
		{
			g_SceneState = SCENE_STATE_FIN;
		}
		break;

	case SCENE_STATE_FIN:	// 終了
		FinScene();

		// 次のシーンに切り替える
		g_NowScene = g_NextScene;
		// シーンは初期化から
		g_SceneState = SCENE_STATE_INIT;
		break;
	}
}

void InitScene()
{
	// 開いているシーンの初期化処理を呼ぶ
	switch (g_NowScene)
	{
	case SCENE_TITLE:	// タイトル
		//InitTitleScene();
		break;

	case SCENE_PLAY:	// プレイ
		InitPlayScene();
		break;

	case SCENE_GAME_CLEAR:	// ゲームクリア
		InitGameClearScene();
		break;

	case SCENE_GAME_OVER:	// ゲームオーバー
		InitGameOverScene();
		break;
	}
}

void LoadScene()
{
	// 開いているシーンのロード処理を呼ぶ
	switch (g_NowScene)
	{
	case SCENE_TITLE:	// タイトル
		//LoadTitleScene();
		break;

	case SCENE_PLAY:	// プレイ
		LoadPlayScene();
		break;

	case SCENE_GAME_CLEAR:	// ゲームクリア
		LoadGameClearScene();
		break;

	case SCENE_GAME_OVER:	// ゲームオーバー
		LoadGameOverScene();
		break;
	}
}

void StartScene()
{
	// 開いているシーンのロード処理を呼ぶ
	switch (g_NowScene)
	{
	case SCENE_TITLE:	// タイトル
		//StartTitleScene();
		break;

	case SCENE_PLAY:	// プレイ
		StartPlayScene();
		break;

	case SCENE_GAME_CLEAR:	// ゲームクリア
		StartGameClearScene();
		break;

	case SCENE_GAME_OVER:	// ゲームオーバー
		StartGameOverScene();
		break;
	}
}

void StepScene()
{
	// 開いているシーンのステップ処理を呼ぶ
	switch (g_NowScene)
	{
	case SCENE_TITLE:	// タイトル
		//StepTitleScene();
		break;

	case SCENE_PLAY:	// プレイ
		StepPlayScene();
		break;

	case SCENE_GAME_CLEAR:	// ゲームクリア
		StepGameClearScene();
		break;

	case SCENE_GAME_OVER:	// ゲームオーバー
		StepGameOverScene();
		break;
	}
}

void UpdateScene()
{
	// 開いているシーンの更新処理を呼ぶ
	switch (g_NowScene)
	{
	case SCENE_TITLE:	// タイトル
		//UpdateTitleScene();
		break;

	case SCENE_PLAY:	// プレイ
		UpdatePlayScene();
		break;

	case SCENE_GAME_CLEAR:	// ゲームクリア
		UpdateGameClearScene();
		break;

	case SCENE_GAME_OVER:	// ゲームオーバー
		UpdateGameOverScene();
		break;
	}
}

void DrawScene()
{
	// 開いているシーンの描画処理を呼ぶ
	switch (g_NowScene)
	{
	case SCENE_TITLE:	// タイトル
		//DrawTitleScene();
		break;

	case SCENE_PLAY:	// プレイ
		DrawPlayScene();
		break;

	case SCENE_GAME_CLEAR:	// ゲームクリア
		DrawGameClearScene();
		break;

	case SCENE_GAME_OVER:	// ゲームオーバー
		DrawGameOverScene();
		break;
	}
}

void FinScene()
{
	// 開いているシーンの終了処理を呼ぶ
	switch (g_NowScene)
	{
	case SCENE_TITLE:	// タイトル
		//FinTitleScene();
		break;

	case SCENE_PLAY:	// プレイ
		FinPlayScene();
		break;

	case SCENE_GAME_CLEAR:	// ゲームクリア
		FinGameClearScene();
		break;

	case SCENE_GAME_OVER:	// ゲームオーバー
		FinGameOverScene();
		break;
	}
}

void ChangeScene(Scene scene)
{
	// 次に遷移するシーンを設定
	g_NextScene = scene;

	// シーンのループを終了させる
	g_IsLoopEnd = true;
}
