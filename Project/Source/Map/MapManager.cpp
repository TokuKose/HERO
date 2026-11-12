#include "MapManager.h"
#include "MapParameter.h"
#include "MapChip.h"
#include "Block.h"
#include "../Player/Player.h"
#include"../Enemy/Enemy.h"
#include "../Collision/Collision.h"

// キャラクターの周囲何マスまでチェックするか
#define CHECK_ROUND_NUM (2)

void InitMap()
{
}

void LoadMap()
{
	LoadMapChipData();
	LoadBlock();
}

void StartMap()
{
	CreateMap();
}

void DrawMap()
{
	// ブロック描画
	DrawBlock();
}

void FinMap()
{
}
void MoveWithMapCollision(Body* body)
{
	// X軸だけ移動する
	body->pos.x += body->move.x;

	// マップチップと当たり判定＆押し出し
	for (int y = 0; y < MAP_CHIP_Y_NUM; y++)
	{
		for (int x = 0; x < MAP_CHIP_X_NUM; x++)
		{
			// マップチップ取得
			MapChipData mapChipData = GetMapChipData(x, y);
			// マップチップが0の場合は何もない
			if (mapChipData.mapChip == 0) continue;

			// ブロックを取り出して当たり判定
			BlockData* block = mapChipData.data;
			// 当たり判定
			if (CheckSquareSquare(body->pos.x, body->pos.y, body->width, body->height,
				block->pos.x, block->pos.y, block->width, block->height))
			{
				// 左からあたったか
				if (body->move.x > 0.0f)
				{
					// 左に押し出す
					body->pos.x -= ((body->pos.x + body->width) - block->pos.x);

				}
				// 右からあたったか
				else if (body->move.x < 0.0f)
				{
					// 右に押し出す
					body->pos.x -= body->pos.x - (block->pos.x + block->width);

				}

				// 移動量は0にする
				body->move.x = 0.0f;
			}

		}
	}

	// Y軸だけ移動する
	body->pos.y += body->move.y;

	// マップチップと当たり判定＆押し出し
	for (int y = 0; y < MAP_CHIP_Y_NUM; y++)
	{
		for (int x = 0; x < MAP_CHIP_X_NUM; x++)
		{
			// マップチップ取得
			MapChipData mapChipData = GetMapChipData(x, y);
			// マップチップが0の場合は何もない
			if (mapChipData.mapChip == 0) continue;

			// ブロックを取り出して当たり判定
			BlockData* block = mapChipData.data;
			// 当たり判定
			if (CheckSquareSquare(body->pos.x, body->pos.y, body->width, body->height,
				block->pos.x, block->pos.y, block->width, block->height))
			{
				// 上からあたったか
				if (body->move.y > 0.0f)
				{
					// 上に押し出す
					body->pos.y -= ((body->pos.y + body->width) - block->pos.y);

					// 空中フラグを折る
					body->isAir = false;
				}
				// 下からあたったか
				else if (body->move.y < 0.0f)
				{
					// 下に押し出す
					body->pos.y -= body->pos.y - (block->pos.y + block->width);

				}

				// 移動量は0にする
				body->move.y = 0.0f;
			}

		}
	}

	
}
void ChceckMapPlayerCollision()
{
	PlayerData* player = GetPlayer();

	int playerX, playerY;
	int left, right, top, bottom;

	// プレイヤーの足元の座標をマップチップのインデックスに変換、xは移動前の場所の位置で計算
	playerX = (int)(player->beforposX / MAP_CHIP_WIDTH);
	playerY = (int)((player->posY + PLAYER_HEIGHT) / MAP_CHIP_HEIGHT);
	//上下移動なので自身より上か下にあるブロックだけを検索する
	left = playerX - CHECK_ROUND_NUM;
	right = playerX + CHECK_ROUND_NUM;
	top = playerY - ((player->moveY < 0) ? CHECK_ROUND_NUM : 0);
	bottom = playerY + ((player->moveY > 0) ? CHECK_ROUND_NUM : 0);

	// 左上から3マスずつチェックしていく
	for (int y = top; y <= bottom; y++)
	{
		// マップチップからはみ出したら処理しなくていい
		if (y < 0 || y >= MAP_CHIP_Y_NUM) continue;

		for (int x = left; x <= right; x++)
		{
			// マップチップからはみ出したら処理しなくていい
			if (x < 0 || x >= MAP_CHIP_X_NUM) continue;

			// マップチップ番号を取得
			MapChipData mapChipData = GetMapChipData(x, y);
			switch (mapChipData.mapChip)
			{
			case NORMAL_BLOCK:
				PlayerHitNormalBlockY(mapChipData);
				break;
			}
		}
	}

	// プレイヤーの足元の座標をマップチップのインデックスに変換、xは移動前の場所の位置で計算
	playerX = (int)(player->posX / MAP_CHIP_WIDTH);
	playerY = (int)((player->posY + PLAYER_HEIGHT) / MAP_CHIP_HEIGHT);
	//左右移動なので自身より左か右にあるブロックだけを検索する
	left = playerX - ((player->moveX < 0) ? CHECK_ROUND_NUM : 0);
	right = playerX + ((player->moveX > 0) ? CHECK_ROUND_NUM : 0);
	top = playerY - CHECK_ROUND_NUM;
	bottom = playerY + CHECK_ROUND_NUM;

	// 左上から3マスずつチェックしていく
	for (int y = top - 1; y <= bottom; y++)
	{
		// マップチップからはみ出したら処理しなくていい
		if (y < 0 || y >= MAP_CHIP_Y_NUM) continue;

		for (int x = left; x <= right; x++)
		{
			// マップチップからはみ出したら処理しなくていい
			if (x < 0 || x >= MAP_CHIP_X_NUM) continue;

			// マップチップ番号を取得
			MapChipData mapChipData = GetMapChipData(x, y);
			switch (mapChipData.mapChip)
			{
			case NORMAL_BLOCK:
				PlayerHitNormalBlockX(mapChipData);
				break;
			}
		}
	}
}

