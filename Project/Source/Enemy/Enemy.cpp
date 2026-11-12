#include "DxLib.h"
#include "Enemy.h"
#include "../Camera/Camera.h"
#include "../Input/Input.h"
#include "../Collision/Collision.h"
#include "../Map/MapManager.h"

#define ENEMY_DEFAULT_POS_X (600.0f)
#define ENEMY_DEFAULT_POS_Y (400.0f)
#define ENEMY_MOVE_SPEED (4.0f)

// ジャンプ力
#define ENEMY_JUMP_POWER (12.0f)
// 重力
#define ENEMY_GRAVITY (0.3f)

// マップ衝突判定用のプレイヤーサイズ補正
#define ENEMY_MAP_COLLISION_OFFSET (0.05f)
// 矩形判定の位置補正
#define ENEMY_BOX_COLLISION_OFFSET_X (24)
#define ENEMY_BOX_COLLISION_OFFSET_Y (20)
// 矩形判定のサイズ
#define ENEMY_BOX_COLLISION_WIDTH (25)
#define ENEMY_BOX_COLLISION_HEIGHT (50)

EnemyData g_EnemysData[ENEMY_NUM] = { 0 };

void CalcBoxCollision(EnemyData enemy, float& x, float& y, float& w, float& h);

//struct EnemyAnimationParam
//{
//	int interval;
//	int frameNum;
//	int width;
//	int height;
//};
//const EnemyAnimationParam ENEMY_ANIM_PARAM[ENEMY_ANIM_MAX] =
//{
//	8, 4, 100, 120,
//	5, 8, 100, 120,
//	8, 2, 100, 120,
//	8, 2, 100, 120,
//	8, 1, 100, 120,
//};


void InitEnemy()
{
	
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		g_EnemysData[i].posX= ENEMY_DEFAULT_POS_X;
		g_EnemysData[i].posY = ENEMY_DEFAULT_POS_Y;
		g_EnemysData[i].active = false;
		g_EnemysData[i].boxCollision.width = 25;
		g_EnemysData[i].boxCollision.height = 50;

		g_EnemysData[i].dir = -1;

		// testデータ
		g_EnemysData[i].posX = ENEMY_DEFAULT_POS_X - 30 + i * 40;
		g_EnemysData[i].posY = ENEMY_DEFAULT_POS_Y - 30 - i * 10;
		g_EnemysData[i].moveX = 0;
		g_EnemysData[i].moveY = 1;

		g_EnemysData[i].Life = 1;
	}



	
}

void LoadEnemy()
{

	
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		g_EnemysData[i].handle = LoadGraph("Data/Enemy/Enemy1.png");
	}
}

void StartEnemy()
{
	// 生存フラグを立てる
	

	for (int i = 0; i < ENEMY_NUM; i++)
	{
		g_EnemysData[i].active = true;
	}
}

void StepEnemy()
{
	// 死んでいたら何もしない
	

	// X移動量は毎回リセットする
	//g_EnemyData.moveX = 0.0f;

	// Y移動量に重力を反映
	//g_EnemyData.moveY += ENEMY_GRAVITY;




}

void UpdateEnemy()
{
	
	

	for (int i = 0; i < ENEMY_NUM; i++)
	{
		// 死んでいたら処理しない
		if (!g_EnemysData[i].active)continue;

		// 上昇しているもしくは落ちている場合は空中フラグを立てる
		if (g_EnemysData[i].moveY < 0.0f || g_EnemysData[i].moveY > ENEMY_GRAVITY)
		{
			g_EnemysData[i].isAir = true;
		}

		if (g_EnemysData[i].Life <= 0)
		{
			g_EnemysData[i].active = false;
		}

		g_EnemysData[i].moveY += ENEMY_GRAVITY;

		// 移動処理
		g_EnemysData[i].beforposX = g_EnemysData[i].posX;
		g_EnemysData[i].beforposY = g_EnemysData[i].posY;
		g_EnemysData[i].posX += g_EnemysData[i].moveX;
		g_EnemysData[i].posY += g_EnemysData[i].moveY;


		//UpdateEnemyAnimation();

		if (g_EnemysData[i].posX >= 1750)
		{
			g_EnemysData[i].posX = 1750;

		}
		if (g_EnemysData[i].posX <= -70)
		{
			g_EnemysData[i].posX = -70;

		}
		if (g_EnemysData[i].posY <= -60)
		{
			g_EnemysData[i].posY = -60;

		}
		if (g_EnemysData[i].posY >= 930)
		{
			g_EnemysData[i].posY = 930;

		}

		// プレイヤーとマップの当たり判定
		ChceckMapEnemyCollision();

		// ヒットフラグは毎回折る（当たり判定後に当たっていたら立てる）
		g_EnemysData[i].hitFlag = false;

		if (g_EnemysData[i].dir == 1)
		{
			g_EnemysData[i].moveX = 1;

		}
		else if (g_EnemysData[i].dir == -1)
		{
			g_EnemysData[i].moveX = -1;

		}
	}

	
}

