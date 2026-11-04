#include "Enemy.h"
#include "DxLib.h"
#include "../Collision/Collision.h"
#include "../Map/MapManager.h"

#define ENEMY_DEFAULT_POS_X (500.0f)
#define ENEMY_DEFAULT_POS_Y (200.0f)
#define ENEMY_MOVE_SPEED (4.0f)

#define ENEMY_MAP_COLLISION_OFFSET (0.05f)

#define ENEMY_GRAVITY (0.3f)
// マップ衝突判定用のプレイヤーサイズ補正
#define ENEMY_MAP_COLLISION_OFFSET (0.05f)
// 矩形判定の位置補正
#define ENEMY_BOX_COLLISION_OFFSET_X (24)
#define ENEMY_BOX_COLLISION_OFFSET_Y (20)
// 矩形判定のサイズ
#define ENEMY_BOX_COLLISION_WIDTH (25)
#define ENEMY_BOX_COLLISION_HEIGHT (50)

EnemyData g_EnemyData = { 0 };


void CalcBoxCollision(EnemyData enemy, float& x, float& y, float& w, float& h);


void InitEnemy()
{
	g_EnemyData.posX = ENEMY_DEFAULT_POS_X;
	g_EnemyData.posY = ENEMY_DEFAULT_POS_Y;
	g_EnemyData.active = false;
	g_EnemyData.boxCollision.width = 25;
	g_EnemyData.boxCollision.height = 50;
}

void LoadEnemy()
{
	g_EnemyData.handle = LoadGraph("Data/Enemy/Enemy1.png");
}

void StartEnemy()
{

	g_EnemyData.active = true;
}

void StepEnemy()
{
}

void UpdateEnemy()
{
}

void DrawEnemy()
{
}

void FinEnemy()
{
}

EnemyData* GetEnemy()
{
	return nullptr;
}

void EnemyHitNormalBlock(MapChipData mapChipData)
{
	EnemyData tempEnemy = g_EnemyData;
	BlockData* block = mapChipData.data;
	const float POS_OFFSET = ENEMY_MAP_COLLISION_OFFSET;
	const float SIZE_OFFSET = ENEMY_MAP_COLLISION_OFFSET * 2;

	// まだ当たっているなら縦に当たっている
	// 当たり判定のボックス計算
	float x, y, w, h;

	// 最新の座標で縦に当たっているかチェック
	tempEnemy.posX = g_EnemyData.posX;
	tempEnemy.posY = g_EnemyData.posY;

	// 当たり判定のボックス計算
	CalcBoxCollision(tempEnemy, x, y, w, h);

	if (CheckSquareSquare(x + POS_OFFSET, y + POS_OFFSET, w - SIZE_OFFSET, h - SIZE_OFFSET,
		block->pos.x, block->pos.y, MAP_CHIP_WIDTH, MAP_CHIP_HEIGHT))
	{
		// 左からあたったか
		if (tempEnemy.moveX > 0.0f)
		{
			// 左に押し出す
			g_EnemyData.posX = tempEnemy.posX - ((x + w) - block->pos.x);
			g_EnemyData.moveX = 0.0f;
		}
		// 右からあたったか
		else if (tempEnemy.moveX < 0.0f)
		{
			// 右に押し出す
			g_EnemyData.posX = tempEnemy.posX + ((block->pos.x + MAP_CHIP_WIDTH) - x);
			g_EnemyData.moveX = 0.0f;
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
