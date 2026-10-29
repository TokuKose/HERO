#pragma once

struct BoxCollision
{
	float posX;
	float posY;
	float width;
	float height;
};

// 関数のプロトタイプ宣言

// 矩形と点の当たり判定
bool CheckSquarePoint(float squarePosX, float squarePosY, float squareWidth, float squareHeight, float pointX, float pointY);

// 矩形と矩形の当たり判定
bool CheckSquareSquare(float squareA_PosX, float squareA_PosY, float squareA_Width, float squareA_Height, float squareB_PosX, float squareB_PosY, float squareB_Width, float squareB_Height);

// 円と点の当たり判定
bool CheckCirclePoint(float circlePosX, float circlePosY, float circleRadius, float pointX, float pointY);

// 円と円の当たり判定
bool CheckCircleCircle(float circleA_PosX, float circleA_PosY, float circleA_Radius, float circleB_PosX, float circleB_PosY, float circleB_Radius);

// 各当たり判定を行う
void CheckCollision();

