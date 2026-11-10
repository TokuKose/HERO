#pragma once
#include "../Map/MapParameter.h"
#include "../Collision/Collision.h"

struct PlayerAttackData
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
	int dir;
	BoxCollision boxCollision;					// 矩形当たり判定
};


void InitPlayerAttack();
void LoadPlayerAttack();
void StartPlayerAttack();
void StepPlayerAttack();
void UpdatePlayerAttack();
void DrawPlayerAttack();
void FinPlayerAttack();
