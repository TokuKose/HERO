#include "DxLib.h"
#include "Player.h"
#include "../Camera/Camera.h"
#include "../Input/Input.h"
#include "../Collision/Collision.h"
#include "../Map/MapManager.h"

#define PLAYER_DEFAULT_POS_X (300.0f)
#define PLAYER_DEFAULT_POS_Y (200.0f)
#define PLAYER_MOVE_SPEED (4.0f)

// ジャンプ力
#define PLAYER_JUMP_POWER (12.0f)
// 重力
#define PLAYER_GRAVITY (0.3f)

// マップ衝突判定用のプレイヤーサイズ補正
#define PLAYER_MAP_COLLISION_OFFSET (0.05f)
// 矩形判定の位置補正
#define PLAYER_BOX_COLLISION_OFFSET_X (24)
#define PLAYER_BOX_COLLISION_OFFSET_Y (20)
// 矩形判定のサイズ
#define PLAYER_BOX_COLLISION_WIDTH (25)
#define PLAYER_BOX_COLLISION_HEIGHT (50)

PlayerData g_PlayerData = { 0 };
PlayerData g_PrevPlayerData = { 0 };

void CalcBoxCollision(PlayerData player, float& x, float& y, float& w, float& h);

struct PlayerAnimationParam
{
	int interval;
	int frameNum;
	int width;
	int height;
};
const PlayerAnimationParam PLAYER_ANIM_PARAM[PLAYER_ANIM_MAX] =
{
	8, 4, 100, 120,
	5, 8, 100, 120,
	8, 2, 100, 120,
	8, 2, 100, 120,
	8, 1, 100, 120,
};


void InitPlayer()
{
	g_PlayerData.posX = PLAYER_DEFAULT_POS_X;
	g_PlayerData.posY = PLAYER_DEFAULT_POS_Y;
	g_PlayerData.active = false;
	g_PlayerData.boxCollision.width = 25;
	g_PlayerData.boxCollision.height = 50;
	//g_PlayerData.moveX = PLAYER_MOVE_SPEED;
	//g_PlayerData.moveY = PLAYER_MOVE_SPEED;


	// testデータ
	g_PlayerData.posX = PLAYER_DEFAULT_POS_X-30;
	g_PlayerData.posY = PLAYER_DEFAULT_POS_Y-30;
	g_PlayerData.moveX = 0;
	g_PlayerData.moveY = 1;
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
	
	g_PlayerData.handle = LoadGraph("Data/Player/Player1.png");
	
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
	//g_PlayerData.moveX = 0.0f;

	// Y移動量に重力を反映
	g_PlayerData.moveY += PLAYER_GRAVITY;

	
}

void UpdatePlayer()
{
	// 上入力
	if (IsTriggerKey(KEY_UP))
	{
		g_PlayerData.moveY = -5;
	}
	// 下入力
	/*if (IsTriggerKey(KEY_DOWN))
	{
		g_PlayerData.moveY = 5;
	}*/
	// 左入力
	if (IsInputKey(KEY_LEFT))
	{
		g_PlayerData.moveX = -3;
	}
	// 右入力
	if (IsInputKey(KEY_RIGHT))
	{
		g_PlayerData.moveX = 3;
	}

	// 死んでいたら処理しない
	if (!g_PlayerData.active) return;

	// 上昇しているもしくは落ちている場合は空中フラグを立てる
	if (g_PlayerData.moveY < 0.0f || g_PlayerData.moveY > PLAYER_GRAVITY)
	{
		g_PlayerData.isAir = true;
	}


	g_PlayerData.moveY += PLAYER_GRAVITY;

	// 移動処理
	
	g_PlayerData.posX += g_PlayerData.moveX;
	g_PlayerData.posY += g_PlayerData.moveY;

	
	//UpdatePlayerAnimation();
	

	g_PlayerData.beforposX = g_PlayerData.posX;

	g_PlayerData.beforposY = g_PlayerData.posY;

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
	
		// プレイヤーとマップの当たり判定
		ChceckMapPlayerCollision();
	
	// ヒットフラグは毎回折る（当たり判定後に当たっていたら立てる）
	g_PlayerData.hitFlag = false;


	g_PlayerData.moveX = 0;
	
}

