//================================
//
//  �Q�[����ʕ\������[game.cpp]
//  Author:kaiti
//
//================================
#include "game.h"
#include "player.h"
#include "background.h"
#include "input.h"
#include "bullet.h"
#include "explosion.h"
#include "enemy.h"
#include "fade.h"
#include "sound.h"
#include "score.h"
#include "result.h"
#include "effect.h"
//�O���[�o���ϐ�
GAMESTATE g_gamestate = GAMESTATE_NONE;
int g_nCounterGameState = 0;
//============
//����������
//============
void InitGame(void)
{
	//�w�i
	InitBackground();
	//�X�R�A
	InitScore();
	SetScore(0);
	//
	InitEffect();
	//�e
	InitBullet();
	//�v���C���[
	InitPlayer();
	//�G
	InitEnemy();
	SetEnemy(D3DXVECTOR3(100.0f, 100.0f, 0.0f), 0);
	//����
	InitExplosion();

	g_gamestate = GAMESTATE_NORMAL;
	g_nCounterGameState = 0;
}
//==========
//�I������
//==========
void UninitGame(void)

{
	//�w�i
	UninitBackground();
	//�X�R�A
	UninitScore();
	//�v���C���[
	UninitPlayer();
	//�e
	UninitBullet();
	//����
	UninitExplosion();
	//�G
	UninitEnemy();
	//
	UninitEffect();
}
//==========
//�X�V����
//==========
void UpdateGame(void)
{
	//�w�i
	UpdateBackground();
	//�X�R�A
	UpdateScore();
	//
	UpdateEffect();
	//�v���C���[
	UpdatePlayer();
	//�e
	UpdateBullet();
	//�G
	UpdateEnemy();
	//����
	UpdateExplosion();

	switch (g_gamestate)
	{
	case GAMESTATE_NORMAL:
		break;
	case GAMESTATE_CLEAR:
		g_nCounterGameState++;
		if (g_nCounterGameState >= 30)
		{
			g_gamestate = GAMESTATE_NONE;
			SetResult(RESULT_CLEAR);
			//���[�h�����U���g�ɂ���
			SetFade(MODE_RESULT);
		}
		break;
	case GAMESTATE_GAMEOVER:
		g_nCounterGameState++;
		if (g_nCounterGameState >= 30)
		{
			g_gamestate = GAMESTATE_NONE;
			SetResult(RESULT_GAMEOVER);
			//���[�h�����U���g�ɂ���
			SetFade(MODE_RESULT);
		}
		break;
	}
}
//==========
//�`�揈��
//==========
void DrawGame(void)
{
	//�w�i
	DrawBackground();
	//�X�R�A
	DrawScore();
	//����
	DrawExplosion();
	//
	DrawEffect();
	//�e
	DrawBullet();
	//�v���C���[
	DrawPlayer();
	//�G
	DrawEnemy();
}
//==============
//�Q�[���̏��
//==============
void SetGameState(GAMESTATE state)
{
	g_gamestate = state;
	g_nCounterGameState = 0;
}
//====================
//�Q�[���̏�Ԃ̎擾
//====================
GAMESTATE GetGameSatate(void)
{
	return g_gamestate;
}