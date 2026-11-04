#pragma once
#include "../Map/MapParameter.h"
#include "../Collision/Collision.h"

// プレイヤーサイズ
#define ENEMY_WIDTH	(40.0f)
#define ENEMY_HEIGHT	(50.0f)
#define ENEMY_RADIUS	(36.0f)



struct EnemyData
{
	int handle;
	bool active;								// 生存フラグ
	bool isTurn;								// 左を向いているか
	bool isAir;									// 空中にいるか
	float posX;									// X座標
	float posY;									// Y座標
	float moveX;								// X移動量
	float moveY;								// Y移動量
	float beforposX;
	float beforposY;
	int hitFlag;
	BoxCollision boxCollision;					// 矩形当たり判定
};


void InitEnemy();
void LoadEnemy();
void StartEnemy();
void StepEnemy();
void UpdateEnemy();
void DrawEnemy();
void FinEnemy();

// 取得関数
EnemyData* GetEnemy();

// 当たり判定
void PlayerHitNormalBlock(MapChipData mapChipData);
