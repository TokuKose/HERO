#pragma once
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
};

// 各ロジックごとの関数
void InitBullet();
void LoadBullet();
void StepBullet();
void UpdateBullet();
void DrawBullet();
void FinBullet();

// 発射関数


// 弾取得
BulletData* GetBullet();

// 当たり判定関連
void BulletHitEnemy(int index);
void BulletHitPlayer(int index);
