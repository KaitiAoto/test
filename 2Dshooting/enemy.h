//============================
//
//  敵表示処理[enemy.h]
//  Author:kaiti
//
//============================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"

#define NUM_ENEMY (4)
#define ENEMY_WIDTH (100)
#define ENEMY_HEIGTH (100)

//敵の状態
typedef enum
{
	ENEMYSTATE_NORMAL = 0,
	ENEMYSTATE_DAMAGE,
	ENEMYSTATE_MAX
}ENEMYSTATE;
//敵構造体
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXVECTOR3 rot;
	int nType;
	ENEMYSTATE state;
	int nCounterState;
	int nCounterBullet;
	int nLife;
	float fLengthEnemy;
	float fAngleEnemy;
	bool bUse;
}Enemy;

//プロトタイプ宣言
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, int Type);
Enemy* GetEnemy(void);
void HitEnemy(int nCntEnemy, int nDamage);
#endif