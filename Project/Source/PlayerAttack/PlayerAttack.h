#pragma once
#include "../Map/MapParameter.h"
#include "../Collision/Collision.h"

// プレイヤーサイズ
#define PLAYERATTACK_WIDTH	(30.0f)
#define PLAYERATTACK_HEIGHT	(50.0f)
#define PLAYERATTACK_RADIUS	(36.0f)


enum ChangeAttack
{
	CHANGE_SEIVERATTACK,
	CHANGE_RANCERATTACK,
	CHANGE_ARCHERATTACK,
	CHANGE_CASTERATTACK,
	CHANGE_MAXATTACK
};


struct PlayerAttackData
{
	int useHandle; // 描画時に使うハンドル
	int handle[CHANGE_MAXATTACK];
	bool active;								// 生存フラグ
	bool isTurn;								// 左を向いているか
	bool isAir;									// 空中にいるか
	float posX;									// X座標
	float posY;									// Y座標
	float moveX;								// X移動量
	float moveY;								// Y移動量
	float beforposX;
	float beforposY;
	float width;
	float height;
	int Timer;
	int hitFlag;
	int dir;
	ChangeAttack change;
	BoxCollision boxCollision;					// 矩形当たり判定
};


void InitPlayerAttack();
void LoadPlayerAttack();
void StartPlayerAttack();
void StepPlayerAttack();
void UpdatePlayerAttack();
void DrawPlayerAttack();
void FinPlayerAttack();

// 取得関数
PlayerAttackData* GetPlayerAttack();

// プレイヤーの攻撃を発生させる
void FirePlayerAttack(float posX, float posY, bool turn);


void PlayerAttackHitEnemy();
void SetChangeAttack(ChangeAttack changeAttack);
