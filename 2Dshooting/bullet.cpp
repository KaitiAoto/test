//==========================
//
//  �e���ˏ���[bullet.cpp]
//  Author:kaiti
//
//==========================
#include "main.h"
#include "player.h"
#include "bullet.h"
#include "explosion.h"
#include "enemy.h"
#include "effect.h"
//�}�N����`
#define MAX_BULLET (256)
//�e�\����
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	int nLife;
	BULLETTYPE type;
	bool bUse;
}Bullet;
//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureBullet[2] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;
Bullet g_aBullet[MAX_BULLET];
//================
//�e�̏���������
//================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̐ݒ�
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\sodapdf-converted.png",&g_pTextureBullet[0]);//�v���C���[�̒e
	//D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bullet000.png", &g_pTextureBullet[0]);//�v���C���[�̒e

	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\2143503.png", &g_pTextureBullet[1]);//�G�̒e1

	//�e���̏�����
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nLife = 100;
		g_aBullet[nCntBullet].bUse = false;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BULLET,
		                        D3DUSAGE_WRITEONLY,
		                        FVF_VERTEX_2D,
		                        D3DPOOL_MANAGED,
		                        &g_pVtxBuffBullet,
		                        NULL);
	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
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
	g_pVtxBuffBullet->Unlock();
}
//==============
//�e�̏I������
//==============
void UninitBullet(void)
{
	int nCnt;
	//�e�N�X�`���̔j��
	for (nCnt = 0; nCnt < 2; nCnt++)
	{
		if (g_pTextureBullet[nCnt] != NULL)
		{
			g_pTextureBullet[nCnt]->Release();
			g_pTextureBullet[nCnt] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}
//===============
//�e�̍X�V����
//===============
void UpdateBullet(void)
{
	int nCntBullet;
	//���_���W���X�V
	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			SetEffect(g_aBullet[nCntBullet].pos, D3DCOLOR_RGBA(255, 255, 255, 255), 30, 30.0);

			if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER)
			{//�v���C���[�̒e
				int nCntEnemy;
				Enemy* pEnemy;
				//�G�擾
				pEnemy = GetEnemy();

				for (nCntEnemy = 0; nCntEnemy < NUM_ENEMY; nCntEnemy++, pEnemy++)
				{
					if (pEnemy->bUse == true)
					{
						if (   g_aBullet[nCntBullet].pos.x >= pEnemy->pos.x - 50.0f //���[
							&& g_aBullet[nCntBullet].pos.x <= pEnemy->pos.x + 50.0f //�E�[
							&& g_aBullet[nCntBullet].pos.y >= pEnemy->pos.y - 50.0f //��[
							&& g_aBullet[nCntBullet].pos.y <= pEnemy->pos.y + 50.0f)//���[
						{
							//�G�̃q�b�g����
							HitEnemy(nCntEnemy, 1);
							SetExplosion(pEnemy->pos, 1.0f);
							g_aBullet[nCntBullet].bUse = false;
						}
					}
				}
			}
			else if (g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY1)
			{//�G�̒e
				Player* pPlayer;
				//�v���C���[�擾
				pPlayer = GetPlayer();

				if (pPlayer->bUse == true)
				{
					if (   g_aBullet[nCntBullet].pos.x >= pPlayer->pos.x - 50.0f //���[
						&& g_aBullet[nCntBullet].pos.x <= pPlayer->pos.x + 50.0f //�E�[
						&& g_aBullet[nCntBullet].pos.y >= pPlayer->pos.y - 50.0f //��[
						&& g_aBullet[nCntBullet].pos.y <= pPlayer->pos.y + 50.0f)//���[
					{
						//�G�̃q�b�g����
						//pPlayer->bUse = false;
						HitPlayer(1);
						g_aBullet[nCntBullet].bUse = false;
					}
				}
			}

			//�e�̈ʒu���X�V
			g_aBullet[nCntBullet].pos.x += g_aBullet[nCntBullet].move.x;
			g_aBullet[nCntBullet].pos.y += g_aBullet[nCntBullet].move.y;
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 30, g_aBullet[nCntBullet].pos.y - 20, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 30, g_aBullet[nCntBullet].pos.y - 20, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 30, g_aBullet[nCntBullet].pos.y + 20, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 30, g_aBullet[nCntBullet].pos.y + 20, 0.0f);

			//�e����ʊO�ɂ�����
			if (g_aBullet[nCntBullet].pos.x >= SCREEN_WIDTH || g_aBullet[nCntBullet].pos.y >= SCREEN_HEIGHT || g_aBullet[nCntBullet].pos.x <= 0 || g_aBullet[nCntBullet].pos.y <= 0)
			{
				g_aBullet[nCntBullet].bUse = false;
			}

			g_aBullet[nCntBullet].nLife -= 0.1;
			//�e�̎���
			if (g_aBullet[nCntBullet].nLife <= 0)
			{
				SetExplosion(g_aBullet[nCntBullet].pos, 1.0);
				g_aBullet[nCntBullet].bUse = false;
			}
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBullet->Unlock();
}
//==============
//�e�̕`�揈��
//==============
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			//�e�N�X�`���̐ݒ�
			if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER)
			{
				pDevice->SetTexture(0, g_pTextureBullet[0]);
			}
			else if (g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY1)
			{
				pDevice->SetTexture(0, g_pTextureBullet[1]);
			}
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				                   nCntBullet*4,
				                   2);
		}
	}
}
//===============
//�e�̐ݒ菈��
//===============
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, BULLETTYPE type)
{
	int nCntBullet;
	//���_���W���X�V
	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{//�e���g�p���Ă��Ȃ�
			g_aBullet[nCntBullet].pos = pos;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 10, g_aBullet[nCntBullet].pos.y - 10, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 10, g_aBullet[nCntBullet].pos.y - 10, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 10, g_aBullet[nCntBullet].pos.y + 10, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 10, g_aBullet[nCntBullet].pos.y + 10, 0.0f);
			//rhw�̐ݒ�
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			g_aBullet[nCntBullet].move = move;
			g_aBullet[nCntBullet].nLife = nLife;
			g_aBullet[nCntBullet].type = type;
			g_aBullet[nCntBullet].bUse = true;
			break;
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBullet->Unlock();
}