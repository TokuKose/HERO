#include "DxLib.h"
#include "PlayerAttack.h"
#include "../Camera/Camera.h"
#include "../Input/Input.h"
#include "../Collision/Collision.h"
#include "../Map/MapManager.h"
#include "../Enemy/Enemy.h"
#include "../Player/Player.h"

#define PLAYERATTACK_MAP_COLLISION_OFFSET (0.05f)

PlayerAttackData g_PlayerAttackData = { 0 };

void CalcBoxCollision(PlayerAttackData player, float& x, float& y, float& w, float& h);

void InitPlayerAttack()
{
	g_PlayerAttackData.boxCollision.width = 40;
	g_PlayerAttackData.boxCollision.height = 40;
}

void LoadPlayerAttack()
{
	g_PlayerAttackData.handle = LoadGraph("Data/Player/Slash.png");
}

void StartPlayerAttack()
{
}

void StepPlayerAttack()
{
}

void UpdatePlayerAttack()
{
	g_PlayerAttackData.Timer = g_PlayerAttackData.Timer - 1;
	if (g_PlayerAttackData.Timer <= 0)
	{
		g_PlayerAttackData.active = false;
	}
}

void DrawPlayerAttack()
{
	CameraData camera = GetCamera();
	PlayerData* Player = GetPlayer();
	int Reverse = 1;
	if (g_PlayerAttackData.active == true)
	{
		DrawRectGraph((int)(g_PlayerAttackData.posX - camera.pos.x), (int)(g_PlayerAttackData.posY - camera.pos.y), 0, 0, 40, 40, g_PlayerAttackData.handle, TRUE, g_PlayerAttackData.isTurn, 0);
	}

	/*
	if (Player->dir = 1)
	{
		g_PlayerAttackData.posX = Player->posX = Player->posX + 5;
	}
	else
	{
		g_PlayerAttackData.posX = Player->posX = Player->posX - 5;
	}
	g_PlayerAttackData.posY = Player->posY ;
	*/
}

void FinPlayerAttack()
{
}

void FirePlayerAttack(float posX, float posY, bool turn)
{
	g_PlayerAttackData.active = true;
	g_PlayerAttackData.posX = posX;
	g_PlayerAttackData.posY = posY;
	g_PlayerAttackData.isTurn = turn;
	g_PlayerAttackData.Timer = 10;
}

PlayerAttackData* GetPlayerAttack()
{
	return nullptr;
}

void PlayerAttackHitEnemy()
{
	PlayerAttackData tempPlayerAttack = g_PlayerAttackData;
	if (g_PlayerAttackData.active == false)
	{
		return;
	}
	
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		EnemyData* Enemy = GetEnemy(i);
		const float POS_OFFSET = PLAYERATTACK_MAP_COLLISION_OFFSET;
		const float SIZE_OFFSET = PLAYERATTACK_MAP_COLLISION_OFFSET * 2;



		// まだ当たっているなら縦に当たっている
		// 当たり判定のボックス計算
		float x, y, w, h;
		CalcBoxCollision(tempPlayerAttack, x, y, w, h);

		if (CheckSquareSquare(x + POS_OFFSET, y + POS_OFFSET, w - SIZE_OFFSET, h - SIZE_OFFSET,
			Enemy->posX, Enemy->posY, ENEMY_WIDTH, ENEMY_HEIGHT))
		{
			// 上からあたったか
			if (tempPlayerAttack.moveY > 0.0f)
			{
				Enemy->Life = Enemy->Life - 1;

			}
			// 下からあたったか
			else
			{
				Enemy->Life = Enemy->Life - 1;

			}
		}
	}
}


void CalcBoxCollision(PlayerAttackData player, float& x, float& y, float& w, float& h)
{
	x = player.isTurn ?
		player.posX + PLAYERATTACK_WIDTH - player.boxCollision.posX - player.boxCollision.width :
		player.posX + player.boxCollision.posX;
	y = player.posY + player.boxCollision.posY;
	w = player.boxCollision.width;
	h = player.boxCollision.height;
}