void DrawEnemy()
{
	

	//カメラ取得
	CameraData camera = GetCamera();

	
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		// 死んでいたら処理しない
		if (!g_EnemysData[i].active) continue;

		//DrawGraph((int)g_EnemyData.posX, (int)g_EnemyData.posY, g_EnemyData.handle, TRUE);
		int Reverse = 0;

		if (g_EnemysData[i].dir == 1)
		{
			Reverse = 1;
		}
		if (g_EnemysData[i].dir == -1)
		{
			Reverse = 0;
		}
		DrawRectGraph((int)(g_EnemysData[i].posX - camera.pos.x), (int)(g_EnemysData[i].posY - camera.pos.y), 0, 0, 35, 50, g_EnemysData[i].handle, TRUE, Reverse, 0);
	}
}

void FinEnemy()
{

}


EnemyData* GetEnemy(int index)
{
	return &g_EnemysData[index];
}

void EnemyHitNormalBlockY(EnemyData* enemyData, MapChipData mapChipData)
{
	EnemyData tempEnemy = *enemyData;
	BlockData* block = mapChipData.data;
	const float POS_OFFSET = ENEMY_MAP_COLLISION_OFFSET;
	const float SIZE_OFFSET = ENEMY_MAP_COLLISION_OFFSET * 2;

	//// Y移動を戻し、横に当たっているかチェック
	tempEnemy.posX = enemyData->beforposX;
	tempEnemy.posY = enemyData->posY;

	// まだ当たっているなら縦に当たっている
	// 当たり判定のボックス計算
	float x, y, w, h;
	CalcBoxCollision(tempEnemy, x, y, w, h);

	if (CheckSquareSquare(x + POS_OFFSET, y + POS_OFFSET, w - SIZE_OFFSET, h - SIZE_OFFSET,
		block->pos.x, block->pos.y, MAP_CHIP_WIDTH, MAP_CHIP_HEIGHT))
	{
		// 上からあたったか
		if (tempEnemy.moveY > 0.0f)
		{
			// 上に押し出す
			enemyData->posY = tempEnemy.posY - ((y + h) - block->pos.y);
			enemyData->isAir = false;
			// Y移動量を0にする
			enemyData->moveY = 0.0f;

		}
		// 下からあたったか
		else if (tempEnemy.moveY < 0.0f)
		{
			// 下に押し出す
			enemyData->posY = tempEnemy.posY + ((block->pos.y + MAP_CHIP_WIDTH) - y);
			// Y移動量を0にする
			enemyData->moveY = 0.0f;
		}
	}
}

void EnemyHitNormalBlockX(EnemyData* enemyData, MapChipData mapChipData)
{
	EnemyData tempEnemy = *enemyData;
	BlockData* block = mapChipData.data;
	const float POS_OFFSET = ENEMY_MAP_COLLISION_OFFSET;
	const float SIZE_OFFSET = ENEMY_MAP_COLLISION_OFFSET * 2;

	// まだ当たっているなら縦に当たっている
	// 当たり判定のボックス計算
	float x, y, w, h;

	// 最新の座標で縦に当たっているかチェック
	tempEnemy.posX = enemyData->posX;
	tempEnemy.posY = enemyData->posY;

	// 当たり判定のボックス計算
	CalcBoxCollision(tempEnemy, x, y, w, h);

	if (CheckSquareSquare(x + POS_OFFSET, y + POS_OFFSET, w - SIZE_OFFSET, h - SIZE_OFFSET,
		block->pos.x, block->pos.y, MAP_CHIP_WIDTH, MAP_CHIP_HEIGHT))
	{
		// 左からあたったか
		if (tempEnemy.moveX > 0.0f)
		{
			// 左に押し出す
			enemyData->posX = tempEnemy.posX - ((x + w) - block->pos.x);
			enemyData->moveX = 0.0f;
			enemyData->dir = -1;
		}
		// 右からあたったか
		else if (tempEnemy.moveX < 0.0f)
		{
			// 右に押し出す
			enemyData->posX = tempEnemy.posX + ((block->pos.x + MAP_CHIP_WIDTH) - x);
			enemyData->moveX = 0.0f;
			enemyData->dir = 1;
			
		}
	}
}


void CalcBoxCollision(EnemyData enemy, float& x, float& y, float& w, float& h)
{
	x = enemy.isTurn ?
		enemy.posX + ENEMY_WIDTH - enemy.boxCollision.posX - enemy.boxCollision.width :
		enemy.posX + enemy.boxCollision.posX;
	y = enemy.posY + enemy.boxCollision.posY;
	w = enemy.boxCollision.width;
	h = enemy.boxCollision.height;
}
