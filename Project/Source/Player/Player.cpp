#include "DxLib.h"
#include "Player.h"
#include "../Camera/Camera.h"
#include "../Input/Input.h"


#define PLAYER_DEFAULT_POS_X (500.0f)
#define PLAYER_DEFAULT_POS_Y (600.0f)
#define PLAYER_MOVE_SPEED (4.0f)

// ジャンプ力
#define PLAYER_JUMP_POWER (12.0f)
// 重力
#define PLAYER_GRAVITY (0.4f)

// マップ衝突判定用のプレイヤーサイズ補正
#define PLAYER_MAP_COLLISION_OFFSET (0.05f)
// 矩形判定の位置補正
#define PLAYER_BOX_COLLISION_OFFSET_X (24)
#define PLAYER_BOX_COLLISION_OFFSET_Y (20)
// 矩形判定のサイズ
#define PLAYER_BOX_COLLISION_WIDTH (20)
#define PLAYER_BOX_COLLISION_HEIGHT (44)

PlayerData g_PlayerData = { 0 };
PlayerData g_PrevPlayerData = { 0 };


void InitPlayer()
{
	g_PlayerData.posX = PLAYER_DEFAULT_POS_X;
	g_PlayerData.posY = PLAYER_DEFAULT_POS_Y;
	g_PlayerData.moveX = 0.0f;
	g_PlayerData.moveY = 0.0f;
	g_PlayerData.active = false;

	g_PlayerData.handle1 = LoadGraph("Data/Player/Player1.png");

	g_PlayerData.posX = PLAYER_DEFAULT_POS_X;
	g_PlayerData.posY = PLAYER_DEFAULT_POS_Y;
	g_PlayerData.moveX = PLAYER_MOVE_SPEED;
	g_PlayerData.moveY = PLAYER_MOVE_SPEED;
	//g_PlayerData.playAnim = PLAYER_ANIM_NONE;

	//for (int i = 0; i < PLAYER_ANIM_MAX; i++)
	//{
		//InitAnimation(&g_PlayerData.animation[i]);
	//}

	// 構造体はmemsetで0初期化できる
	//memset(&g_PlayerData.boxCollision, 0, sizeof(g_PlayerData.boxCollision));
}

void LoadPlayer()
{
	/*g_PlayerData.animation[PLAYER_ANIM_IDLE].handle = LoadGraph("Data/Player/PlayerIdle.png");
	g_PlayerData.animation[PLAYER_ANIM_RUN].handle = LoadGraph("Data/Player/PlayerRun.png");
	g_PlayerData.animation[PLAYER_ANIM_JUMP].handle = LoadGraph("Data/Player/PlayerJump.png");
	g_PlayerData.animation[PLAYER_ANIM_FALL].handle = LoadGraph("Data/Player/PlayerFall.png");
	g_PlayerData.animation[PLAYER_ANIM_LANDING].handle = LoadGraph("Data/Player/PlayerLanding.png");*/
	
}

void StartPlayer()
{
	// 生存フラグを立てる
	g_PlayerData.active = true;

	// 矩形判定設定
	/*g_PlayerData.boxCollision.posX = PLAYER_BOX_COLLISION_OFFSET_X;
	g_PlayerData.boxCollision.posY = PLAYER_BOX_COLLISION_OFFSET_Y;
	g_PlayerData.boxCollision.width = PLAYER_BOX_COLLISION_WIDTH;
	g_PlayerData.boxCollision.height = PLAYER_BOX_COLLISION_HEIGHT;*/

	// 待機アニメーションから開始する
	//StartPlayerAnimation(PLAYER_ANIM_IDLE);
}

void StepPlayer()
{
	// 死んでいたら何もしない
	if (!g_PlayerData.active)
	{
		return;
	}

	// 前回のデータとして記憶	
	g_PrevPlayerData = g_PlayerData;

	// X移動量は毎回リセットする
	g_PlayerData.moveX = 0.0f;

	// Y移動量に重力を反映
	g_PlayerData.moveY += PLAYER_GRAVITY;

	// 左入力
	if (IsInputKey(KEY_LEFT))
	{
		g_PlayerData.moveX = -PLAYER_MOVE_SPEED;
		g_PlayerData.isTurn = true;
	}
	// 右入力
	else if (IsInputKey(KEY_RIGHT))
	{
		g_PlayerData.moveX = PLAYER_MOVE_SPEED;
	g_PlayerData.isTurn = false;
	}

	// Z入力
	if (IsTriggerKey(KEY_Z))
	{
		g_PlayerData.moveY = -PLAYER_JUMP_POWER;
	}
}

