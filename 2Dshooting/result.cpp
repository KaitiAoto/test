//================================
//
//  ���U���g�\������[result.cpp]
//  Author:kaiti
//
//================================
#include "result.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "game.h"
//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureResult[2] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;
RESULT g_gamestate = RESULT_NONE;
int g_nCounterResultState = 0;
//===========
//����������
//===========
void InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\kokuban3.png", &g_pTextureResult[0]); //�N���A
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\kokuban1.png", &g_pTextureResult[1]); //�Q�[���I�[�o�[

	//���_�o�b�t�@�̐����E���_���̐ݒ�
	VERTEX_2D* pVtx;
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		                        D3DUSAGE_WRITEONLY,
		                        FVF_VERTEX_2D,
		                        D3DPOOL_MANAGED,
		                        &g_pVtxBuffResult,
		                        NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffResult->Unlock();
}
//==========
//�I������
//==========
void UninitResult(void)
{
	int nCnt;
	for (nCnt = 0; nCnt < 2; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureResult[nCnt] != NULL)
		{
			g_pTextureResult[nCnt]->Release();
			g_pTextureResult[nCnt] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}
}
//==========
//�X�V����
//==========
void UpdateResult(void)
{
	if (KeyboardTrigger(DIK_RETURN) == true)
	{//����L�[�������ꂽ
		//���[�h�ݒ�
		SetFade(MODE_TITLE);
	}
}
//==========
//�`�揈��
//==========
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	//�e�N�X�`���̐ݒ�
	if (g_gamestate == RESULT_CLEAR)
	{
		pDevice->SetTexture(0, g_pTextureResult[0]);
	}
	else if (g_gamestate == RESULT_GAMEOVER)
	{
		pDevice->SetTexture(0, g_pTextureResult[1]);
	}
	//�v���C���[�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
//===============
//���U���g�ݒ�
//===============
void SetResult(RESULT result)
{
	g_gamestate = result;
	g_nCounterResultState = 0;
}