#include "DxLib.h"
#include "Camera/Camera.h"
//#include "FPS/FPS.h"
//#include "Scene/SceneManager.h"
//#include "UI/UIImage.h"
//#include "UI/UIText.h"
//#include "Sound/SoundManager.h"
#include "Map/MapManager.h"
// プログラムは WinMain から始まります
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
    // ウィンドウモードON
    //ChangeWindowMode(TRUE);

    // 画面解像度の設定
    //SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_COLOR_DEPTH);

    if (DxLib_Init() == -1)        // ＤＸライブラリ初期化処理
    {
        return -1;            // エラーが起きたら直ちに終了
    }

    InitMap();

    LoadMap();

    // ウィンドウサイズ設定
    //SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);

    // 透過色の設定
    //SetTransColor(TRANS_COLOR_R, TRANS_COLOR_G, TRANS_COLOR_B);

    // 描画先を裏画面にする
    SetDrawScreen(DX_SCREEN_BACK);

    // 入力システムを初期化
    //InitInput();

    // UIはどこでも使うのでゲーム起動時に初期化、ロード
    //InitUIImage();
    //InitUIText();

    //LoadUIImage();
    //LoadUIText();

    // サウンドもどこでも使うのでゲーム起動時にロード
    //LoadBGM();
    //LoadSE();

    // FPS制御を初期化
    //InitFPS();

    // ゲームのメインループ
    while (ProcessMessage() >= 0)
    {
        // ループ処理前に1ミリ秒止めると処理が安定する
        Sleep(1);

        // 画面をクリア
        ClearDrawScreen();

        // 入力を更新
        //UpdateInput();

        // シーン管理の更新
        //SceneManagerUpdate();

        // 入力システムの描画
        //DrawInput();

        StartMap();

        DrawMap();
        // エスケープキーで終了
        if (CheckHitKey(KEY_INPUT_ESCAPE)) break;

        // FPS制御を更新
        //UpdateFPS();

        // FPS描画
        //DrawFPS();

        // 1フレームが速すぎたら待機
        //FPSWait();

        // 画面フリップ
        ScreenFlip();
    }

    // 入力システムの終了
    //FinInput();

    // UI終了
    //FinUIImage();
    //FinUIText();

    // サウンド終了
    //FinBGM();
    //FinSE();

    DxLib_End();                // ＤＸライブラリ使用の終了処理

    return 0;                // ソフトの終了 
}