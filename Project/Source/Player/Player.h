#pragma once
#include "../Map/MapParameter.h"


// プレイヤーサイズ
#define PLAYER_WIDTH	(25.0f)
#define PLAYER_HEIGHT	(50.0f)
#define PLAYER_RADIUS	(36.0f)



struct PlayerData
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
	//BoxCollision boxCollision;					// 矩形当たり判定
};


void InitPlayer();
void LoadPlayer();
void StartPlayer();
void StepPlayer();
void UpdatePlayer();
void DrawPlayer();
void FinPlayer();

// 取得関数
PlayerData GetPlayer();

// 当たり判定
void PlayerHitNormalBlock(MapChipData mapChipData);