void UpdatePlayer()
{
	// 死んでいたら処理しない
	if (!g_PlayerData.active) return;

	// 上昇しているもしくは落ちている場合は空中フラグを立てる
	if (g_PlayerData.moveY < 0.0f || g_PlayerData.moveY > PLAYER_GRAVITY)
	{
		g_PlayerData.isAir = true;
	}

	// 移動処理
	g_PlayerData.posX += g_PlayerData.moveX;
	g_PlayerData.posY += g_PlayerData.moveY;

	//UpdatePlayerAnimation();


	g_PlayerData.beforposX = g_PlayerData.posX;

	g_PlayerData.beforposY = g_PlayerData.posY;
	// 上入力
	if (IsInputKey(KEY_UP))
	{
		g_PlayerData.posY -= g_PlayerData.moveY;
	}
	// 下入力
	if (IsInputKey(KEY_DOWN))
	{
		g_PlayerData.posY += g_PlayerData.moveY;
	}
	// 左入力
	if (IsInputKey(KEY_LEFT))
	{
		g_PlayerData.posX -= g_PlayerData.moveX;
	}
	// 右入力
	if (IsInputKey(KEY_RIGHT))
	{
		g_PlayerData.posX += g_PlayerData.moveX;
	}
	//if (IsTriggerKey(KEY_Z))
	//{
	//	float fireX = g_PlayerData.posX + PLAYER_NORMAL_SHOT_OFFSET_X;
	//	float fireY = g_PlayerData.posY + PLAYER_NORMAL_SHOT_OFFSET_Y;

	//	RequestFireBullet(BULLET_LIFE, fireX, fireY, BULLET_SPEED, 0.0f, BULLET_RADIUS);

	//	//PlaySE(SE_PLAYER_SHOT);

	//	g_PlayerData.bulletIntervalTimer = PLAYER_NORMAL_SHOT_INTERVAL;
	//}

	if (g_PlayerData.posX >= 1750)
	{
		g_PlayerData.posX = 1750;

	}
	if (g_PlayerData.posX <= -70)
	{
		g_PlayerData.posX = -70;

	}
	if (g_PlayerData.posY <= -60)
	{
		g_PlayerData.posY = -60;

	}
	if (g_PlayerData.posY >= 930)
	{
		g_PlayerData.posY = 930;

	}
	// ヒットフラグは毎回折る（当たり判定後に当たっていたら立てる）
	g_PlayerData.hitFlag = false;
}

void DrawPlayer()
{
	// 死んでいたら処理しない
	if (!g_PlayerData.active) return;

	//カメラ取得
	CameraData camera = GetCamera();
	//// アニメーション描画でプレイヤーを描画する
	//PlayerAnimationType animType = g_PlayerData.playAnim;
	//AnimationData* animData = &g_PlayerData.animation[animType];
	//DrawAnimation(animData, g_PlayerData.posX - camera.pos.x, g_PlayerData.posY - camera.pos.y, g_PlayerData.isTurn);

	// 当たり判定を描画
	//float x, y, w, h;
	//CalcBoxCollision(g_PlayerData, x, y, w, h);
	//DrawBox((int)(x - camera.posX), (int)(y - camera.posY), (int)(x + w - camera.posX), (int)(y + h - camera.posY), GetColor(255, 255, 255), false);
}

void FinPlayer()
{
	/*for (int i = 0; i < PLAYER_ANIM_MAX; i++)
	{
		DeleteGraph(g_PlayerData.animation[i].handle);
	}*/
}

PlayerData GetPlayer()
{
	return PlayerData();
}

void PlayerHitNormalBlock(MapChipData mapChipData)
{
}
