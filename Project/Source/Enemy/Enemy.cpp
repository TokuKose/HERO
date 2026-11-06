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

EnemyData g_EnemyData = { 0 };
EnemyData g_PrevEnemyData = { 0 };

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
	g_EnemyData.posX = ENEMY_DEFAULT_POS_X;
	g_EnemyData.posY = ENEMY_DEFAULT_POS_Y;
	g_EnemyData.active = false;
	g_EnemyData.boxCollision.width = 25;
	g_EnemyData.boxCollision.height = 50;
	//g_EnemyData.moveX = ENEMY_MOVE_SPEED;
	//g_EnemyData.moveY = ENEMY_MOVE_SPEED;
	g_EnemyData.dir = -1;

	// testデータ
	g_EnemyData.posX = ENEMY_DEFAULT_POS_X - 30;
	g_EnemyData.posY = ENEMY_DEFAULT_POS_Y - 30;
	g_EnemyData.moveX = 0;
	g_EnemyData.moveY = 1;
	//g_EnemyData.playAnim = ENEMY_ANIM_NONE;

	//for (int i = 0; i < ENEMY_ANIM_MAX; i++)
	//{
		//InitAnimation(&g_EnemyData.animation[i]);
	//}

	// 構造体はmemsetで0初期化できる
	//memset(&g_EnemyData.boxCollision, 0, sizeof(g_EnemyData.boxCollision));
}

void LoadEnemy()
{

	g_EnemyData.handle = LoadGraph("Data/Enemy/Enemy1.png");
	/*if(IsInputKey(KEY_LEFT))
	{
		g_EnemyData.handle = LoadGraph("Data/Enemy/Enemy1B.png");
	}*/

}

void StartEnemy()
{
	// 生存フラグを立てる
	g_EnemyData.active = true;

	// 矩形判定設定
	/*g_EnemyData.boxCollision.posX = ENEMY_BOX_COLLISION_OFFSET_X;
	g_EnemyData.boxCollision.posY = ENEMY_BOX_COLLISION_OFFSET_Y;
	g_EnemyData.boxCollision.width = ENEMY_BOX_COLLISION_WIDTH;
	g_EnemyData.boxCollision.height = ENEMY_BOX_COLLISION_HEIGHT;*/

	// 待機アニメーションから開始する
	//StartEnemyAnimation(ENEMY_ANIM_IDLE);
}

void StepEnemy()
{
	// 死んでいたら何もしない
	if (!g_EnemyData.active)
	{
		return;
	}

	// 前回のデータとして記憶	
	g_PrevEnemyData = g_EnemyData;

	// X移動量は毎回リセットする
	//g_EnemyData.moveX = 0.0f;

	// Y移動量に重力を反映
	g_EnemyData.moveY += ENEMY_GRAVITY;


}

void UpdateEnemy()
{
	
	// 死んでいたら処理しない
	if (!g_EnemyData.active) return;

	// 上昇しているもしくは落ちている場合は空中フラグを立てる
	if (g_EnemyData.moveY < 0.0f || g_EnemyData.moveY > ENEMY_GRAVITY)
	{
		g_EnemyData.isAir = true;
	}


	g_EnemyData.moveY += ENEMY_GRAVITY;

	// 移動処理
	g_EnemyData.beforposX = g_EnemyData.posX;
	g_EnemyData.beforposY = g_EnemyData.posY;
	g_EnemyData.posX += g_EnemyData.moveX;
	g_EnemyData.posY += g_EnemyData.moveY;


	//UpdateEnemyAnimation();

	if (g_EnemyData.posX >= 1750)
	{
		g_EnemyData.posX = 1750;

	}
	if (g_EnemyData.posX <= -70)
	{
		g_EnemyData.posX = -70;

	}
	if (g_EnemyData.posY <= -60)
	{
		g_EnemyData.posY = -60;

	}
	if (g_EnemyData.posY >= 930)
	{
		g_EnemyData.posY = 930;

	}

	// プレイヤーとマップの当たり判定
	ChceckMapEnemyCollision();

	// ヒットフラグは毎回折る（当たり判定後に当たっていたら立てる）
	g_EnemyData.hitFlag = false;

	if (g_EnemyData.dir == 1)
	{
		g_EnemyData.moveX=1;
		
	}
	else if(g_EnemyData.dir == -1)
	{
		g_EnemyData.moveX=-1;
		
	}
	//g_EnemyData.moveX = -1;



	
}

void DrawEnemy()
{
	// 死んでいたら処理しない
	if (!g_EnemyData.active) return;

	//カメラ取得
	CameraData camera = GetCamera();

	//DrawGraph((int)g_EnemyData.posX, (int)g_EnemyData.posY, g_EnemyData.handle, TRUE);
	int Reverse=0;

	if (g_EnemyData.dir == 1)
	{
		Reverse = 1;
	}
	if (g_EnemyData.dir == -1)
	{
		Reverse = 0;
	}
	DrawRectGraph((int)g_EnemyData.posX - camera.pos.x, (int)g_EnemyData.posY - camera.pos.y, 0, 0, 35, 50, g_EnemyData.handle, TRUE, Reverse, 0);
	
}

void FinEnemy()
{
	/*for (int i = 0; i < ENEMY_ANIM_MAX; i++)
	{
		DeleteGraph(g_EnemyData.animation[i].handle);
	}*/
}

EnemyData* GetEnemy()
{
	return &g_EnemyData;
}

void EnemyHitNormalBlockY(MapChipData mapChipData)
{
	EnemyData tempEnemy = g_EnemyData;
	BlockData* block = mapChipData.data;
	const float POS_OFFSET = ENEMY_MAP_COLLISION_OFFSET;
	const float SIZE_OFFSET = ENEMY_MAP_COLLISION_OFFSET * 2;

	//// Y移動を戻し、横に当たっているかチェック
	tempEnemy.posX = g_EnemyData.beforposX;
	tempEnemy.posY = g_EnemyData.posY;

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
			g_EnemyData.posY = tempEnemy.posY - ((y + h) - block->pos.y);
			g_EnemyData.isAir = false;
			// Y移動量を0にする
			g_EnemyData.moveY = 0.0f;

		}
		// 下からあたったか
		else if (tempEnemy.moveY < 0.0f)
		{
			// 下に押し出す
			g_EnemyData.posY = tempEnemy.posY + ((block->pos.y + MAP_CHIP_WIDTH) - y);
			// Y移動量を0にする
			g_EnemyData.moveY = 0.0f;
		}
	}
}

void EnemyHitEnemy()
{

}

void EnemyHitNormalBlockX(MapChipData mapChipData)
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
			g_EnemyData.dir = -1;
		}
		// 右からあたったか
		else if (tempEnemy.moveX < 0.0f)
		{
			// 右に押し出す
			g_EnemyData.posX = tempEnemy.posX + ((block->pos.x + MAP_CHIP_WIDTH) - x);
			g_EnemyData.moveX = 0.0f;
			g_EnemyData.dir = 1;
			
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
