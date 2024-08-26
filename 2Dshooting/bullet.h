//========================
//
//  弾発射処理[bullet.h]
//  Author:kaiti
//
//========================
#ifndef _BULLET_H_
#define _BULLET_H_

//弾の種類
typedef enum
{
	BULLETTYPE_PLAYER = 0,
	BULLETTYPE_ENEMY1,
	BULLETTYPE_MAX,

}BULLETTYPE;

//プロトタイプ宣言
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move,int nLife,BULLETTYPE type);

#endif
