//==============================
//
//  �Q�[����ʕ\������[game.h]
//  Author:kaiti
//
//==============================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"

//�Q�[���̏��
typedef enum
{
	GAMESTATE_NONE=0,//�������Ă��Ȃ����
	GAMESTATE_NORMAL,//�ʏ��ԁi�Q�[���v���C���j
	GAMESTATE_CLEAR,// �N���A
	GAMESTATE_GAMEOVER,//�I�����
	GAMESTATE_MAX
}GAMESTATE;

//�v���g�^�C�v�錾
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
void SetGameState(GAMESTATE state);
GAMESTATE GetGameSatate(void);

#endif#pragma once
