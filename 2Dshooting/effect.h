//==============================
//
//  �G�t�F�N�g����[effect.h]
//  Author:kaiti
//
//==============================
#ifndef _EFFECT_H_
#define _EFFECT_H_


//�v���g�^�C�v�錾
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col,int nLife,float fRadius);

#endif
