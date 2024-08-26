//========================
//
//  �e���ˏ���[bullet.h]
//  Author:kaiti
//
//========================
#ifndef _BULLET_H_
#define _BULLET_H_

//�e�̎��
typedef enum
{
	BULLETTYPE_PLAYER = 0,
	BULLETTYPE_ENEMY1,
	BULLETTYPE_MAX,

}BULLETTYPE;

//�v���g�^�C�v�錾
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move,int nLife,BULLETTYPE type);

#endif
