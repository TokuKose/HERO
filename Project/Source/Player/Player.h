#pragma once
#include "../Map/MapParameter.h"
#include "../Collision/Collision.h"

// プレイヤーサイズ
#define PLAYER_WIDTH	(30.0f)
#define PLAYER_HEIGHT	(50.0f)
#define PLAYER_RADIUS	(36.0f)

enum Change
{
	CHANGE_SEIVER,
    CHANGE_RANCER,
	CHANGE_ARCHER,
	CHANGE_CASTER,
	CHANGE_MAX
};
struct PlayerData
{
	int handle[CHANGE_MAX];
	
	bool active;								// 生存フラグ
	bool isTurn;								// 左を向いているか
	bool isAir;									// 空中にいるか
	int flash;                                  // 点滅
	float posX;									// X座標
	float posY;									// Y座標
	float moveX;								// X移動量
	float moveY;								// Y移動量
	float beforposX;
	float beforposY;
	int hitFlag;
	int dir;
	int Life;
	int interval;
	Change change;
	Body body;
	BoxCollision boxCollision;					// 矩形当たり判定
};


void InitPlayer();
void LoadPlayer();
void StartPlayer();
void StepPlayer();
void UpdatePlayer();
void DrawPlayer();
void FinPlayer();

// 取得関数
PlayerData* GetPlayer();

// 当たり判定
void PlayerHitNormalBlockX(MapChipData mapChipData);
void PlayerHitNormalBlockY(MapChipData mapChipData);

void PlayerHitEnemy();
