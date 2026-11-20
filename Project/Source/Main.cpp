#include"DxLib.h" 

#include "Map/MapManager.h"

#include "../Source/Map/Block.h"

#include "Input/Input.h"

#include "Player/Player.h"
#include "PlayerAttack/PlayerAttack.h"
#include "Enemy/Enemy.h"
#include "Camera/Camera.h"
#include "Bullet/Bullet.h"

//プログラムの初めはWinMainから始まります

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstamce, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)

{

    SetGraphMode(1600, 900, 32);

    ChangeWindowMode(TRUE);

    if (DxLib_Init() == -1)  //DXライブラリ初期化処理

    {

        return -1;           //エラーが起きたら直ちに終了

    }

    InitBlock();

    InitMap();

    InitInput();

    InitCamera();

    InitPlayer();

    InitPlayerAttack();

    InitBullet();
    
    InitEnemy();

    LoadPlayer();

    LoadPlayerAttack();

    LoadBullet();

    LoadEnemy();

    LoadMap();

    StartMap();

    StartPlayer();

    StartEnemy();

    SetDrawScreen(DX_SCREEN_BACK);

    while (ProcessMessage() >= 0)

    {
        StepCamera();

        ClearDrawScreen();

        UpdateInput();

        UpdatePlayer();

        UpdatePlayerAttack();

        UpdateBullet();

        UpdateEnemy();

        PlayerHitEnemy();

        PlayerAttackHitEnemy();

        DrawBox(0, 0, 1600, 900,

            GetColor(255, 255, 255), TRUE);

        if (CheckHitKey(KEY_INPUT_ESCAPE))

        {

            break;

        }

        DrawMap();

        DrawBullet();

        DrawEnemy();

        DrawPlayer();

        DrawPlayerAttack();

        ScreenFlip();

    }
    FinEnemy();
}
