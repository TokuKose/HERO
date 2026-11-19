#include "BulletManager.h"
#include "Bullet.h"
void InitAllBullet()
{
	InitBullet();
}

void LoadAllBullet()
{
	LoadBullet();
}

void StepAllBullet()
{
	StepBullet();
}

void UpdateAllBullet()
{
	UpdateBullet();
}

void DrawAllBullet()
{
	DrawBullet();
}

void FinAllBullet()
{
	FinBullet();
}

void RequestFireBullet(int life, float posX, float posY, float moveX, float moveY, float radius)
{
}
