#pragma once
#include "DxLib.h"

struct CameraData
{
	VECTOR pos;
};

void InitCamera();
void StepCamera();
void DrawCamera();

CameraData GetCamera();