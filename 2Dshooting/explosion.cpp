//=============================
//
//  ��������[explosion.cpp]
//  Author:kaiti
//
//=============================
#include "main.h"
#include "explosion.h"
#include "effect.h"
//�}�N����`
#define MAX_EXPLOSION (128)
//�����\����
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXCOLOR col;
	int nCounterAnim;
	int nPattemAnim;
	bool bUse;
}Explosion;
//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureExplosion = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;
Explosion g_aExplosion[MAX_EXPLOSION];
//================
//�����̏���������
//================
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntExplosion;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̐ݒ�
	D3DXCreateTextureFromFile(pDevice,
		                      "data\\TEXTURE\\Explosion000.png",
		                      &g_pTextureExplosion);

	//�������̏�����
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		g_aExplosion[nCntExplosion].nCounterAnim = 0;
		g_aExplosion[nCntExplosion].nPattemAnim = 0;
		g_aExplosion[nCntExplosion].bUse = false;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EXPLOSION,
		                        D3DUSAGE_WRITEONLY,
		                        FVF_VERTEX_2D,
		                        D3DPOOL_MANAGED,
		                        &g_pVtxBuffExplosion,
		                        NULL);
	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
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
		pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffExplosion->Unlock();
}
//==============
//�����̏I������
//==============
void UninitExplosion(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}
}
//===============
//�����̍X�V����
//===============
void UpdateExplosion(void)
{
	int nCntExplosion;

	//���_���W���X�V
	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{
			SetEffect(g_aExplosion[nCntExplosion].pos, D3DCOLOR_RGBA(255, 255, 255, 255), 30, 30.0);

			if (nCntExplosion > MAX_EXPLOSION)
			{
				g_aExplosion->bUse = false;
			}

			g_aExplosion[nCntExplosion].nCounterAnim++;

			if ((g_aExplosion[nCntExplosion].nCounterAnim  % 5) == 0)
			{//��莞�Ԍo��
				//�p�^�[��No���X�V
				g_aExplosion[nCntExplosion].nPattemAnim = (g_aExplosion[nCntExplosion].nPattemAnim + 1) % 8;


				//�e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2((g_aExplosion[nCntExplosion].nPattemAnim % 8) * 0.125f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2((g_aExplosion[nCntExplosion].nPattemAnim % 8) * 0.125f + 0.125f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2((g_aExplosion[nCntExplosion].nPattemAnim % 8) * 0.125f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2((g_aExplosion[nCntExplosion].nPattemAnim % 8) * 0.125f + 0.125f,1.0f);
			}
			if (g_aExplosion[nCntExplosion].nCounterAnim == 32)
			{
				g_aExplosion[nCntExplosion].bUse = false;
			}
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffExplosion->Unlock();
}
//==============
//�����̕`�揈��
//==============
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntExplosion;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureExplosion);
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				                   nCntExplosion*4,
				                   2);
		}
	}
}
//===============
//�����̐ݒ菈��
//===============
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	int nCntExplosion;
	//���_���W���X�V
	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == false)
		{//�������g�p���Ă��Ȃ�
			g_aExplosion[nCntExplosion].pos = pos;
			g_aExplosion[nCntExplosion].nCounterAnim = 0;
			g_aExplosion[nCntExplosion].nPattemAnim = 0;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - 35, g_aExplosion[nCntExplosion].pos.y - 35, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 35, g_aExplosion[nCntExplosion].pos.y - 35, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - 35, g_aExplosion[nCntExplosion].pos.y + 35, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 35, g_aExplosion[nCntExplosion].pos.y + 35, 0.0f);
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
			pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);

			g_aExplosion[nCntExplosion].bUse = true;

			break;
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffExplosion->Unlock();
}