void ChceckMapEnemyCollision()
{
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		EnemyData* enemy = GetEnemy(i);

		int enemyX, enemyY;
		int left, right, top, bottom;

		// プレイヤーの足元の座標をマップチップのインデックスに変換、xは移動前の場所の位置で計算
		enemyX = (int)(enemy->beforposX / MAP_CHIP_WIDTH);
		enemyY = (int)((enemy->posY + PLAYER_HEIGHT) / MAP_CHIP_HEIGHT);
		//上下移動なので自身より上か下にあるブロックだけを検索する
		left = enemyX - CHECK_ROUND_NUM;
		right = enemyX + CHECK_ROUND_NUM;
		top = enemyY - ((enemy->moveY < 0) ? CHECK_ROUND_NUM : 0);
		bottom = enemyY + ((enemy->moveY > 0) ? CHECK_ROUND_NUM : 0);

		// 左上から3マスずつチェックしていく
		for (int y = top; y <= bottom; y++)
		{
			// マップチップからはみ出したら処理しなくていい
			if (y < 0 || y >= MAP_CHIP_Y_NUM) continue;

			for (int x = left; x <= right; x++)
			{
				// マップチップからはみ出したら処理しなくていい
				if (x < 0 || x >= MAP_CHIP_X_NUM) continue;

				// マップチップ番号を取得
				MapChipData mapChipData = GetMapChipData(x, y);
				switch (mapChipData.mapChip)
				{
				case NORMAL_BLOCK:
					EnemyHitNormalBlockY(enemy, mapChipData);
					break;
				}
			}
		}

		// プレイヤーの足元の座標をマップチップのインデックスに変換、xは移動前の場所の位置で計算
		enemyX = (int)(enemy->posX / MAP_CHIP_WIDTH);
		enemyY = (int)((enemy->posY + PLAYER_HEIGHT) / MAP_CHIP_HEIGHT);
		//左右移動なので自身より左か右にあるブロックだけを検索する
		left = enemyX - ((enemy->moveX < 0) ? CHECK_ROUND_NUM : 0);
		right = enemyX + ((enemy->moveX > 0) ? CHECK_ROUND_NUM : 0);
		top = enemyY - CHECK_ROUND_NUM;
		bottom = enemyY + CHECK_ROUND_NUM;

		// 左上から3マスずつチェックしていく
		for (int y = top - 1; y <= bottom; y++)
		{
			// マップチップからはみ出したら処理しなくていい
			if (y < 0 || y >= MAP_CHIP_Y_NUM) continue;

			for (int x = left; x <= right; x++)
			{
				// マップチップからはみ出したら処理しなくていい
				if (x < 0 || x >= MAP_CHIP_X_NUM) continue;

				// マップチップ番号を取得
				MapChipData mapChipData = GetMapChipData(x, y);
				switch (mapChipData.mapChip)
				{
				case NORMAL_BLOCK:
					EnemyHitNormalBlockX(enemy, mapChipData);
					break;
				}
			}
		}
	}
}
