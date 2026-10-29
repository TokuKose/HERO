#include "DxLib.h"
#include "Collision.h"
#include "../Player/Player.h"
#include "../Map/Block.h"
#include "../Map//MapManager.h"
#include <math.h>

// 矩形と点の当たり判定
// 引数
// squarePosX:矩形の左上X座標
// squarePosY:矩形の左上Y座標
// squareWidth:矩形の横幅
// squareHeight:矩形の高さ
// pointX:点のX座標
// pointY:点のY座標
// 戻り値
// 当たっていればtrue
bool CheckSquarePoint(float squarePosX, float squarePosY, float squareWidth, float squareHeight, float pointX, float pointY)
{
	// 点のX座標が矩形の間にあるか
	if (pointX >= squarePosX && pointX <= (squarePosX + squareWidth))
	{
		// 点のY座標が矩形の間にあるか
		if (pointY >= squarePosY && (pointY <= squarePosY + squareHeight))
		{
			// 当たっている
			return true;
		}
	}

	return false;
}

// 矩形と矩形の当たり判定
// 引数
// squareA_PosX:矩形Aの左上X座標
// squareA_PosY:矩形Aの左上Y座標
// squareA_Width:矩形Aの横幅
// squareA_Height:矩形Aの高さ
// squareB_PosX:矩形Bの左上X座標
// squareB_PosY:矩形Bの左上Y座標
// squareB_Width:矩形Bの横幅
// squareB_Height:矩形Bの高さ
// 戻り値
// 当たっていればtrue
bool CheckSquareSquare(float squareA_PosX, float squareA_PosY, float squareA_Width, float squareA_Height, float squareB_PosX, float squareB_PosY, float squareB_Width, float squareB_Height)
{
	// 矩形Aの各辺の位置を計算する
	float leftA = squareA_PosX;
	float rightA = squareA_PosX + squareA_Width;
	float topA = squareA_PosY;
	float bottomA = squareA_PosY + squareA_Height;

	// 矩形Bの各辺の位置を計算する
	float leftB = squareB_PosX;
	float rightB = squareB_PosX + squareB_Width;
	float topB = squareB_PosY;
	float bottomB = squareB_PosY + squareB_Height;

	// 左右の辺がめり込んでいるかチェック
	if (rightA >= leftB && leftA <= rightB)
	{
		// 上下の片がめり込んでいるかチェック
		if (bottomA >= topB && topA <= bottomB)
		{
			// 当たっている
			return true;
		}
	}

	return false;
}

// 円と点の当たり判定
// 引数
// circlePosX:円の中心座標（X）
// circlePosY:円の中心座用（Y）
// circleRadius:円の半径
// pointX:点のX座標
// pointY:点のY座標
// 戻り値
// 当たっていればtrue
bool CheckCirclePoint(float circlePosX, float circlePosY, float circleRadius, float pointX, float pointY)
{
	// 円の中心から点までの距離を計算する
	float distance = sqrtf((pointX - circlePosX) * (pointX - circlePosX) + (pointY - circlePosY) * (pointY - circlePosY));

	// 求めた距離が半径の長さ以下であれば当たっている
	if (distance <= circleRadius)
	{
		return true;
	}

	return false;
}

// 円と点の当たり判定
// 引数
// circleA_PosX:円Aの中心座標（X）
// circleA_PosY:円Aの中心座用（Y）
// circleA_Radius:円Aの半径
// circleB_PosX:円Bの中心座標（X）
// circleB_PosX:円Bの中心座用（Y）
// circleB_Radius:円Bの半径
// 戻り値
// 当たっていればtrue
bool CheckCircleCircle(float circleA_PosX, float circleA_PosY, float circleA_Radius, float circleB_PosX, float circleB_PosY, float circleB_Radius)
{
	// 円の中心間の距離を計算する
	float distance = sqrtf((circleB_PosX - circleA_PosX) * (circleB_PosX - circleA_PosX) + (circleB_PosY - circleA_PosY) * (circleB_PosY - circleA_PosY));

	// 中心間の距離が2つの円の半径の合計以下であれば当たっている
	if (distance <= (circleA_Radius + circleB_Radius))
	{
		return true;
	}

	return false;
}

void CheckCollision()
{
	// ここに当たり判定の処理を書く

	// プレイヤーとマップの当たり判定
	ChceckMapPlayerCollision();
}

