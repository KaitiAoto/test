//================================
//
//  ゲーム画面表示処理[game.cpp]
//  Author:kaiti
//
//================================
#include "game.h"
#include "player.h"
#include "background.h"
#include "input.h"
#include "bullet.h"
#include "explosion.h"
#include "enemy.h"
#include "fade.h"
#include "sound.h"
#include "score.h"
#include "result.h"
#include "effect.h"
//グローバル変数
GAMESTATE g_gamestate = GAMESTATE_NONE;
int g_nCounterGameState = 0;
//============
//初期化処理
//============
void InitGame(void)
{
	//背景
	InitBackground();
	//スコア
	InitScore();
	SetScore(0);
	//
	InitEffect();
	//弾
	InitBullet();
	//プレイヤー
	InitPlayer();
	//敵
	InitEnemy();
	SetEnemy(D3DXVECTOR3(100.0f, 100.0f, 0.0f), 0);
	//爆発
	InitExplosion();

	g_gamestate = GAMESTATE_NORMAL;
	g_nCounterGameState = 0;
}
//==========
//終了処理
//==========
void UninitGame(void)

{
	//背景
	UninitBackground();
	//スコア
	UninitScore();
	//プレイヤー
	UninitPlayer();
	//弾
	UninitBullet();
	//爆発
	UninitExplosion();
	//敵
	UninitEnemy();
	//
	UninitEffect();
}
//==========
//更新処理
//==========
void UpdateGame(void)
{
	//背景
	UpdateBackground();
	//スコア
	UpdateScore();
	//
	UpdateEffect();
	//プレイヤー
	UpdatePlayer();
	//弾
	UpdateBullet();
	//敵
	UpdateEnemy();
	//爆発
	UpdateExplosion();

	switch (g_gamestate)
	{
	case GAMESTATE_NORMAL:
		break;
	case GAMESTATE_CLEAR:
		g_nCounterGameState++;
		if (g_nCounterGameState >= 30)
		{
			g_gamestate = GAMESTATE_NONE;
			SetResult(RESULT_CLEAR);
			//モードをリザルトにする
			SetFade(MODE_RESULT);
		}
		break;
	case GAMESTATE_GAMEOVER:
		g_nCounterGameState++;
		if (g_nCounterGameState >= 30)
		{
			g_gamestate = GAMESTATE_NONE;
			SetResult(RESULT_GAMEOVER);
			//モードをリザルトにする
			SetFade(MODE_RESULT);
		}
		break;
	}
}
//==========
//描画処理
//==========
void DrawGame(void)
{
	//背景
	DrawBackground();
	//スコア
	DrawScore();
	//爆発
	DrawExplosion();
	//
	DrawEffect();
	//弾
	DrawBullet();
	//プレイヤー
	DrawPlayer();
	//敵
	DrawEnemy();
}
//==============
//ゲームの状態
//==============
void SetGameState(GAMESTATE state)
{
	g_gamestate = state;
	g_nCounterGameState = 0;
}
//====================
//ゲームの状態の取得
//====================
GAMESTATE GetGameSatate(void)
{
	return g_gamestate;
}