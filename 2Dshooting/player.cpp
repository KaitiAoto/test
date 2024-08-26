//===================================
//
//  �v���C���[�\������[player.cpp]
//  Author:kaiti
//
//===================================
#include "main.h"
#include "player.h"
#include "background.h"
#include "input.h"
#include "bullet.h"
#include "explosion.h"
#include "enemy.h"
#include "fade.h"
#include "game.h"
#include "result.h"
#include "effect.h"
//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;
Player g_player;
//========================
//�v���C���[�̏���������
//========================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	//1��
	//�e�N�X�`���̓ǂݍ���
	//D3DXCreateTextureFromFile(pDevice,"data\\TEXTURE\\runningman100.png",&g_pTexturePlayer);

	D3DXCreateTextureFromFile(pDevice,"data\\TEXTURE\\2006960.png",&g_pTexturePlayer);

	g_player.nCounterAnimPlayer = 0;
	g_player.nPatternAnimPlayer = 0;

	g_player.pos = D3DXVECTOR3(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, 0.0f);
	g_player.move = D3DXVECTOR3(0.0f,0.0f,0.0f);
	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.state = PLAYERSTATE_NORMAL;
	//�Ίp���̒������Z�o
	g_player.fLengthPlayer = sqrtf(PLAYER_WIDTH * PLAYER_WIDTH + PLAYER_HEIGTH * PLAYER_HEIGTH) / 2.0f;
	//�Ίp���̊p�x���Z�o
	g_player.fAnglePlayer = atan2f(PLAYER_WIDTH, PLAYER_HEIGTH);
	g_player.nLife = 3;
	g_player.bUse = true;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,
		                        D3DUSAGE_WRITEONLY,
		                        FVF_VERTEX_2D,
		                        D3DPOOL_MANAGED,
		                        &g_pVtxBuffPlayer,
		                        NULL);
	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	//pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - 50.0f, g_player.pos.y - 50.0f, 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + 50.0f, g_player.pos.y - 50.0f, 0.0f);
	//pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - 50.0f, g_player.pos.y + 50.0f, 0.0f);
	//pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + 50.0f, g_player.pos.y + 50.0f, 0.0f);
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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
	//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[1].tex = D3DXVECTOR2(0.2f, 0.0f);
	//pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
	//pVtx[3].tex = D3DXVECTOR2(0.2f, 0.5f);
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffPlayer->Unlock();

	g_player.rot.z -= D3DX_PI/2;
}
//======================
//�v���C���[�̏I������
//======================
void UninitPlayer(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
}
//======================
//�v���C���[�̍X�V����
//======================
void UpdatePlayer(void)
{
	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//SetEffect(g_player.pos, D3DCOLOR_RGBA(255, 255, 255, 255), 30, 30.0);

	if (g_player.bUse == true)
	{
		//�L�[���͂ɂ��ړ����R���g���[���[
		//��
		if (GetKeyboardPress(DIK_A) == true|| GetJoypadPress(JOYKEY_LEFT) == true)
		{// A
			if (GetKeyboardPress(DIK_W) == true || GetJoypadPress(JOYKEY_UP) == true)
			{//����
				g_player.move.x -= sinf(D3DX_PI * 0.75f) * 0.3f;
				g_player.move.y += cosf(D3DX_PI * 0.75f) * 0.3f;
			}
			else if (GetKeyboardPress(DIK_S) == true || GetJoypadPress(JOYKEY_DOWN) == true)
			{//����
				g_player.move.x -= sinf(D3DX_PI * 0.25f) * 0.3f;
				g_player.move.y += cosf(D3DX_PI * 0.25f) * 0.3f;
			}
			else
			{//��
				g_player.move.x -= 0.3f;
			}
		}
		//�E
		else if (GetKeyboardPress(DIK_D) == true|| GetJoypadPress(JOYKEY_RIGET) == true)
		{// D
			if (GetKeyboardPress(DIK_W) == true || GetJoypadPress(JOYKEY_UP) == true)
			{//�E��
				g_player.move.x += sinf(D3DX_PI * 0.75f) * 0.3f;
				g_player.move.y += cosf(D3DX_PI * 0.75f) * 0.3f;
			}
			else if (GetKeyboardPress(DIK_S) == true || GetJoypadPress(JOYKEY_DOWN) == true)
			{//�E��
				g_player.move.x += sinf(D3DX_PI * 0.75f) * 0.3f;
				g_player.move.y -= cosf(D3DX_PI * 0.75f) * 0.3f;
			}
			else
			{//�E
				g_player.move.x += 0.3f;
			}
		}
		//��
		else if (GetKeyboardPress(DIK_W) == true|| GetJoypadPress(JOYKEY_UP) == true)
		{// W
			if (GetKeyboardPress(DIK_A) == true || GetJoypadPress(JOYKEY_LEFT) == true)
			{//����
				g_player.move.x -= sinf(D3DX_PI * 0.75f) * 0.3f;
				g_player.move.y += cosf(D3DX_PI * 0.75f) * 0.3f;
			}
			else if (GetKeyboardPress(DIK_D) == true || GetJoypadPress(JOYKEY_RIGET) == true)
			{//�E��
				g_player.move.x += sinf(D3DX_PI * 0.75f) * 0.3f;
				g_player.move.y += cosf(D3DX_PI * 0.75f) * 0.3f;
			}
			else
			{//��
				g_player.move.y -= 0.3f;
			}
		}
		//��
		else if (GetKeyboardPress(DIK_S) == true|| GetJoypadPress(JOYKEY_DOWN) == true)
		{// S

			if (GetKeyboardPress(DIK_A) == true || GetJoypadPress(JOYKEY_LEFT) == true)
			{//����
				g_player.move.x -= sinf(D3DX_PI * 0.25f) * 0.3f;
				g_player.move.y += cosf(D3DX_PI * 0.25f) * 0.3f;
			}
			else if (GetKeyboardPress(DIK_D) == true || GetJoypadPress(JOYKEY_RIGET) == true)
			{//�E��
				g_player.move.x += sinf(D3DX_PI * 0.25f) * 0.3f;
				g_player.move.y -= cosf(D3DX_PI * 0.25f) * 0.3f;
			}
			else
			{//��
				g_player.move.y += 0.3f;
			}
		}
		////��]
		//else if (GetKeyboardPress(DIK_Q) == true|| GetJoypadPress(JOYKEY_L1) == true)
		//{
		//	g_player.rot.z += 0.1;
		//	if (g_player.rot.z >= D3DX_PI)
		//	{
		//		g_player.rot.z = -D3DX_PI;
		//	}
		//}
		////��]
		//else if (GetKeyboardPress(DIK_E) == true|| GetJoypadPress(JOYKEY_R1) == true)
		//{
		//	g_player.rot.z -= 0.1;
		//	if (g_player.rot.z <= -D3DX_PI)
		//	{
		//		g_player.rot.z = D3DX_PI;
		//	}
		//}
		//�e����
		if (KeyboardTrigger(DIK_SPACE) == true|| GetJoypadPress(JOYKEY_A) == true)
		{
			//�e�̐ݒ�
			SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI) * 10.0f, cosf(g_player.rot.z + D3DX_PI) * 10.0f, 0.0f), 100, BULLETTYPE_PLAYER);

			////��������
			//int nCnt,nData=-25;
			//for (nCnt = 0; nCnt < 3; nCnt++)
			//{
			//	SetBullet(D3DXVECTOR3(g_player.pos.x, g_player.pos.y + nData, 0.0f), D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI) * 10.0f, cosf(g_player.rot.z + D3DX_PI) * 10.0f, 0.0f), 100, BULLETTYPE_PLAYER);
			//	SetBullet(D3DXVECTOR3(g_player.pos.x, g_player.pos.y + nData, 0.0f), D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI + 0.5) * 10.0f, cosf(g_player.rot.z + D3DX_PI + 0.5) * 10.0f, 0.0f), 100, BULLETTYPE_PLAYER);
			//	SetBullet(D3DXVECTOR3(g_player.pos.x, g_player.pos.y + nData, 0.0f), D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI - 0.5) * 10.0f, cosf(g_player.rot.z + D3DX_PI - 0.5) * 10.0f, 0.0f), 100, BULLETTYPE_PLAYER);
			//	nData += 25;
			//}

			////���
			//SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI) * -10.0f, cosf(g_player.rot.z + D3DX_PI) * -10.0f, 0.0f), 100, BULLETTYPE_PLAYER);
			////�΂�
			//SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI + 0.5) * 10.0f, cosf(g_player.rot.z + D3DX_PI + 0.5) * 10.0f, 0.0f), 100, BULLETTYPE_PLAYER);
			//SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI - 0.5) * 10.0f, cosf(g_player.rot.z + D3DX_PI - 0.5) * 10.0f, 0.0f), 100, BULLETTYPE_PLAYER);

			////�΂ߌ��
			//SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI + 0.5) * -10.0f, cosf(g_player.rot.z + D3DX_PI + 0.5) * -10.0f, 0.0f), 100, BULLETTYPE_PLAYER);
			//SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI - 0.5) * -10.0f, cosf(g_player.rot.z + D3DX_PI - 0.5) * -10.0f, 0.0f), 100, BULLETTYPE_PLAYER);
			////�㉺ 
			//SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI/2) * 10.0f, cosf(g_player.rot.z + D3DX_PI/2) * 10.0f, 0.0f), 100, BULLETTYPE_PLAYER);
			//SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI/2) * -10.0f, cosf(g_player.rot.z + D3DX_PI/2) * -10.0f, 0.0f), 100, BULLETTYPE_PLAYER);
		}

		//START
		else if (GetKeyboardPress(DIK_0) == true||GetJoypadPress(JOYKEY_START) == true)
		{
			SetResult(RESULT_GAMEOVER);
			SetFade(MODE_RESULT);
		}
		//BACK
		else if (GetKeyboardPress(DIK_9) == true || GetJoypadPress(JOYKEY_BACK) == true)
		{
			SetFade(MODE_TITLE);
		}


		//�ړ�����
		if (g_player.pos.x <= 25)
		{
			g_player.move.x = 0.3;
		}
		else if(g_player.pos.x >= SCREEN_WIDTH - 25)
		{
			g_player.move.x = -0.3;
		}
		if (g_player.pos.y <= 40)
		{
			g_player.move.y = 0.3;
		}
		else if (g_player.pos.y >= SCREEN_HEIGHT - 40)
		{
			g_player.move.y = -0.3;
		}

		//�ʒu���X�V
		g_player.pos.x += g_player.move.x;
		g_player.pos.y += g_player.move.y;
		//�ړ��ʂ��X�V
		g_player.move.x += (0.0f - g_player.move.x) * 0.02f;
		g_player.move.y += (0.0f - g_player.move.y) * 0.02f;

		pVtx[0].pos.x = g_player.pos.x + sinf(g_player.rot.z + (-D3DX_PI + g_player.fAnglePlayer)) * g_player.fLengthPlayer;
		pVtx[0].pos.y = g_player.pos.y + cosf(g_player.rot.z + (-D3DX_PI + g_player.fAnglePlayer)) * g_player.fLengthPlayer;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_player.pos.x + sinf(g_player.rot.z + (D3DX_PI - g_player.fAnglePlayer)) * g_player.fLengthPlayer;
		pVtx[1].pos.y = g_player.pos.y + cosf(g_player.rot.z + (D3DX_PI - g_player.fAnglePlayer)) * g_player.fLengthPlayer;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_player.pos.x + sinf(g_player.rot.z - g_player.fAnglePlayer) * g_player.fLengthPlayer;
		pVtx[2].pos.y = g_player.pos.y + cosf(g_player.rot.z - g_player.fAnglePlayer) * g_player.fLengthPlayer;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_player.pos.x + sinf(g_player.rot.z + g_player.fAnglePlayer) * g_player.fLengthPlayer;
		pVtx[3].pos.y = g_player.pos.y + cosf(g_player.rot.z + g_player.fAnglePlayer) * g_player.fLengthPlayer;
		pVtx[3].pos.z = 0.0f;

		//�A�j���[�V����
		//g_player.nCounterAnimPlayer++;
		//if ((g_player.nCounterAnimPlayer % 5) == 0)
		//{//��莞�Ԍo��
		//	//�p�^�[��No���X�V
		//	g_player.nPatternAnimPlayer = (g_player.nPatternAnimPlayer + 1) % 10;

		//	//�e�N�X�`�����W�̐ݒ�
		//	//U���W�͂T�Ŋ��������܂肪�P��0���łł�
		//	//V���W�͂T�Ŋ��������ʂ�0.?��1.?���ł킩��
		//	if (GetKeyboardPress(DIK_D) == true)
		//	{
		//		pVtx[1].tex = D3DXVECTOR2((g_player.nPatternAnimPlayer % 5) * 0.2f, (g_player.nPatternAnimPlayer / 5) * 0.5f);
		//		pVtx[0].tex = D3DXVECTOR2((g_player.nPatternAnimPlayer % 5) * 0.2f + 0.2f, (g_player.nPatternAnimPlayer / 5) * 0.5f);
		//		pVtx[3].tex = D3DXVECTOR2((g_player.nPatternAnimPlayer % 5) * 0.2f, (g_player.nPatternAnimPlayer / 5) * 0.5f + 0.5f);
		//		pVtx[2].tex = D3DXVECTOR2((g_player.nPatternAnimPlayer % 5) * 0.2f + 0.2f, (g_player.nPatternAnimPlayer / 5) * 0.5f + 0.5f);
		//	}
		//	else if (GetKeyboardPress(DIK_A) == true)
		//	{
		//		pVtx[0].tex = D3DXVECTOR2((g_player.nPatternAnimPlayer % 5) * 0.2f, (g_player.nPatternAnimPlayer / 5) * 0.5f);
		//		pVtx[1].tex = D3DXVECTOR2((g_player.nPatternAnimPlayer % 5) * 0.2f + 0.2f, (g_player.nPatternAnimPlayer / 5) * 0.5f);
		//		pVtx[2].tex = D3DXVECTOR2((g_player.nPatternAnimPlayer % 5) * 0.2f, (g_player.nPatternAnimPlayer / 5) * 0.5f + 0.5f);
		//		pVtx[3].tex = D3DXVECTOR2((g_player.nPatternAnimPlayer % 5) * 0.2f + 0.2f, (g_player.nPatternAnimPlayer / 5) * 0.5f + 0.5f);
		//	}
		//	else if (GetKeyboardPress(DIK_S) == true || GetKeyboardPress(DIK_W) == true)
		//	{
		//		pVtx[0].tex = D3DXVECTOR2((g_player.nPatternAnimPlayer % 5) * 0.2f, (g_player.nPatternAnimPlayer / 5) * 0.5f);
		//		pVtx[1].tex = D3DXVECTOR2((g_player.nPatternAnimPlayer % 5) * 0.2f + 0.2f, (g_player.nPatternAnimPlayer / 5) * 0.5f);
		//		pVtx[2].tex = D3DXVECTOR2((g_player.nPatternAnimPlayer % 5) * 0.2f, (g_player.nPatternAnimPlayer / 5) * 0.5f + 0.5f);
		//		pVtx[3].tex = D3DXVECTOR2((g_player.nPatternAnimPlayer % 5) * 0.2f + 0.2f, (g_player.nPatternAnimPlayer / 5) * 0.5f + 0.5f);
		//	}
		//}

		switch (g_player.state)
		{
		case PLAYERSTATE_NORMAL:
			break;
		case PLAYERSTATE_DAMAGE:
			g_player.nCounterState--;
			if (g_player.nCounterState <= 0)
			{
				g_player.state = PLAYERSTATE_NORMAL;
				//�|���S����ʏ�F�ɖ߂�
				VERTEX_2D* pVtx;
				//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
				g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				//���_�o�b�t�@���A�����b�N
				g_pVtxBuffPlayer->Unlock();
			}
			break;
		case PLAYERSTATE_DEATH:
			g_player.nCounterState--;
			if (g_player.nCounterState <= 0)
			{

				return;
			}
			break;
		}
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffPlayer->Unlock();
}
//======================
//�v���C���[�̕`�揈��
//======================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	if (g_player.bUse == true)
	{
		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));
		//1��
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexturePlayer);
		//�v���C���[�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}
//================
//�v���C���[�擾
//================
Player* GetPlayer(void)
{
	return &g_player;
}
//===================
//�v���C���[�̏��
//===================
void HitPlayer(int nDamage)
{
	g_player.nLife -= nDamage;
	if (g_player.nLife <= 0)
	{
		//�����̐ݒ�
		SetExplosion(g_player.pos, 1.0f);
		g_player.bUse = false;
		g_player.state = PLAYERSTATE_DEATH;
		g_player.nCounterState = 60;

		//���[�h�ݒ�����U���g�ɂ���
		SetGameState(GAMESTATE_GAMEOVER);
	}
	else
	{
		g_player.state = PLAYERSTATE_DAMAGE;
		g_player.nCounterState = 5;
		VERTEX_2D* pVtx;
		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		//���_�o�b�t�@���A�����b�N
		g_pVtxBuffPlayer->Unlock();
	}
}