void DrawPlayer()
{
	// 死んでいたら処理しない
	if (!g_PlayerData.active) return;

	//カメラ取得
	CameraData camera = GetCamera();

	DrawGraph((int)g_PlayerData.posX, (int)g_PlayerData.posY, g_PlayerData.handle, TRUE);
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

PlayerData* GetPlayer()
{
	return &g_PlayerData;
}

void PlayerHitNormalBlock(MapChipData mapChipData)
{
	PlayerData player = g_PlayerData;
	BlockData* block = mapChipData.data;
	const float POS_OFFSET = PLAYER_MAP_COLLISION_OFFSET;
	const float SIZE_OFFSET = PLAYER_MAP_COLLISION_OFFSET * 2;

	// ターンフラグは前回のものにしないと反転した分ずれる
	player.isTurn = g_PrevPlayerData.isTurn;

	//// Y移動を戻し、横に当たっているかチェック
	//player.posX = g_PlayerData.posX;
	//player.posY = g_PrevPlayerData.posY;

	// まだ当たっているなら縦に当たっている
	// 当たり判定のボックス計算
	float x, y, w, h;
	CalcBoxCollision(player, x, y, w, h);

	if (CheckSquareSquare(x + POS_OFFSET, y + POS_OFFSET, w - SIZE_OFFSET, h - SIZE_OFFSET,
		block->pos.x, block->pos.y, MAP_CHIP_WIDTH, MAP_CHIP_HEIGHT))
	{
		// Y移動量を0にする
		g_PlayerData.moveY = 0.0f;

		// 上からあたったか
		if (player.moveY > 0.0f)
		{
			// 上に押し出す
			g_PlayerData.posY -= (y + h) - block->pos.y;
			g_PlayerData.isAir = false;
			g_PlayerData.moveY = 0.0f;
		}
		// 下からあたったか
		else if (player.moveY < 0.0f)
		{
			// 下に押し出す
			g_PlayerData.posY += (block->pos.y + MAP_CHIP_WIDTH) - y;
			g_PlayerData.moveY = 0.0f;
		}
	}

	// 最新の座標で縦に当たっているかチェック
	player.posX = g_PlayerData.posX;
	player.posY = g_PlayerData.posY;

	// 当たり判定のボックス計算
	CalcBoxCollision(player, x, y, w, h);

	if (CheckSquareSquare(x + POS_OFFSET, y + POS_OFFSET, w - SIZE_OFFSET, h - SIZE_OFFSET,
		block->pos.x, block->pos.y, MAP_CHIP_WIDTH, MAP_CHIP_HEIGHT))
	{
		// 左からあたったか
		if (player.moveX > 0.0f)
		{
			// 左に押し出す
			g_PlayerData.posX -= (x + w) - block->pos.x;
			g_PlayerData.moveX = 0.0f;
		}
		// 右からあたったか
		else if (player.moveX < 0.0f)
		{
			// 右に押し出す
			g_PlayerData.posX += (block->pos.x + MAP_CHIP_WIDTH) - x;
			g_PlayerData.moveX = 0.0f;
		}
	}
	

	/*
	// 最新の座標で縦に当たっているかチェック
	player.posX = g_PlayerData.posX;
	player.posY = g_PlayerData.posY;

	// 当たり判定のボックス計算
	CalcBoxCollision(player, x, y, w, h);

	// まだ当たっているなら縦に当たっている
	if (CheckSquareSquare(x + POS_OFFSET, y + POS_OFFSET, w - SIZE_OFFSET, h - SIZE_OFFSET,
		block->pos.x, block->pos.y, MAP_CHIP_WIDTH, MAP_CHIP_HEIGHT))
	{
		// Y移動量を0にする
		g_PlayerData.moveY = 0.0f;

		// 上からあたったか
		if (player.moveY > 0.0f)
		{
			// 上に押し出す
			g_PlayerData.posY -= (y + h) - block->pos.y;
			g_PlayerData.isAir = false;
		}
		// 下からあたったか
		else if (player.moveY < 0.0f)
		{
			// 下に押し出す
			g_PlayerData.posY += (block->pos.y + MAP_CHIP_WIDTH) - y;
		}
	}
	*/
}

void CalcBoxCollision(PlayerData player, float& x, float& y, float& w, float& h)
{
	x = player.isTurn ?
		player.posX + PLAYER_WIDTH - player.boxCollision.posX - player.boxCollision.width :
		player.posX + player.boxCollision.posX;
	y = player.posY + player.boxCollision.posY;
	w = player.boxCollision.width;
	h = player.boxCollision.height;
}
