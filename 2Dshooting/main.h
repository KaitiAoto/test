//==============================
//
//�@�E�C���h�E�\������[main.h]
//�@Author:kaiti
//
//==============================
#ifndef _MAIN_H_
#define _MAIN_H_

#include<Windows.h>
#include "d3dx9.h"

#define DIRECTINPUT_VERSION (0x0800)
#include "dinput.h"
#include "Xinput.h"
#include "xaudio2.h"
//���C�u�����̃����N
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"xinput.lib")

//�}�N����`
#define CLASS_NAME "WindowsClass"
#define WINDOW_NAME "2D�V���[�e�B���O�Q�[��"
#define SCREEN_WIDTH (1280)
#define SCREEN_HEIGHT (720)
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//���_���(2D)�̍\����
typedef struct
{
	D3DXVECTOR3 pos;//���_���W
	float rhw;      //���W�ϊ��p�W��
	D3DCOLOR col;   //���_�J���[
	D3DXVECTOR2 tex;//�e�N�X�`�����W
}VERTEX_2D;

//
typedef enum
{
	MODE_TITLE=0,
	MODE_GAME,
	MODE_RESULT,
	MODE_MAX
}MODE;

//�v���g�^�C�v�錾
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
void SetMode(MODE mode);
MODE GetMode(void);

LPDIRECT3DDEVICE9 GetDevice(void);

#endif