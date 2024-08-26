//=================================
//
//  プレイヤー表示処理[player.h]
//  Author:kaiti
//
//=================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#define PLAYER_WIDTH (50)
#define PLAYER_HEIGTH (75)

//
typedef enum
{
	PLAYERSTATE_APPEAR = 0,
	PLAYERSTATE_NORMAL,
	PLAYERSTATE_DAMAGE,
	PLAYERSTATE_DEATH,
	PLAYERSTATE_MAX,
}PLAYERSTATE;
//プレイヤー構造体
typedef struct
{
	int nCounterAnimPlayer;
	int nPatternAnimPlayer;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	PLAYERSTATE state;
	int nCounterState;
	D3DXVECTOR3 rot;
	int nLife;
	float fLengthPlayer;
	float fAnglePlayer;
	bool bUse;
}Player;
//プロトタイプ宣言
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
Player* GetPlayer(void);
void HitPlayer(int nDamage);

#endif
