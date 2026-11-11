#include "DxLib.h"
#include "Player.h"
#include "../Camera/Camera.h"
#include "../Input/Input.h"
#include "../Collision/Collision.h"
#include "../Map/MapManager.h"
#include "../Enemy/Enemy.h"
#include "../PlayerAttack/PlayerAttack.h"

#define FPS (60)

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

PlayerAttackData* PlayerAttack = GetPlayerAttack();

void InitPlayer()
{
	g_PlayerData.posX = PLAYER_DEFAULT_POS_X;
	g_PlayerData.posY = PLAYER_DEFAULT_POS_Y;
	g_PlayerData.active = false;
	g_PlayerData.boxCollision.width = 25;
	g_PlayerData.boxCollision.height = 50;

	g_PlayerData.dir = 1;


	// testデータ
	g_PlayerData.posX = PLAYER_DEFAULT_POS_X - 30;
	g_PlayerData.posY = PLAYER_DEFAULT_POS_Y - 30;
	g_PlayerData.moveX = 0;
	g_PlayerData.moveY = 1;

}

void LoadPlayer()
{

	g_PlayerData.handle = LoadGraph("Data/Player/Player1.png");


}

void StartPlayer()
{
	// 生存フラグを立てる
	g_PlayerData.active = true;


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

	// 左入力
	if (IsInputKey(KEY_LEFT))
	{
		g_PlayerData.moveX = -3;
		g_PlayerData.dir = 1;

	}
	// 右入力
	if (IsInputKey(KEY_RIGHT))
	{
		g_PlayerData.moveX = 3;
		g_PlayerData.dir = -1;

	}
	if (IsTriggerKey(KEY_Z))
	{
		

		if (g_PlayerData.dir == 1)
		{
			FirePlayerAttack(g_PlayerData.posX - 100, g_PlayerData.posY - 30, true);
			
		}
		else
		{
			FirePlayerAttack(g_PlayerData.posX +10, g_PlayerData.posY-30,false);
		}
		

		
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
	g_PlayerData.beforposX = g_PlayerData.posX;
	g_PlayerData.beforposY = g_PlayerData.posY;
	g_PlayerData.posX += g_PlayerData.moveX;
	g_PlayerData.posY += g_PlayerData.moveY;



	/*if (g_PlayerData.posX >= 1750)
	{
		g_PlayerData.posX = 1750;

	}
	if (g_PlayerData.posX <= -70)
	{
		g_PlayerData.posX = -70;

	}*/
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

int test = 0;
void DrawPlayer()
{
	
	// 死んでいたら処理しない
	if (!g_PlayerData.active) return;

	//カメラ取得
	CameraData camera = GetCamera();
	
	//DrawGraph((int)g_PlayerData.posX, (int)g_PlayerData.posY, g_PlayerData.handle, TRUE);
	int Reverse = 0;
	if (g_PlayerData.dir == 1)
	{
		Reverse = 1;
	}
	if (g_PlayerData.dir == -1)
	{
		Reverse = 0;
	}

	if (g_PlayerData.flash-- > 0)
	{
		if (test++ %  10 > 3)
		{
			DrawRectGraph((int)(g_PlayerData.posX - camera.pos.x), (int)(g_PlayerData.posY - camera.pos.y), 0, 0, 35, 50, g_PlayerData.handle, TRUE, Reverse, 0);
		}
	}
	else
	{
		DrawRectGraph((int)(g_PlayerData.posX - camera.pos.x), (int)(g_PlayerData.posY - camera.pos.y), 0, 0, 35, 50, g_PlayerData.handle, TRUE, Reverse, 0);
	}
	
}

void FinPlayer()
{

}

PlayerData* GetPlayer()
{
	return &g_PlayerData;
}


void PlayerHitEnemy()
{
	PlayerData tempPlayer = g_PlayerData;
	EnemyData* Enemy = GetEnemy();
	const float POS_OFFSET = PLAYER_MAP_COLLISION_OFFSET;
	const float SIZE_OFFSET = PLAYER_MAP_COLLISION_OFFSET * 2;
	if (Enemy->active == false)
	{
		return;
	}
	// まだ当たっているなら縦に当たっている
	// 当たり判定のボックス計算
	float x, y, w, h;
	CalcBoxCollision(tempPlayer, x, y, w, h);

	if (CheckSquareSquare(x + POS_OFFSET, y + POS_OFFSET, w - SIZE_OFFSET, h - SIZE_OFFSET,
		Enemy->posX, Enemy->posY, ENEMY_WIDTH, ENEMY_HEIGHT))
	{
		// 上からあたったか
		if (tempPlayer.moveY > 0.0f)
		{
			g_PlayerData.flash = 3 * FPS;
			
		}
		// 下からあたったか
		else
		{
			g_PlayerData.flash = 3 * FPS;
			
		}
	}
}

void PlayerHitNormalBlockY(MapChipData mapChipData)
{
	PlayerData tempPlayer = g_PlayerData;
	BlockData* block = mapChipData.data;
	const float POS_OFFSET = PLAYER_MAP_COLLISION_OFFSET;
	const float SIZE_OFFSET = PLAYER_MAP_COLLISION_OFFSET * 2;

	//// Y移動を戻し、横に当たっているかチェック
	tempPlayer.posX = g_PlayerData.beforposX;
	tempPlayer.posY = g_PlayerData.posY;

	// まだ当たっているなら縦に当たっている
	// 当たり判定のボックス計算
	float x, y, w, h;
	CalcBoxCollision(tempPlayer, x, y, w, h);

	if (CheckSquareSquare(x + POS_OFFSET, y + POS_OFFSET, w - SIZE_OFFSET, h - SIZE_OFFSET,
		block->pos.x, block->pos.y, MAP_CHIP_WIDTH, MAP_CHIP_HEIGHT))
	{
		// 上からあたったか
		if (tempPlayer.moveY > 0.0f)
		{
			// 上に押し出す
			g_PlayerData.posY = tempPlayer.posY - ((y + h) - block->pos.y);
			g_PlayerData.isAir = false;
			// Y移動量を0にする
			g_PlayerData.moveY = 0.0f;

		}
		// 下からあたったか
		else if (tempPlayer.moveY < 0.0f)
		{
			// 下に押し出す
			g_PlayerData.posY = tempPlayer.posY + ((block->pos.y + MAP_CHIP_WIDTH) - y);
			// Y移動量を0にする
			g_PlayerData.moveY = 0.0f;
		}
	}
}



void PlayerHitNormalBlockX(MapChipData mapChipData)
{
	PlayerData tempPlayer = g_PlayerData;
	BlockData* block = mapChipData.data;
	const float POS_OFFSET = PLAYER_MAP_COLLISION_OFFSET;
	const float SIZE_OFFSET = PLAYER_MAP_COLLISION_OFFSET * 2;

	// まだ当たっているなら縦に当たっている
	// 当たり判定のボックス計算
	float x, y, w, h;

	// 最新の座標で縦に当たっているかチェック
	tempPlayer.posX = g_PlayerData.posX;
	tempPlayer.posY = g_PlayerData.posY;

	// 当たり判定のボックス計算
	CalcBoxCollision(tempPlayer, x, y, w, h);

	if (CheckSquareSquare(x + POS_OFFSET, y + POS_OFFSET, w - SIZE_OFFSET, h - SIZE_OFFSET,
		block->pos.x, block->pos.y, MAP_CHIP_WIDTH, MAP_CHIP_HEIGHT))
	{
		// 左からあたったか
		if (tempPlayer.moveX > 0.0f)
		{
			// 左に押し出す
			g_PlayerData.posX = tempPlayer.posX - ((x + w) - block->pos.x);
			g_PlayerData.moveX = 0.0f;
		}
		// 右からあたったか
		else if (tempPlayer.moveX < 0.0f)
		{
			// 右に押し出す
			g_PlayerData.posX = tempPlayer.posX + ((block->pos.x + MAP_CHIP_WIDTH) - x);
			g_PlayerData.moveX = 0.0f;
		}
	}
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
