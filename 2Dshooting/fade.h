//==============================
//
//  フェード表示処理[fade.h]
//  Author:kaiti
//
//==============================
#ifndef _FADE_H_
#define _FADE_H_

#include"main.h"

//フェードの状態
typedef enum
{
	FADE_NONE=0,
	FADE_IN,
	FADE_OUT,
	FADE_MAX,
}FADE;

//プロトタイプ宣言
void InitFade(MODE modeNext);
void UninitFade(void);
void UpdateFade(void);
void DrawFade(void);
void SetFade(MODE modeNext);
FADE GetFade(void);

#endif#pragma once
