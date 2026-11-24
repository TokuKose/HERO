#include "DxLib.h"
#include "Bullet.h"
#include "../Enemy/Enemy.h"
#include "../PlayerAttack/PlayerAttack.h"
#include "../Player/Player.h"
#include "../Camera/Camera.h"

#define HIT_EFFECT_INTERVAL (1)
#define HIT_EFFECT_OFFSET_X (-10.0f)
#define HIT_EFFECT_OFFSET_Y (-10.0f)


#define BULLETATTACK_MAP_COLLISION_OFFSET (0.05f)

BulletData g_BulletData[BULLET_MAX] = { 0 };

int arrowHandle;
int magicHandle;


void CalcBulletBoxCollision(BulletData* bullet, float& x, float& y, float& w, float& h);

// 各弾丸の画像ハンドル
int g_BulletHandle = 0;

void InitBullet()
{
	// 処理高速化のためポインタを使う
	BulletData* bullet = g_BulletData;
	for (int i = 0; i < BULLET_MAX; i++, bullet++)
	{
		bullet->life = 0;
		bullet->posX = 0.0f;
		bullet->posY = 0.0f;
		bullet->moveX = 0.0f;
		bullet->moveY = 0.0f;
		bullet->active = false;
		bullet->width = 60;
		bullet->height = 20;
	}
}

void LoadBullet()
{
	arrowHandle = LoadGraph("Data/Player/Arrow.png");
	magicHandle = LoadGraph("Data/Player/Magic.png");
}

void StepBullet()
{

}


void MoveBullet()
{
	// 処理高速化のためポインタを使う
	BulletData* bullet = g_BulletData;
	for (int i = 0; i < BULLET_MAX; i++, bullet++)
	{
		// 生きている弾だけ描画する
		if (!bullet->active) continue;

		bullet->posX -= bullet->dir * 10;
	}
}

void UpdateBullet()
{
	MoveBullet();

	// 処理高速化のためポインタを使う
	BulletData* bullet = g_BulletData;
	for (int i = 0; i < BULLET_MAX; i++, bullet++)
	{
		// 生きている弾だけ描画する
		if (!bullet->active) continue;

		for (int j = 0; j < ENEMY_NUM; j++)
		{
			EnemyData* Enemy = GetEnemy(j);
			const float POS_OFFSET = BULLETATTACK_MAP_COLLISION_OFFSET;
			const float SIZE_OFFSET = BULLETATTACK_MAP_COLLISION_OFFSET * 2;

			if (Enemy->active==false)
			{
				continue; 
			}

			// まだ当たっているなら縦に当たっている
			// 当たり判定のボックス計算
			float x, y, w, h;
			CalcBulletBoxCollision(bullet, x, y, w, h);

			if (CheckSquareSquare(x + POS_OFFSET, y + POS_OFFSET, w - SIZE_OFFSET, h - SIZE_OFFSET,
				Enemy->posX, Enemy->posY, ENEMY_WIDTH, ENEMY_HEIGHT))
			{
			
					Enemy->Life = Enemy->Life - 1;
					bullet->active = false;
			}
		}

	}
}

void DrawBullet()
{
	// 処理高速化のためポインタを使う
	BulletData* bullet = g_BulletData;
	//カメラ取得
	CameraData camera = GetCamera();
	int Reverse = 0;
	for (int i = 0; i < BULLET_MAX; i++, bullet++)
	{
		// 生きている弾だけ描画する
		if (!bullet->active) continue;

		if (bullet->dir == -1)
		{
			Reverse = 0;
		}
		if (bullet->dir == 1)
		{
			Reverse = 1;
		}

		//int arrowHandle;
		//int magicHandle;
		int Change;
		if (Change == 1)
		{
			arrowHandle;
		}
		else if (Change == 2)
		{
			magicHandle;
		}



		DrawRectGraph((int)(bullet->posX - camera.pos.x), (int)(bullet->posY - camera.pos.y), 0, 0, bullet->width, bullet->height, Change, TRUE, Reverse, 0);
		//DrawGraph((int)bullet->posX-camera.pos.x, (int)bullet->posY-camera.pos.y, bullet->handle[CHANGE_ARCHERBULLET], TRUE, );
	}
}

void FinBullet()
{
	DeleteGraph(g_BulletHandle);
}

void FirePlayerBullet(float posX, float posY, int dir)
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (g_BulletData[i].active == false)
		{
			g_BulletData[i].dir = dir;
			g_BulletData[i].active = true;
			g_BulletData[i].posX = posX;
			g_BulletData[i].posY = posY;
			g_BulletData[i].boxCollision.posX = 12;
			g_BulletData[i].boxCollision.posY = 6;
			g_BulletData[i].boxCollision.width = 48;
			g_BulletData[i].boxCollision.height = 8;
			break;
		}
	}
	
	
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

void CalcBulletBoxCollision(BulletData* bullet, float& x, float& y, float& w, float& h)
{
	x = bullet->posX + bullet->boxCollision.posX;
	y = bullet->posY + bullet->boxCollision.posY;
	w = bullet->boxCollision.width;
	h = bullet->boxCollision.height;
}
