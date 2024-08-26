//==============================
//
//  �G�t�F�N�g����[effect.cpp]
//  Author:kaiti
//
//==============================
#include "main.h"
#include "player.h"
#include "effect.h"
#include "enemy.h"
#include "bullet.h"
//�}�N����`
#define MAX_EFFECT (4096)
//�G�t�F�N�g�\����
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXCOLOR col;
	int nLife;
	float fRadius;
	bool bUse;
}Effect;
//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureEffect = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;
Effect g_aEffect[MAX_EFFECT];
//=========================
//�G�t�F�N�g�̏���������
//=========================
void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEffect;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̐ݒ�
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\effect000.jpg", &g_pTextureEffect);//�v���C���[�̃G�t�F�N�g

	//�G�t�F�N�g���̏�����
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_aEffect[nCntEffect].nLife = 100;
		g_aEffect[nCntEffect].bUse = false;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EFFECT,
		                        D3DUSAGE_WRITEONLY,
		                        FVF_VERTEX_2D,
		                        D3DPOOL_MANAGED,
		                        &g_pVtxBuffEffect,
		                        NULL);
	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffEffect->Unlock();
}
//======================
//�G�t�F�N�g�̏I������
//======================
void UninitEffect(void)
{
	int nCnt;
	//�e�N�X�`���̔j��
	for (nCnt = 0; nCnt < MAX_EFFECT; nCnt++)
	{
		if (g_pTextureEffect != NULL)
		{
			g_pTextureEffect->Release();
			g_pTextureEffect = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}
//=======================
//�G�t�F�N�g�̍X�V����
//=======================
void UpdateEffect(void)
{
	int nCntEffect;
	//���_���W���X�V
	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{
			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 0.5f, 0.0f, g_aEffect[nCntEffect].nLife);
			pVtx[1].col = D3DXCOLOR(1.0f, 0.5f, 0.0f, g_aEffect[nCntEffect].nLife);
			pVtx[2].col = D3DXCOLOR(1.0f, 0.5f, 0.0f, g_aEffect[nCntEffect].nLife);
			pVtx[3].col = D3DXCOLOR(1.0f, 0.5f, 0.0f, g_aEffect[nCntEffect].nLife);

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].pos.y - g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].pos.y - g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].fRadius, 0.0f);

			g_aEffect[nCntEffect].nLife -= 0.1;
			g_aEffect[nCntEffect].fRadius -= 1.0;
			//�G�t�F�N�g�̎���
			if (g_aEffect[nCntEffect].nLife <= 0)
			{
				g_aEffect[nCntEffect].bUse = false;
			}
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffEffect->Unlock();
}
//=======================
//�G�t�F�N�g�̕`�揈��
//=======================
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEffect;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureEffect);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				                   nCntEffect *4,
				                   2);
		}
	}
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}
//======================
//�G�t�F�N�g�̐ݒ菈��
//======================
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, int nLife, float fRadius)
{
	int nCntEffect;
	//���_���W���X�V
	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == false)
		{//�G�t�F�N�g���g�p���Ă��Ȃ�
			g_aEffect[nCntEffect].pos = pos;
			g_aEffect[nCntEffect].col = col;
			g_aEffect[nCntEffect].fRadius = fRadius;
			g_aEffect[nCntEffect].nLife = nLife;
			g_aEffect[nCntEffect].bUse = true;
			break;
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffEffect->Unlock();
}