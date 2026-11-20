#pragma once
#include "../Collision/Collision.h"
#define BULLET_MAX (128)
enum ChangeBullet
{
	CHANGE_ARCHERBULLET
};
// 弾のデータ
struct BulletData
{
	bool active;
	int handle[2];
	int life;
	float posX;
	float posY;
	float moveX;
	float moveY;
	float radius;
	int width;
	int height;
	int dir;
	BoxCollision boxCollision;
};

// 各ロジックごとの関数
void InitBullet();
void LoadBullet();
void StepBullet();
void UpdateBullet();
void DrawBullet();
void FinBullet();

// 発射関数
void FirePlayerBullet(float posX, float posY, int dir);

// 弾取得
BulletData* GetBullet();

// 当たり判定関連
void BulletHitEnemy(int index);
void BulletHitPlayer(int index);
