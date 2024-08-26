//====================================
//
//	�w�i�\������[background.cpp]
//  Author:kaiti
//
//====================================
#include "main.h"
#include "player.h"
#include "background.h"

#define NUM_BG (3)
//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_apTextureBackground[NUM_BG] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBackground = NULL;
float g_aPosTexU[NUM_BG];
//============
//����������
//============
void InitBackground(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBG;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�w�i
    //�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bg100.png", &g_apTextureBackground[0]); //1
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bg101.png", &g_apTextureBackground[1]); //2
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bg102.png", &g_apTextureBackground[2]); //3

	//�e�N�X�`�����W�̊J�n�ʒu(U�l)�̏�����
	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		g_aPosTexU[nCntBG] = 0.0f;
	}

	VERTEX_2D* pVtx;
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 *NUM_BG,
		                        D3DUSAGE_WRITEONLY,
		                        FVF_VERTEX_2D,
		                        D3DPOOL_MANAGED,
		                        &g_pVtxBuffBackground,
		                        NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBackground->Lock(0, 0, (void**)&pVtx, 0);

	//�w�i
	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);
		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(g_aPosTexU[nCntBG], 0.0f);
		pVtx[1].tex = D3DXVECTOR2(g_aPosTexU[nCntBG] + 1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(g_aPosTexU[nCntBG], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(g_aPosTexU[nCntBG] + 1.0f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBackground->Unlock();
}
//============
//�I������
//============
void UninitBackground(void)
{
	int nCntBG;
	//�e�N�X�`���̔j��
	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
		if (g_apTextureBackground[nCntBG] != NULL)
	{
		g_apTextureBackground[nCntBG]->Release();
		g_apTextureBackground[nCntBG] = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBackground != NULL)
	{
		g_pVtxBuffBackground->Release();
		g_pVtxBuffBackground = NULL;
	}
}
//==========
//�X�V����
//==========
void UpdateBackground(void)
{
	int nCntBG;
	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBackground->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		//�e�N�X�`�����W�̊J�n�ʒu(U�l)�̏�����
		g_aPosTexU[0] += 0.0010f;
		g_aPosTexU[1] += 0.0012f;
		g_aPosTexU[2] += 0.0014f;

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(g_aPosTexU[nCntBG], 0.0f);
		pVtx[1].tex = D3DXVECTOR2(g_aPosTexU[nCntBG] + 1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(g_aPosTexU[nCntBG], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(g_aPosTexU[nCntBG] + 1.0f, 1.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBackground->Unlock();
}
//==========
//�`�揈��
//==========
void DrawBackground(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBackground, 0, sizeof(VERTEX_2D));

	int nCntBG;

	//�w�i
	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTextureBackground[nCntBG]);
		//�v���C���[�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBG * 4, 2);

	}
}