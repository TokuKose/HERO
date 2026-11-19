#include "DxLib.h"
#include "Bullet.h"
#include "../Enemy/Enemy.h"
#include "../PlayerAttack/PlayerAttack.h"
#include "../Player/Player.h"

#define HIT_EFFECT_INTERVAL (1)
#define HIT_EFFECT_OFFSET_X (-10.0f)
#define HIT_EFFECT_OFFSET_Y (-10.0f)

BulletData g_BulletData[BULLET_MAX] = { 0 };


// 各弾丸の画像ハンドル
int g_BulletHandle = 0;

void InitBullet()
{
	// 処理高速化のためポインタを使う
	BulletData* bullet = g_BulletData;
	for (int i = 0; i < BULLET_MAX; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			bullet->handle[j] = 0;
		}
		
		bullet->life = 0;
		bullet->posX = 0.0f;
		bullet->posY = 0.0f;
		bullet->moveX = 0.0f;
		bullet->moveY = 0.0f;
		bullet->active = false;
	}
}

void LoadBullet()
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		g_BulletData[i].handle[CHANGE_ARCHERBULLET] = LoadGraph("Data/Player/Arrow.png");
	}
}

void StepBullet()
{

}

void UpdateBullet()
{

}

void DrawBullet()
{
	// 処理高速化のためポインタを使う
	BulletData* bullet = g_BulletData;
	for (int i = 0; i < BULLET_MAX; i++, bullet++)
	{
		// 生きている弾だけ描画する
		if (!bullet->active) continue;

		for (int j = 0; j < 2; j++)
		{
			DrawGraph((int)bullet->posX, (int)bullet->posY, bullet->handle[j], TRUE);
		}

		
	}
}

void FinBullet()
{
	DeleteGraph(g_BulletHandle);
}


BulletData* GetBullet()
{
	return g_BulletData;
}

void BulletHitEnemy(int index)
{
	BulletData* bullet = &g_BulletData[index];

	// 衝突したら死亡
	bullet->active = false;

	// エフェクトを表示
	float effectPosX = bullet->posX;
	float effectPosY = bullet->posY;

}

void BulletHitPlayer(int index)
{
	BulletData* bullet = &g_BulletData[index];

	// 衝突したら死亡
	bullet->active = false;

	// エフェクトを表示
	float effectPosX = bullet->posX;
	float effectPosY = bullet->posY;
	
}
